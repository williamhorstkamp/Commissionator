#include <QSqlQuery>
#include <QDate>
#include "ComModel.h"

namespace Commissionator {
    ComModel::ComModel(QObject *parent) : QObject(parent) {
        sql = new QSqlDatabase();
    }

    ComModel::~ComModel() {
        delete insertCommissionerQuery;
        delete sql;
    }

    void ComModel::newRecord() {
        build();
        prepare();
    }
    
    QDataWidgetMapper *ComModel::getCommissioner() {
        return commissionerMapper;
    }

    QSqlQueryModel *ComModel::getCommissionerCommissions() {

    }

    QSqlQueryModel *ComModel::getCommissionerContacts() {

    }

    QSqlQueryModel *ComModel::getCommissioners() {
        return commissionersModel;
    }

    QSqlQueryModel *ComModel::getCommissionPayments() {

    }

    QSqlQueryModel *ComModel::getCommissions() {
        return commissionsModel;
    }

    QSqlQueryModel *ComModel::getContactTypes() {
        return contactTypesModel;
    }

    QSqlQueryModel *ComModel::getPaymentTypes() {
        return paymentTypesModel;
    }

    QDataWidgetMapper *ComModel::getPiece() {

    }

    QSqlQueryModel *ComModel::getPieces() {

    }

    QSqlQueryModel *ComModel::getProducts() {

    }

    void ComModel::searchCommissioners(const QString name, const QString dateOldest,
        const QString balance) {
        commissionersModel->query().bindValue(0, "%" + name + "%");
        commissionersModel->query().bindValue(1, "%" + dateOldest + "%");
        commissionersModel->query().bindValue(2, "%" + balance + "%");
        commissionersModel->query().exec();
        commissionersModel->setQuery(commissionersModel->query());
    }

    void ComModel::searchCommissions(const QString commissioner,
        const QString createDate, const QString paidDate,
        const QString dueDate, const QString numberOfPieces,
        const QString finishDate) {
        commissionsModel->query().bindValue(0, "%" + commissioner + "%");
        commissionsModel->query().bindValue(1, "%" + createDate + "%");
        commissionsModel->query().bindValue(2, "%" + paidDate + "%");
        commissionsModel->query().bindValue(3, "%" + dueDate + "%");
        commissionsModel->query().bindValue(4, "%" + numberOfPieces + "%");
        commissionsModel->query().bindValue(5, "%" + finishDate + "%");
        commissionsModel->query().exec();
        commissionsModel->setQuery(commissionsModel->query());
    }

    void ComModel::searchPieces(const QString commissionerName,
        const QString pieceName, const QString startDate,
        const QString finishDate) {

    }

    void ComModel::searchProducts(const QString name, const QString basePrice,
        const QString numberOfPieces) {

    }

    void ComModel::setCommission(const QModelIndex &index) {

    }

    void ComModel::setCommissioner(const QModelIndex &index) {
        qobject_cast<QSqlQueryModel *>(commissionerMapper->model())->query()
            .bindValue(0, getValue(index, 0));
    }

    void ComModel::setPiece(const QModelIndex &index) {

    }

    void ComModel::insertCommission(const int commissionerId, 
        const QDateTime dueDate) {
        insertCommissionQuery->bindValue(0, commissionerId);
        insertCommissionQuery->bindValue(1, dueDate.toMSecsSinceEpoch());
        insertCommissionQuery->bindValue(2, 
            QDateTime::currentDateTime().toMSecsSinceEpoch());
        insertCommissionQuery->bindValue(3, "");
        insertCommissionQuery->exec();
        searchCommissions("", "", "", "", "", "");
    }

    void ComModel::insertCommissioner(const QString commissionerName,
        const QString commissionerNotes) {
        insertCommissionerQuery->bindValue(0, commissionerName);
        insertCommissionerQuery->bindValue(1, commissionerNotes);
        insertCommissionerQuery->exec();
        searchCommissioners("", "", "");
    }

    void ComModel::insertContact(const int commissionerId,
        const int contactType, const QString contactEntry) {
        insertContactQuery->bindValue(0, commissionerId);
        insertContactQuery->bindValue(1, contactType);
        insertContactQuery->bindValue(2, contactEntry);
        //update commissionerContacts
    }

    void ComModel::insertContactType(const QString contactTypeName) {
        insertContactTypeQuery->bindValue(0, contactTypeName);
        insertContactTypeQuery->exec();
        contactTypesModel->query().exec();
        contactTypesModel->setQuery(contactTypesModel->query());
    }

    void ComModel::insertPayment(const int commissionId, const int paymentTypeId,
        const double paymentAmount, const QString paymentNotes) {
        insertPaymentQuery->bindValue(0, commissionId);
        insertPaymentQuery->bindValue(1, paymentTypeId);
        insertPaymentQuery->bindValue(2, paymentAmount);
        insertPaymentQuery->bindValue(3, paymentNotes);
        insertPaymentQuery->bindValue(4, 
            QDateTime::currentDateTime().toMSecsSinceEpoch());
        insertPaymentQuery->exec();
        //update commissionPayments
    }

    void ComModel::insertPaymentType(const QString typeName) {
        insertPaymentTypeQuery->bindValue(0, typeName);
        insertPaymentTypeQuery->exec();
        paymentTypesModel->query().exec();
        paymentTypesModel->setQuery(paymentTypesModel->query());
    }

    void ComModel::insertPiece(const int commission, const int product,
        const QString name, const QString description) {
        insertPieceQuery->bindValue(0, commission);
        insertPieceQuery->bindValue(1, product);
        insertPieceQuery->bindValue(2, name);
        insertPieceQuery->bindValue(3, description);
        insertPieceQuery->bindValue(4, 0);
        insertPieceQuery->bindValue(5, 0);
        insertPieceQuery->exec();
        searchPieces("", "", "", "");
    }

    void ComModel::insertProduct(const QString productName, const double basePrice) {
        insertProductQuery->bindValue(0, productName);
        insertProductQuery->exec();
        QSqlQuery insertedRow;
        insertedRow.exec("(SELECT last_insert_rowid())");
        insertedRow.first();
        insertedRow.value(0).toInt();
        insertProductPrice(insertedRow.value(0).toInt(), basePrice);
        searchProducts("", "", "");
    }

    void ComModel::insertProductPrice(const int productId, const double basePrice) {
        insertProductQuery->bindValue(0, productId);
        insertProductQuery->bindValue(1, basePrice);
        insertProductPriceQuery->bindValue(2,
            QDateTime::currentDateTime().toMSecsSinceEpoch());
        insertProductPriceQuery->exec();
        searchProducts("", "", "");
    }

    void ComModel::build() {
        *sql = QSqlDatabase::addDatabase("QSQLITE");
        sql->setDatabaseName(":memory:");
        sql->open();
        sql->exec("PRAGMA foreign_keys = ON;");
        sql->exec("CREATE TABLE IF NOT EXISTS ContactType("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "type	TEXT NOT NULL"
            ");"
            "CREATE TABLE IF NOT EXISTS Contact("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "commissioner   INTEGER NOT NULL,"
            "type	INTEGER NOT NULL,"
            "entry	TEXT NOT NULL,"
            "FOREIGN KEY(type) REFERENCES ContactType(id),"
            "FOREIGN KEY(commissioner) REFERENCES Commissioner(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS Commissioner("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name	TEXT NOT NULL,"
            "notes  TEXT NOT NULL"
            ");"
            "CREATE TABLE IF NOT EXISTS Product("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name	TEXT NOT NULL"
            ");"
            "CREATE TABLE IF NOT EXISTS ProductPrices("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "product INTEGER NOT NULL,"
            "price REAL NOT NULL,"
            "date TEXT NOT NULL,"
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS ProductOption("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name	TEXT NOT NULL,"
            "price	REAL NOT NULL,"
            "isInt	BOOL NOT NULL,"
            "product	INTEGER NOT NULL,"
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS ProductOptionPrices("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "productOption INTEGER NOT NULL,"
            "price REAL NOT NULL,"
            "date TEXT NOT NULL,"
            "FOREIGN KEY(productOption)REFERENCES ProductOption(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS Piece("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name   TEXT NOT NULL,"
            "description    TEXT NOT NULL,"
            "commission   INTEGER NOT NULL,"
            "product  INTEGER NOT NULL,"
            "createDate TEXT NOT NULL,"
            "finishDate TEXT NOT NULL,"
            "FOREIGN KEY(commission) REFERENCES Commission(id),"
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS PieceOption("
            "field	TEXT NOT NULL,"
            "piece	INTEGER NOT NULL,"
            "option	INTEGER NOT NULL,"
            "FOREIGN KEY(piece) REFERENCES Piece(id),"
            "FOREIGN KEY(option) REFERENCES ProductOption(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS Commission("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "createDate	TEXT NOT NULL,"
            "dueDate TEXT NOT NULL, "
            "paidDate	TEXT NOT NULL,"
            "commissioner INTEGER NOT NULL,"
            "FOREIGN KEY(commissioner) REFERENCES Commissioner(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS PaymentType("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name	TEXT NOT NULL"
            ");"
            "CREATE TABLE IF NOT EXISTS Payment("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "commission	INTEGER NOT NULL,"
            "method	INTEGER NOT NULL,"
            "date	TEXT NOT NULL,"
            "fee	REAL NOT NULL,"
            "note   TEXT NOT NULL,"
            "FOREIGN KEY(commission) REFERENCES Commission(id),"
            "FOREIGN KEY(method) REFERENCES PaymentType(id)"
            ");");
        //needs to add generics (product, commissioner, ?)
    }

    QVariant getValue(const QModelIndex &index, int column) {
        if (index.isValid())
            return index.model()->data(index.model()->index(index.row(), column));
        else
            return QVariant();
    }

    void ComModel::prepare() {
        commissionerMapper = new QDataWidgetMapper(this);
        QSqlQueryModel commissionerModel(this);
        commissionerMapper->setModel(&commissionerModel);
        commissionerModel.setQuery(QSqlQuery("SELECT name, "
            "datetime(min(Commission.createDate), 'unixepoch', 'localtime'), "
            "CASE WHEN(SELECT SUM(a.price) - b.fee FROM"
            "(SELECT ProductPrices.price price FROM Commission"
            "INNER JOIN Piece ON Commission.id = Piece.commission"
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product"
            "WHERE Commission.commissioner = C.id"
            "AND ProductPrices.date < Commission.createDate"
            "GROUP BY Piece.id HAVING date = max(date)) a"
            "LEFT JOIN(SELECT SUM(Payment.fee) fee FROM Payment"
            "INNER JOIN Commission ON Payment.commission = Commission.id"
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id"
            "WHERE Commissioner.id = C.id) b) = 0 THEN 'Paid off'"
            "HEN(SELECT SUM(a.price) FROM"
            "SELECT ProductPrices.price price FROM Commission"
            "INNER JOIN Piece ON Commission.id = Piece.commission"
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product"
            "WHERE Commission.commissioner = C.id"
            "AND ProductPrices.date < Commission.createDate"
            "GROUP BY Piece.id"
            "HAVING date = max(date)) a) IS NULL THEN 'No Commissioned Pieces'"
            "ELSE(SELECT SUM(a.price) - b.fee FROM"
            "(SELECT ProductPrices.price price FROM Commission"
            "INNER JOIN Piece ON Commission.id = Piece.commission"
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product"
            "WHERE Commission.commissioner = C.id"
            "AND ProductPrices.date < Commission.createDate"
            "GROUP BY Piece.id HAVING date = max(date)) a"
            "LEFT JOIN(SELECT SUM(Payment.fee) fee FROM Payment"
            "INNER JOIN Commission ON Payment.commission = Commission.id"
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id"
            "WHERE Commissioner.id = C.id) b)"
            "END AS amountOwed, C.notes"
            "FROM Commissioner C"
            "LEFT JOIN Commission ON C.id = Commission.commissioner"
            "WHERE C.id = (?)"));
        commissionersModel = new QSqlQueryModel(this);
        commissionersModel->setQuery(QSqlQuery("SELECT name,"
            "CASE WHEN max(Commission.createDate) IS NULL THEN 'No Commissions'"
            "ELSE datetime(max(Commission.createDate), 'unixepoch', 'localtime')"
            "END AS firstCommission,"
            "CASE WHEN(SELECT SUM(a.price) - b.fee FROM"
            "(SELECT ProductPrices.price price FROM Commission"
            "INNER JOIN Piece ON Commission.id = Piece.commission"
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product"
            "WHERE Commission.commissioner = C.id"
            "AND ProductPrices.date < Commission.createDate"
            "GROUP BY Piece.id HAVING date = max(date)) a"
            "LEFT JOIN (SELECT SUM(Payment.fee) fee FROM Payment"
            "INNER JOIN Commission ON Payment.commission = Commission.id"
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id"
            "WHERE Commissioner.id = C.id) b) = 0 THEN 'Paid off'"
            "WHEN(SELECT SUM(a.price) FROM"
            "(SELECT ProductPrices.price price FROM Commission"
            "INNER JOIN Piece ON Commission.id = Piece.commission"
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product"
            "WHERE Commission.commissioner = C.id"
            "AND ProductPrices.date < Commission.createDate"
            "GROUP BY Piece.id"
            "HAVING date = max(date)) a) IS NULL THEN 'No Commissioned Pieces'"
            "ELSE (SELECT SUM(a.price) - b.fee FROM"
            "(SELECT ProductPrices.price price FROM Commission"
            "INNER JOIN Piece ON Commission.id = Piece.commission"
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product"
            "WHERE Commission.commissioner = C.id"
            "AND ProductPrices.date < Commission.createDate"
            "GROUP BY Piece.id HAVING date = max(date)) a"
            "LEFT JOIN (SELECT SUM(Payment.fee) fee FROM Payment"
            "INNER JOIN Commission ON Payment.commission = Commission.id"
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id"
            "WHERE Commissioner.id = C.id) b)"
            "END AS amountOwed"
            "FROM Commissioner C"
            "LEFT JOIN Commission ON C.id = Commission.commissioner"
            "WHERE name LIKE (?)"
            "GROUP BY C.id HAVING firstCommission like (?)"
            "AND amountOwed like (?);"));
        searchCommissioners("", "", "");
        commissionsModel = new QSqlQueryModel(this);
        commissionsModel->setQuery(QSqlQuery("SELECT Commission.id, "
            "Commissioner.name, Commission.createDate, Commission.paidDate, "
            "Commission.dueDate, COUNT(Piece.id), "
            "CASE WHEN MIN(Piece.finishDate) LIKE '0' THEN 'Unfinished' "
            "WHEN MIN(Piece.finishDate IS NULL THEN 'No Pieces'"
            "ELSE MAX(Piece.finishDate) "
            "END "
            "FROM Commission INNER JOIN "
            "Commissioner ON Commission.Commissioner = Commissioner.id "
            "LEFT JOIN Piece ON Commission.id = Piece.commission "
            "WHERE Commissioner.name LIKE (?) AND "
            "Commission.createDate LIKE (?) AND "
            "Commission.paidDate LIKE (?) AND Commission.dueDate LIKE (?) "
            "GROUP BY Commission.id "
            "HAVING COUNT(Piece.id) LIKE (?) AND "
            "MAX(Piece.finishDate) LIKE (?)"));
        contactTypesModel = new QSqlQueryModel(this);
        contactTypesModel->setQuery(QSqlQuery("SELECT type FROM ContactType"));
        contactTypesModel->query().exec();
        searchCommissions("", "", "", "", "", "");
        insertCommissionerQuery = new QSqlQuery("INSERT INTO "
            "Commissioner(name, notes) VALUES (?, ?);");
        insertCommissionQuery = new QSqlQuery("INSERT INTO "
            "Commission(commissioner, dueDate, createDate, paidDate) "
            "VALUES (?, ?, ?, ?);");
        insertContactTypeQuery = new QSqlQuery("INSERT INTO "
            "ContactType(type) VALUES (?)");
        insertContactQuery = new QSqlQuery("INSERT INTO"
            "Contact(commissioner, type, entry) VALUES(?, ?, ?)");
        insertPaymentTypeQuery = new QSqlQuery("INSERT INTO"
            "PaymentType(name) VALUES (?)");
        insertPaymentQuery = new QSqlQuery("INSERT INTO"
            "Payment(commission, method, fee, note, date)"
            "VALUES (?, ?, ?, ?, ?)");
        insertPieceQuery = new QSqlQuery("INSERT INTO "
            "Piece(commission, product, name, description, createDate, finishDate) "
            "VALUES(?, ?, ?, ?, ?, ?)");
        insertProductPriceQuery = new QSqlQuery("INSERT INTO "
            "ProductPrices(product, price, date) "
            "VALUES (?, ?, ?);");
        insertProductQuery = new QSqlQuery("INSERT INTO "
            "Product(name) VALUES(?);");
        paymentTypesModel = new QSqlQueryModel(this);
        paymentTypesModel->setQuery(QSqlQuery("SELECT name FROM PaymentType"));
        paymentTypesModel->query().exec();
    }
}