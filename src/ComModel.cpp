#include <QSqlQuery>
#include <QDate>
#include "ComModel.h"

namespace Commissionator {
    ComModel::ComModel(QObject *parent) : QObject(parent) {
        newRecord();
    }

    ComModel::~ComModel() {
//        delete insertCommissionerQuery;
        sql.close();
        //delete sql;
    }

    void ComModel::newRecord() {
        build();
        prepare();
    }
    
    QDataWidgetMapper *ComModel::getCommissionerEditable() {
        return commissionerEditableMapper;
    }

    QDataWidgetMapper *ComModel::getCommissionerGenerated() {
        return commissionerGeneratedMapper;
    }

    QSqlQueryModel *ComModel::getCommissionerCommissions() {
		return commissionerCommissionsModel;
    }

    QSqlQueryModel *ComModel::getCommissionerContacts() {
		return commissionerContactsModel;
    }

    QSqlQueryModel *ComModel::getCommissioners() {
        return commissionersModel;
    }

    QSqlQueryModel *ComModel::getCommissionPayments() {
		return commissionPaymentsModel;
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

    QDataWidgetMapper *ComModel::getPieceEditable() {
        return pieceEditableMapper;
    }

    QDataWidgetMapper *ComModel::getPieceGenerated() {
        return pieceGeneratedMapper;
    }

    QSqlQueryModel *ComModel::getPieces() {
        return piecesModel;
    }

    QSqlQueryModel *ComModel::getProducts() {
        return productsModel;
    }

    void ComModel::searchCommissioners(const QString name, const QString dateOldest,
        const QString balance) {
        //commissionersModel->query().bindValue(0, "%" + name + "%");
        //commissionersModel->query().bindValue(1, "%" + dateOldest + "%");
        //commissionersModel->query().bindValue(2, "%" + balance + "%");
        commissionersModel->query().addBindValue("%");
        commissionersModel->query().addBindValue("%");
        commissionersModel->query().addBindValue("%");
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
        piecesModel->query().bindValue(0, "%" + commissionerName + "%");
        piecesModel->query().bindValue(1, "%" + pieceName + "%");
        piecesModel->query().bindValue(2, "%" + startDate + "%");
        piecesModel->query().bindValue(3, "%" + finishDate + "%");
        piecesModel->query().exec();
        piecesModel->setQuery(piecesModel->query());
    }

    void ComModel::searchProducts(const QString name, const QString basePrice,
        const QString numberOfPieces) {
        productsModel->query().bindValue(0, "%" + name + "%");
        productsModel->query().bindValue(1, "%" + basePrice + "%");
        productsModel->query().bindValue(2, "%" + numberOfPieces + "%");
        productsModel->query().exec();
        productsModel->setQuery(productsModel->query());
    }

    void ComModel::setCommission(const QModelIndex &index) {
        commissionPaymentsModel->query().bindValue(0, getValue(index, 0));
        commissionPaymentsModel->query().exec();
        commissionPaymentsModel->setQuery(commissionPaymentsModel->query());
    }

    void ComModel::setCommissioner(const QModelIndex &index) {
        commissionerGeneratedModel->query().bindValue(0, getValue(index, 0));
        commissionerGeneratedModel->query().exec();
        commissionerGeneratedModel->setQuery(commissionerGeneratedModel->query());
        commissionerEditableMapper->setCurrentModelIndex(index);
        commissionerCommissionsModel->query().bindValue(0, getValue(index, 0));
        commissionerCommissionsModel->query().exec();
        commissionerCommissionsModel->setQuery(commissionerCommissionsModel->query());
        commissionerContactsModel->query().bindValue(0, getValue(index, 0));
        commissionerContactsModel->query().exec();
        commissionerContactsModel->setQuery(commissionerContactsModel->query());
    }

    void ComModel::setPiece(const QModelIndex &index) {
        QSqlQueryModel *pieGenQueryModel = qobject_cast<QSqlQueryModel *>
            (pieceGeneratedMapper->model());
        pieGenQueryModel->query().bindValue(0, getValue(index, 0));
        pieGenQueryModel->query().exec();
        pieGenQueryModel->setQuery(pieGenQueryModel->query());
        pieceEditableMapper->setCurrentModelIndex(index);
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
        commissionerContactsModel->query().exec();
        commissionerContactsModel->setQuery(commissionerContactsModel->query());
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
        commissionPaymentsModel->query().exec();
        commissionPaymentsModel->setQuery(commissionPaymentsModel->query());
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
        insertPieceQuery->bindValue(4, QDateTime::currentDateTime().toMSecsSinceEpoch());
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
        sql = QSqlDatabase::addDatabase("QSQLITE");
        sql.setDatabaseName(":memory:");
        sql.open();
        sql.exec("PRAGMA foreign_keys = ON;");
        sql.exec("CREATE TABLE IF NOT EXISTS ContactType("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "type	TEXT NOT NULL"
            ");");
        sql.exec("CREATE TABLE IF NOT EXISTS Contact("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "commissioner   INTEGER NOT NULL, "
            "type	INTEGER NOT NULL, "
            "entry	TEXT NOT NULL, "
            "FOREIGN KEY(type) REFERENCES ContactType(id), "
            "FOREIGN KEY(commissioner) REFERENCES Commissioner(id)"
            ");"
            );
        sql.exec("CREATE TABLE IF NOT EXISTS Commissioner("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name	TEXT NOT NULL, "
            "notes  TEXT NOT NULL"
            ");"
            );
        sql.exec("CREATE TABLE IF NOT EXISTS Product("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name	TEXT NOT NULL"
            ");"
            );
        sql.exec("CREATE TABLE IF NOT EXISTS ProductPrices("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "product INTEGER NOT NULL, "
            "price REAL NOT NULL, "
            "date TEXT NOT NULL, "
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");"
            );
        sql.exec("CREATE TABLE IF NOT EXISTS ProductOption("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name	TEXT NOT NULL, "
            "price	REAL NOT NULL, "
            "isInt	BOOL NOT NULL, "
            "product	INTEGER NOT NULL, "
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");"
            );
        sql.exec("CREATE TABLE IF NOT EXISTS ProductOptionPrices("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "productOption INTEGER NOT NULL, "
            "price REAL NOT NULL, "
            "date TEXT NOT NULL, "
            "FOREIGN KEY(productOption)REFERENCES ProductOption(id)"
            ");"
            );
        sql.exec("CREATE TABLE IF NOT EXISTS Piece("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name   TEXT NOT NULL, "
            "commission   INTEGER NOT NULL, "
            "product  INTEGER NOT NULL, "
            "createDate TEXT NOT NULL, "
            "finishDate TEXT NOT NULL, "
            "notes TEXT NOT NULL, "
            "FOREIGN KEY(commission) REFERENCES Commission(id), "
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");"
            );
        sql.exec("CREATE TABLE IF NOT EXISTS PieceOption("
            "field	TEXT NOT NULL, "
            "piece	INTEGER NOT NULL, "
            "option	INTEGER NOT NULL, "
            "FOREIGN KEY(piece) REFERENCES Piece(id), "
            "FOREIGN KEY(option) REFERENCES ProductOption(id)"
            ");"
            );
        sql.exec("CREATE TABLE IF NOT EXISTS Commission("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "createDate	TEXT NOT NULL, "
            "dueDate TEXT NOT NULL, "
            "paidDate	TEXT NOT NULL, "
            "commissioner INTEGER NOT NULL, "
            "notes TEXT NOT NULL, "
            "FOREIGN KEY(commissioner) REFERENCES Commissioner(id)"
            ");"
            );
        sql.exec("CREATE TABLE IF NOT EXISTS PaymentType("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name	TEXT NOT NULL"
            ");"
            );
        sql.exec("CREATE TABLE IF NOT EXISTS Payment("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "commission	INTEGER NOT NULL, "
            "method	INTEGER NOT NULL, "
            "date	TEXT NOT NULL, "
            "fee	REAL NOT NULL, "
            "note   TEXT NOT NULL, "
            "FOREIGN KEY(commission) REFERENCES Commission(id), "
            "FOREIGN KEY(method) REFERENCES PaymentType(id)"
            ");");
        //needs to add generics (product, commissioner, ?)
    }

    QVariant ComModel::getValue(const QModelIndex &index, int column) {
        if (index.isValid())
            return index.model()->data(index.model()->index(index.row(), column));
        else
            return QVariant();
    }

    void ComModel::prepare() {
		commissionerCommissionsModel = new QSqlQueryModel(this);
        commissionerCommissionsModel->setQuery(QSqlQuery("SELECT createDate,"
            " paidDate, SUM(price), finishDate FROM (SELECT datetime"
            "(Commission.createDate, 'unixepoch', 'localtime') createDate, "
            "datetime(Commission.paidDate, 'unixepoch', 'localtime' paidDate,)"
            "ProductPrices.price price, datetime(max(Piece.finishDate),"
            " 'unixepoch', 'localtime') finishDate"
            "FROM Commission"
            "INNER JOIN Piece ON Commission.id = Piece.commission"
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product"
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id"
            "WHERE Commissioner.id = (?)"
            "AND ProductPrices.date < Commission.createDate"
            "GROUP BY Piece.id HAVING date = max(date));", sql));
		commissionerContactsModel = new QSqlQueryModel(this);
        commissionerContactsModel->setQuery(QSqlQuery("SELECT ContactType.type,"
            "Contact.entry FROM Contact"
            "INNER JOIN ContactType ON Contact.type = ContactType.id"
            "WHERE Contact.commissioner = (?);", sql));
        commissionerEditableMapper = new QDataWidgetMapper(this);
        QSqlTableModel commissionerEditableModel(this, sql);
        commissionerEditableModel.setTable("Commissioner");
        commissionerEditableMapper->setModel(&commissionerEditableModel);
        commissionerGeneratedMapper = new QDataWidgetMapper(this);
        commissionerGeneratedModel = new QSqlQueryModel(this);
        commissionerGeneratedMapper->setModel(commissionerGeneratedModel);
        commissionerGeneratedModel->setQuery(QSqlQuery("SELECT "
            "min(Commission.createDate), "
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
            "WHEN(SELECT SUM(a.price) FROM"
            "(SELECT ProductPrices.price price FROM Commission"
            "INNER JOIN Piece ON Commission.id = Piece.commission"
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product"
            "WHERE Commission.commissioner = C.id"
            "AND ProductPrices.date < Commission.createDate"
            "GROUP BY Piece.id"
            "HAVING date = max(date)) a) IS NULL THEN 'No Commissioned Pieces'"
            "WHEN(SELECT SUM(b.fee) FROM "
            "(SELECT SUM(Payment.fee) fee FROM Payment"
            "INNER JOIN Commission ON Payment.commission = Commission.id"
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id"
            "WHERE Commissioner.id = C.id) b) IS NULL THEN (SELECT SUM(a.price) FROM"
            "(SELECT ProductPrices.price price FROM Commission"
            "INNER JOIN Piece ON Commission.id = Piece.commission"
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product"
            "WHERE Commission.commissioner = C.id"
            "AND ProductPrices.date < Commission.createDate"
            "GROUP BY Piece.id HAVING date = max(date)) a)"
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
            "END AS amountOwed"
            "FROM Commissioner C"
            "LEFT JOIN Commission ON C.id = Commission.commissioner"
            "WHERE C.id = (?);", sql));
        commissionersModel = new QSqlQueryModel(this);
        commissionersModel->setQuery(QSqlQuery("SELECT C.id, C.name, "
            "CASE WHEN max(Commission.createDate) IS NULL THEN 'No Commissions' "
            "ELSE datetime(max(Commission.createDate), 'unixepoch', 'localtime') "
            "END AS firstCommission, "
            "CASE WHEN(SELECT SUM(a.price) - b.fee FROM "
            "(SELECT ProductPrices.price price FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "WHERE Commission.commissioner = C.id "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) a "
            "LEFT JOIN (SELECT SUM(Payment.fee) fee FROM Payment "
            "INNER JOIN Commission ON Payment.commission = Commission.id "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "WHERE Commissioner.id = C.id) b) = 0 THEN 'Paid off' "
            "WHEN(SELECT SUM(a.price) FROM "
            "(SELECT ProductPrices.price price FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "WHERE Commission.commissioner = C.id "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id "
            "HAVING date = max(date)) a) IS NULL THEN 'No Commissioned Pieces' "
            "ELSE (SELECT SUM(a.price) - b.fee FROM "
            "(SELECT ProductPrices.price price FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "WHERE Commission.commissioner = C.id "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) a "
            "LEFT JOIN (SELECT SUM(Payment.fee) fee FROM Payment "
            "INNER JOIN Commission ON Payment.commission = Commission.id "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "WHERE Commissioner.id = C.id) b) "
            "END AS amountOwed "
            "FROM Commissioner C "
            "LEFT JOIN Commission ON C.id = Commission.commissioner "
            "WHERE name LIKE (?) "
            "GROUP BY C.id HAVING firstCommission like (?) "
            "AND amountOwed like (?);", sql));

        commissionersModel->query().addBindValue(QVariant("%"));
        commissionersModel->query().addBindValue(QVariant("%"));
        commissionersModel->query().addBindValue(QVariant("%"));

        commissionersModel->query().exec();
        //searchCommissioners("", "", "");
		commissionPaymentsModel = new QSqlQueryModel(this);
        commissionPaymentsModel->setQuery(QSqlQuery("SELECT PaymentType.name,"
            "DATETIME(Payment.date, 'unixepoch', 'localtime'), Payment.fee, "
            "Payment.note FROM Payment "
            "INNER JOIN PaymentType ON Payment.method = PaymentType.id"
            "WHERE Payment.commission = (?);", sql));
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
            "MAX(Piece.finishDate) LIKE (?);", sql));
        searchCommissions("", "", "", "", "", "");
        contactTypesModel = new QSqlQueryModel(this);
        contactTypesModel->setQuery(QSqlQuery("SELECT type FROM ContactType;", sql));
        contactTypesModel->query().exec();
        insertCommissionerQuery = new QSqlQuery("INSERT INTO "
            "Commissioner(name, notes) VALUES (?, ?);", sql);
        insertCommissionQuery = new QSqlQuery("INSERT INTO "
            "Commission(commissioner, dueDate, createDate, paidDate) "
            "VALUES (?, ?, ?, ?);", sql);
        insertContactTypeQuery = new QSqlQuery("INSERT INTO "
            "ContactType(type) VALUES (?);", sql);
        insertContactQuery = new QSqlQuery("INSERT INTO"
            "Contact(commissioner, type, entry) VALUES(?, ?, ?);", sql);
        insertPaymentTypeQuery = new QSqlQuery("INSERT INTO"
            "PaymentType(name) VALUES (?);", sql);
        insertPaymentQuery = new QSqlQuery("INSERT INTO"
            "Payment(commission, method, fee, note, date)"
            "VALUES (?, ?, ?, ?, ?);", sql);
        insertPieceQuery = new QSqlQuery("INSERT INTO "
            "Piece(commission, product, name, description, createDate, finishDate) "
            "VALUES(?, ?, ?, ?, ?, ?);", sql);
        insertProductPriceQuery = new QSqlQuery("INSERT INTO "
            "ProductPrices(product, price, date) "
            "VALUES (?, ?, ?);", sql);
        insertProductQuery = new QSqlQuery("INSERT INTO "
            "Product(name) VALUES(?);", sql);
        paymentTypesModel = new QSqlQueryModel(this);
        paymentTypesModel->setQuery(QSqlQuery("SELECT name FROM PaymentType", sql));
        paymentTypesModel->query().exec();
        pieceEditableMapper = new QDataWidgetMapper(this);
        QSqlTableModel pieceEditableModel(this, sql);
        pieceEditableModel.setTable("Piece");
        pieceEditableMapper->setModel(&pieceEditableModel);
        pieceGeneratedMapper = new QDataWidgetMapper(this);
        QSqlQueryModel pieceGeneratedModel(this);
        pieceGeneratedMapper->setModel(&pieceGeneratedModel);
        pieceGeneratedModel.setQuery(QSqlQuery("SELECT Commissioner.name,"
            "Product.name FROM Piece"
            "INNER JOIN Product ON Piece.product = Product.id"
            "INNER JOIN Commission ON Piece.commission = Commission.id"
            "INNER JOIN Commissioner ON Commission.commissioner = Commissioner.id"
            "WHERE Piece.id = (?)", sql));
        piecesModel = new QSqlQueryModel(this);
        piecesModel->setQuery(QSqlQuery("SELECT Piece.id, Commissioner.name,"
            "Piece.name, DATETIME(Piece.createDate, 'unixepoch', 'localtime'),"
            "DATETIME(Piece.finishDate, 'unixepoch', 'localtime')"
            "FROM Piece"
            "INNER JOIN Commission ON Piece.commission = Commission.id"
            "INNER JOIN Commissioner ON Commission.commissioner = Commissioner.id;"
            "WHERE Commissioner.name LIKE (?)"
            "AND DATETIME(Piece.createDate, 'unixepoch', 'localtime') LIKE (?)"
            "AND DATETIME(Piece.finishDate, 'unixepoch', 'localtime') LIKE (?)", sql));
        searchPieces("", "", "", "");
        productsModel = new QSqlQueryModel(this);
        productsModel->setQuery(QSqlQuery("SELECT Product.id, Product.name,"
            "ProductPrices.price, COALESCE(SUM(Piece.id), 0)"
            "FROM Product"
            "LEFT JOIN ProductPrices ON Product.id = ProductPrices.product"
            "LEFT JOIN Piece ON Product.id = Piece.product"
            "WHERE Product.name LIKE (?)"
            "AND ProductPrices.price LIKE (?)"
            "GROUP BY Product.id"
            "HAVING ProductPrices.date = MAX(ProductPrices.date)"
            "AND COALESCE(SUM(Piece.id), 0) LIKE (?)", sql));
        searchProducts("", "", "");
    }
}