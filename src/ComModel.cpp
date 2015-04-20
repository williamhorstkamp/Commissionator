#include <QSqlQuery>
#include <QDate>
#include <QDebug>
#include "ComModel.h"

namespace Commissionator {
    ComModel::ComModel(QObject *parent) : QObject(parent) {
        newRecord();
    }

    ComModel::~ComModel() {
        close();
    }

    void ComModel::close() {
        cleanupQueries();
        QString connection = sql.connectionName();
        sql.close();
        sql = QSqlDatabase();
        QSqlDatabase::removeDatabase(connection);
    }

    void ComModel::newRecord() {
        if (sql.isOpen()) {
            //throw error
        } else {
            build();
            prepareModels();
        } 
    }
    
    QSqlQueryModel *ComModel::getCommissioner() {
        return commissionerModel;
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

    QSqlQueryModel *ComModel::getPiece() {
        return pieceModel;
    }

    QSqlQueryModel *ComModel::getPieces() {
        return piecesModel;
    }

    QSqlQueryModel *ComModel::getProducts() {
        return productsModel;
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
        commissionPaymentsModel->query().bindValue(0, getValue(index, 0).toInt());
        commissionPaymentsModel->query().exec();
        commissionPaymentsModel->setQuery(commissionPaymentsModel->query());
    }

    void ComModel::setCommissioner(const QModelIndex &index) {
        int comId = getValue(index, 0).toInt();
        commissionerModel->query().bindValue(0, comId);
        commissionerModel->query().exec();
        commissionerModel->setQuery(commissionerModel->query());
        commissionerCommissionsModel->query().bindValue(0, comId);
        commissionerCommissionsModel->query().exec();
        commissionerCommissionsModel->setQuery(commissionerCommissionsModel->query());
        commissionerContactsModel->query().bindValue(0, comId);
        commissionerContactsModel->query().exec();
        commissionerContactsModel->setQuery(commissionerContactsModel->query());
    }

    void ComModel::setPiece(const QModelIndex &index) {
        pieceModel->query().bindValue(0, getValue(index, 0).toInt());
        pieceModel->query().exec();
        pieceModel->setQuery(pieceModel->query());
    }

    void ComModel::insertCommission(const int commissionerId, 
        const QDateTime dueDate, const QString notes) {
        insertCommissionQuery->bindValue(0, commissionerId);
        insertCommissionQuery->bindValue(1, dueDate.toMSecsSinceEpoch());
        insertCommissionQuery->bindValue(2, notes);
        insertCommissionQuery->bindValue(3, 
            QDateTime::currentDateTime().toMSecsSinceEpoch());
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
        insertContactQuery->exec();
        commissionerContactsModel->query().bindValue(0, commissionerId);
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
        QSqlQuery wasJustPaid("SELECT CASE WHEN Commission.paidDate IS NULL "
            "AND totalPrices.price = sum(Payment.fee) "
            "THEN 'true' ELSE 'false' END "
            "FROM Commission "
            "LEFT JOIN(SELECT prices.com comId, SUM(prices.price) price "
            "FROM(SELECT C.id com, PP.price price FROM Commission C "
            "INNER JOIN Piece P ON C.id = P.commission "
            "INNER JOIN ProductPrices PP ON P.product = PP.product "
            "WHERE  PP.date <= C.createDate "
            "GROUP BY P.id HAVING PP.date = MAX(PP.date)) as prices "
            "GROUP BY prices.com) as totalPrices "
            "ON Commission.id = totalPrices.comId "
            "LEFT JOIN Payment ON Commission.id = Payment.commission "
            "WHERE Commission.id = (?)", sql);
        wasJustPaid.bindValue(0, commissionId);
        wasJustPaid.exec();
        wasJustPaid.next();
        qDebug() << wasJustPaid.value(0).toBool();
        if (wasJustPaid.value(0).toBool() == true) {
            QSqlQuery setPaidDate("UPDATE Commission SET paidDate = (?) "
                "WHERE Commission.id = (?)", sql);
            setPaidDate.bindValue(0, QDateTime::currentDateTime().toMSecsSinceEpoch());
            setPaidDate.bindValue(1, commissionId);
            setPaidDate.exec();
            commissionerCommissionsModel->query().exec();
            commissionerCommissionsModel->setQuery(commissionerCommissionsModel->query());
        }
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
        //insertPieceQuery->bindValue(5, 0);
        insertPieceQuery->bindValue(5, QVariant(QVariant::String));
        insertPieceQuery->exec();
        searchPieces("", "", "", "");
    }

    void ComModel::insertProduct(const QString productName, const double basePrice) {
        insertProductQuery->bindValue(0, productName);
        insertProductQuery->exec();
        QSqlQuery lastId("SELECT last_insert_rowid();", sql);
        lastId.exec();
        lastId.first();
        insertProductPrice(lastId.value(0).toInt(), basePrice);
        searchProducts("", "", "");
    }

    void ComModel::insertProductPrice(const int productId, const double basePrice) {
        insertProductPriceQuery->bindValue(0, basePrice);
        insertProductPriceQuery->bindValue(1, basePrice);
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
            "finishDate TEXT, "
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
            "paidDate	TEXT, "
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

    void ComModel::cleanupQueries() {
        commissionerCommissionsModel->query().finish();
        commissionerContactsModel->query().finish();
        commissionerModel->query().finish();
        commissionersModel->query().finish();
        commissionPaymentsModel->query().finish();
        commissionsModel->query().finish();
        contactTypesModel->query().exec();
        insertCommissionerQuery->finish();
        insertCommissionQuery->finish();
        insertContactTypeQuery->finish();
        insertContactQuery->finish();
        insertPaymentTypeQuery->finish();
        insertPaymentQuery->finish();
        insertPieceQuery->finish();
        insertProductPriceQuery->finish();
        insertProductQuery->finish();
        paymentTypesModel->query().finish();
        pieceModel->query().finish();
        piecesModel->query().finish();
        productsModel->query().finish();
    }

    QVariant ComModel::getValue(const QModelIndex &index, int column) {
        if (index.isValid())
            return index.model()->data(index.model()->index(index.row(), column));
        else
            return QVariant();
    }

    void ComModel::prepareModels() {
		commissionerCommissionsModel = new QSqlQueryModel(this);
        commissionerCommissionsModel->setQuery(QSqlQuery("SELECT createDate, "
            "paidDate, SUM(price), finishDate FROM (SELECT Commission.id comID, "
            "strftime('%m/%d/%Y', Commission.createDate/1000, "
            "'unixepoch', 'localtime') createDate, "
            "COALESCE(strftime('%m/%d/%Y', Commission.paidDate/1000, "
            "'unixepoch', 'localtime'), 'Unpaid') paidDate, "
            "ProductPrices.price price, "
            "COALESCE(strftime('%m/%d/%Y', max(Piece.finishDate)/1000, "
            "'unixepoch', 'localtime'), 'Unfinished') finishDate "
            "FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "WHERE Commissioner.id = (?) "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) "
            "GROUP BY ComID;", sql));
		commissionerContactsModel = new QSqlQueryModel(this);
        commissionerContactsModel->setQuery(QSqlQuery("SELECT ContactType.type, "
            "Contact.entry FROM Contact "
            "INNER JOIN ContactType ON Contact.type = ContactType.id "
            "WHERE Contact.commissioner = (?);", sql));
        commissionerModel = new QSqlQueryModel(this);
        commissionerModel->setQuery(QSqlQuery("SELECT C.name, "
            "min(Commission.createDate), "
            "CASE WHEN(SELECT SUM(a.price) - b.fee FROM "
            "(SELECT ProductPrices.price price FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "WHERE Commission.commissioner = C.id "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) a "
            "LEFT JOIN(SELECT SUM(Payment.fee) fee FROM Payment "
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
            "WHEN(SELECT SUM(b.fee) FROM "
            "(SELECT SUM(Payment.fee) fee FROM Payment "
            "INNER JOIN Commission ON Payment.commission = Commission.id "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "WHERE Commissioner.id = C.id) b) IS NULL THEN (SELECT SUM(a.price) FROM "
            "(SELECT ProductPrices.price price FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "WHERE Commission.commissioner = C.id "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) a) "
            "ELSE(SELECT SUM(a.price) - b.fee FROM "
            "(SELECT ProductPrices.price price FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "WHERE Commission.commissioner = C.id "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) a "
            "LEFT JOIN(SELECT SUM(Payment.fee) fee FROM Payment "
            "INNER JOIN Commission ON Payment.commission = Commission.id "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "WHERE Commissioner.id = C.id) b) "
            "END AS amountOwed, C.notes "
            "FROM Commissioner C "
            "LEFT JOIN Commission ON C.id = Commission.commissioner "
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
        searchCommissioners("", "", "");
		commissionPaymentsModel = new QSqlQueryModel(this);
        commissionPaymentsModel->setQuery(QSqlQuery("SELECT PaymentType.name, "
            "strftime('%m/%d/%Y', Payment.date/1000, 'unixepoch', 'localtime'), Payment.fee, "
            "Payment.note FROM Payment "
            "INNER JOIN PaymentType ON Payment.method = PaymentType.id "
            "WHERE Payment.commission = (?);", sql));
        commissionsModel = new QSqlQueryModel(this);
        commissionsModel->setQuery(QSqlQuery("SELECT Commission.id, "
            "Commissioner.name, STRFTIME('%m/%d/%Y', "
            "Commission.createDate/1000, 'unixepoch', 'localtime'), "
            "COALESCE(STRFTIME('%m/%d/%Y', Commission.paidDate/1000, "
            "'unixepoch', 'localtime'), 'Unpaid'), "
            "STRFTIME('%m/%d/%Y', Commission.dueDate/1000, 'unixepoch', 'localtime'), "
            "COUNT(Piece.id), "
            "CASE WHEN MIN(Piece.finishDate) LIKE '0' THEN 'Unfinished' "
            "WHEN MIN(Piece.finishDate) IS NULL THEN 'No Pieces'"
            "ELSE MAX(Piece.finishDate) "
            "END "
            "FROM Commission INNER JOIN "
            "Commissioner ON Commission.Commissioner = Commissioner.id "
            "LEFT JOIN Piece ON Commission.id = Piece.commission "
            "WHERE Commissioner.name LIKE (?) AND "
            "Commission.createDate LIKE (?) AND "
            "COALESCE(Commission.paidDate, '') LIKE (?) AND Commission.dueDate LIKE (?) "
            "GROUP BY Commission.id "
            "HAVING COUNT(Piece.id) LIKE (?) AND "
            "COALESCE(MAX(Piece.finishDate), '') LIKE (?);", sql));
        searchCommissions("", "", "", "", "", "");
        contactTypesModel = new QSqlQueryModel(this);
        contactTypesModel->setQuery(QSqlQuery("SELECT id, type FROM ContactType;", sql));
        contactTypesModel->query().exec();
        insertCommissionerQuery = new QSqlQuery("INSERT INTO "
            "Commissioner(name, notes) VALUES (?, ?);", sql);
        insertCommissionQuery = new QSqlQuery("INSERT INTO "
            "Commission(commissioner, dueDate, notes, createDate) "
            "VALUES (?, ?, ?, ?);", sql);
        insertContactTypeQuery = new QSqlQuery("INSERT INTO "
            "ContactType(type) VALUES (?);", sql);
        insertContactQuery = new QSqlQuery("INSERT INTO "
            "Contact(commissioner, type, entry) VALUES(?, ?, ?);", sql);
        insertPaymentTypeQuery = new QSqlQuery("INSERT INTO "
            "PaymentType(name) VALUES (?);", sql);
        insertPaymentQuery = new QSqlQuery("INSERT INTO "
            "Payment(commission, method, fee, note, date) "
            "VALUES (?, ?, ?, ?, ?);", sql);
        insertPieceQuery = new QSqlQuery("INSERT INTO "
            "Piece(commission, product, name, notes, createDate, finishDate) "
            "VALUES(?, ?, ?, ?, ?, ?);", sql);
        insertProductPriceQuery = new QSqlQuery("INSERT INTO "
            "ProductPrices(product, price, date) "
            "VALUES (?, ?, ?);", sql);
        insertProductQuery = new QSqlQuery("INSERT INTO "
            "Product(name) VALUES(?);", sql);
        paymentTypesModel = new QSqlQueryModel(this);
        paymentTypesModel->setQuery(QSqlQuery("SELECT id, name FROM PaymentType", sql));
        paymentTypesModel->query().exec();
        pieceModel = new QSqlQueryModel(this);
        pieceModel->setQuery(QSqlQuery("SELECT Commissioner.name, Piece.name, "
            "STRFTIME('%m/%d/%Y', Piece.createDate/1000, 'unixepoch', "
            "'localtime'), COALESCE(STRFTIME('%m/%d/%Y', Piece.finishDate/1000, "
            "'unixepoch', 'localtime'), 'Unfinished'), Piece.notes FROM Piece "
            "INNER JOIN Product ON Piece.product = Product.id "
            "INNER JOIN Commission ON Piece.commission = Commission.id "
            "INNER JOIN Commissioner ON Commission.commissioner = Commissioner.id "
            "WHERE Piece.id = (?)"));
        piecesModel = new QSqlQueryModel(this);
        piecesModel->setQuery(QSqlQuery("SELECT Piece.id, Commissioner.name, "
            "Piece.name, STRFTIME('%m/%d/%Y',Piece.createDate/1000, 'unixepoch', "
            "'localtime'), "
            "COALESCE(STRFTIME('%m/%d/%Y', Piece.finishDate/1000, 'unixepoch', "
            "'localtime'), 'Unfinished') "
            "FROM Piece "
            "INNER JOIN Commission ON Piece.commission = Commission.id "
            "INNER JOIN Commissioner ON Commission.commissioner = Commissioner.id "
            "WHERE Commissioner.name LIKE (?) "
            "AND Piece.name LIKE (?) "
            "AND STRFTIME('%m/%d/%Y', Piece.createDate/1000, 'unixepoch', 'localtime') LIKE (?) "
            "AND COALESCE(STRFTIME('%m/%d/%Y', Piece.finishDate/1000, 'unixepoch', "
            "'localtime'), 0) LIKE (?);", sql));
        searchPieces("", "", "", "");
        productsModel = new QSqlQueryModel(this);
        productsModel->setQuery(QSqlQuery("SELECT Product.id, Product.name, "
            "ProductPrices.price, COUNT(DISTINCT Piece.id) "
            "FROM Product "
            "LEFT JOIN ProductPrices ON Product.id = ProductPrices.product "
            "LEFT JOIN Piece ON Product.id = Piece.product "
            "WHERE Product.name LIKE (?) "
            "AND ProductPrices.price LIKE (?) "
            "GROUP BY Product.id "
            "HAVING ProductPrices.date = MAX(ProductPrices.date) "
            "AND COALESCE(COUNT(Piece.id), 0) LIKE (?);", sql));
        searchProducts("", "", "");
    }
}