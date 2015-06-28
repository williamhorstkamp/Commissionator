#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include "ComModel.h"

namespace Commissionator {
    ComModel::ComModel(QObject *parent) : QObject(parent) {
        changesMade = false;
        sql = new QSqlDatabase();
    }

    ComModel::~ComModel() {
        close();
        delete deleteCommissionerQuery;
        delete deleteCommissionQuery;
        delete deleteContactQuery;
        delete deletePieceQuery;
        delete editCommissionCommissionerQuery;
        delete editCommissionNotesQuery;
        delete editCommissionerNameQuery;
        delete editCommissionerNotesQuery;
        delete editProductAvailabilityQuery;
        delete editProductNameQuery;
        delete editProductPriceQuery;
        delete insertCommissionerQuery;
        delete insertCommissionQuery;
        delete insertContactQuery;
        delete insertContactTypeQuery;
        delete insertPaymentQuery;
        delete insertPaymentTypeQuery;
        delete insertPieceQuery;
        delete insertProductQuery;
        delete sql;
    }

    bool ComModel::hasBeenChanged() {
        return changesMade;
    }

    void ComModel::close() {
        sql->exec("ROLLBACK TO SAVEPOINT sv");
        cleanupQueries();
        QString connection = sql->connectionName();
        sql->close();
        sql = new QSqlDatabase();
        QSqlDatabase::removeDatabase(connection);
        emit recordClosed();
    }

    void ComModel::open(QString fileName, bool newFile) {
        if (sql->isOpen())
            close();;
        *sql = QSqlDatabase::addDatabase("QSQLITE");
        sql->setDatabaseName(fileName);
        sql->open();

        if (newFile) {
            build();
            prepareModels();

            //this is test data that only exists because the user can not currently enter this data
            insertContactType("Contact Type");
            insertContactType("Contact Type 2");
            insertContactType("Contact Type 3");
            insertPaymentType("payment type");
            insertPaymentType("payment type 2");
            insertPaymentType("payment type 3");
        } else
            prepareModels();

        sql->exec("SAVEPOINT sv");
        changesMade = false;
        emit recordOpened();
    }
    
    void ComModel::save() {
        if (changesMade){
            sql->exec("RELEASE SAVEPOINT sv");
            sql->exec("SAVEPOINT sv");
            changesMade = false;
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

    QSqlQueryModel *ComModel::getCommissionerNames() {
        return commissionerNamesModel;
    }

    QSqlQueryModel *ComModel::getCommissioners() {
        return commissionersModel;
    }

    QSqlQueryModel *ComModel::getCommissionPayments() {
		return commissionPaymentsModel;
    }

    QSqlQueryModel *ComModel::getCommissionPieces() {
        return commissionPiecesModel;
    }

    QSqlQueryModel *ComModel::getCommission() {
        return commissionModel;
    }

    QSqlQueryModel *ComModel::getCommissionList() {
        return commissionListModel;
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

    QSqlQueryModel *ComModel::getProduct() {
        return productModel;
    }

    QSqlQueryModel *ComModel::getProducts() {
        return productsModel;
    }

    QSqlQueryModel *ComModel::getProductNames() {
        return productNamesModel;
    }

    QSqlQueryModel *ComModel::getProductPiecesSold() {
        return productPiecesModel;
    }

    void ComModel::editCommissionCommissioner(const int commission,
        const int commissioner) {
        editCommissionCommissionerQuery->bindValue(0, commissioner);
        editCommissionCommissionerQuery->bindValue(1, commission);
        editCommissionCommissionerQuery->exec();
        refreshCommissions();
        refreshCommissioners();
        changesMade = true;
    }

    void ComModel::editCommissionNotes(const int commission, 
        const QString notes) {
        editCommissionNotesQuery->bindValue(0, notes);
        editCommissionNotesQuery->bindValue(1, commission);
        editCommissionNotesQuery->exec();
        refreshCommissions();
        changesMade = true;
    }

    void ComModel::editCommissionerName(const int commissioner, const QString name) {
        editCommissionerNameQuery->bindValue(0, name);
        editCommissionerNameQuery->bindValue(1, commissioner);
        editCommissionerNameQuery->exec();
        refreshCommissioners();
        refreshCommissions();
        changesMade = true;
    }

    void ComModel::editCommissionerNotes(const int commissioner, const QString notes) {
        editCommissionerNotesQuery->bindValue(0, notes);
        editCommissionerNotesQuery->bindValue(1, commissioner);
        editCommissionerNotesQuery->exec();
        refreshCommissioners();
        changesMade = true;
    }

    void ComModel::editProductAvailability(const int productId, 
        const bool available) {
        editProductAvailabilityQuery->bindValue(0, available);
        editProductAvailabilityQuery->bindValue(1, productId);
        editProductAvailabilityQuery->exec();
        refreshProducts();
    }

    void ComModel::editProductPrice(const int productId, const double basePrice) {
        editProductPriceQuery->bindValue(0, productId);
        editProductPriceQuery->bindValue(1, basePrice);
        editProductPriceQuery->bindValue(2,
            QDateTime::currentDateTime().toMSecsSinceEpoch());
        editProductPriceQuery->exec();
        refreshProducts();
        changesMade = true;
    }

    void ComModel::editProductName(const int productId, const QString name) {
        editProductNameQuery->bindValue(0, name);
        editProductNameQuery->bindValue(1, productId);
        editProductNameQuery->exec();
        refreshProducts();
        changesMade = true;
    }

    void ComModel::searchCommissioners(const QString name, const QString dateOldest,
        const QString balance, const QString notes) {
        commissionersModel->query().bindValue(0, "%" + name + "%");
        commissionersModel->query().bindValue(1, "%" + dateOldest + "%");
        commissionersModel->query().bindValue(2, "%" + balance + "%");
        commissionersModel->query().bindValue(3, "%" + notes + "%");
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
        int comId = getValue(index, 0).toInt();
        commissionModel->query().bindValue(0, comId);
        commissionModel->query().exec();
        commissionModel->setQuery(commissionModel->query());
        commissionPaymentsModel->query().bindValue(0, comId);
        commissionPaymentsModel->query().exec();
        commissionPaymentsModel->setQuery(commissionPaymentsModel->query());
        commissionPiecesModel->query().bindValue(0, comId);
        commissionPiecesModel->query().exec();
        commissionPiecesModel->setQuery(commissionPiecesModel->query());
        emit commissionChanged();
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
        emit commissionerChanged();
    }

    void ComModel::setPiece(const QModelIndex &index) {
        pieceModel->query().bindValue(0, getValue(index, 0).toInt());
        pieceModel->query().exec();
        pieceModel->setQuery(pieceModel->query());  
        emit pieceChanged();
    }
    
    void ComModel::setProduct(const QModelIndex &index) {
        int proId = getValue(index, 0).toInt();
        productModel->query().bindValue(0, proId);
        productModel->query().exec();
        productModel->setQuery(productModel->query());
        productPiecesModel->query().bindValue(0, proId);
        productPiecesModel->query().exec();
        productPiecesModel->setQuery(productPiecesModel->query());
        emit productChanged();
    }

    void ComModel::deleteCommission(const QModelIndex &index) {
        deleteCommissionQuery->bindValue(0, getValue(index, 0));
        deleteCommissionQuery->exec();
        refreshCommissioners();
        refreshCommissions();
        changesMade = true;
    }

    void ComModel::deleteCommissioner(const QModelIndex &index) {
        deleteCommissionerQuery->bindValue(0, getValue(index, 0));
        deleteCommissionerQuery->exec();
        refreshCommissioners();
        refreshCommissions();
        changesMade = true;
    }

    void ComModel::deleteContact(const QModelIndex &index) {
        deleteContactQuery->bindValue(0, getValue(index, 0));
        deleteContactQuery->exec();
        refreshContacts();
        changesMade = true;
    }

    void ComModel::deletePiece(const QModelIndex &index) {
        deletePieceQuery->bindValue(0, getValue(index, 0));
        deletePieceQuery->exec();
        refreshCommissioners();
        refreshCommissions();
        refreshPieces();
        changesMade = true;
    }

    void ComModel::deleteProduct(const QModelIndex &index) {
        editProductAvailability(getValue(index, 0).toInt(), false);
    }

    int ComModel::insertCommission(const int commissionerId, 
        const QDateTime dueDate, const QString notes) {
        insertCommissionQuery->bindValue(0, commissionerId);
        insertCommissionQuery->bindValue(1, dueDate.toMSecsSinceEpoch());
        insertCommissionQuery->bindValue(2, notes);
        insertCommissionQuery->bindValue(3, 
            QDateTime::currentDateTime().toMSecsSinceEpoch());
        insertCommissionQuery->exec();
        refreshCommissions();
        refreshCommissioners();
        changesMade = true;
        return insertCommissionQuery->lastInsertId().toInt();
    }

    void ComModel::insertCommissioner(const QString commissionerName,
        const QString commissionerNotes) {
        insertCommissionerQuery->bindValue(0, commissionerName);
        insertCommissionerQuery->bindValue(1, commissionerNotes);
        insertCommissionerQuery->exec();
        refreshCommissioners();
        changesMade = true;
    }

    void ComModel::insertContact(const int commissionerId,
        const int contactType, const QString contactEntry) {
        if (contactEntry != "") {
            insertContactQuery->bindValue(0, commissionerId);
            insertContactQuery->bindValue(1, contactType);
            insertContactQuery->bindValue(2, contactEntry);
            insertContactQuery->exec();
        }
        refreshContacts();
        changesMade = true;
    }

    void ComModel::insertContactType(const QString contactTypeName) {
        insertContactTypeQuery->bindValue(0, contactTypeName);
        insertContactTypeQuery->exec();
        refreshContactTypes();
        changesMade = true;
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
        refreshPayments();
        refreshCommissions();
        refreshCommissioners();
        changesMade = true;
    }

    void ComModel::insertPaymentType(const QString typeName) {
        insertPaymentTypeQuery->bindValue(0, typeName);
        insertPaymentTypeQuery->exec();
        refreshPaymentTypes();
        changesMade = true;
    }

    void ComModel::insertPiece(const int commission, const int product,
        const QString name, const QString description, 
        const double overridePrice) {
        insertPieceQuery->bindValue(0, commission);
        insertPieceQuery->bindValue(1, product);
        insertPieceQuery->bindValue(2, name);
        insertPieceQuery->bindValue(3, description);
        insertPieceQuery->bindValue(4, QDateTime::currentDateTime().toMSecsSinceEpoch());
        insertPieceQuery->bindValue(5, QVariant(QVariant::String));
        if (overridePrice > -1)
            insertPieceQuery->bindValue(6, overridePrice);
        else
            insertPieceQuery->bindValue(6, QVariant(QVariant::Double));
        insertPieceQuery->exec();
        refreshCommissioners();
        refreshCommissions();
        refreshPieces();
        changesMade = true;
    }

    void ComModel::insertProduct(const QString productName, const double basePrice) {
        insertProductQuery->bindValue(0, productName);
        insertProductQuery->exec();
        QSqlQuery lastId("SELECT last_insert_rowid();", *sql);
        lastId.exec();
        lastId.first();
        editProductPrice(lastId.value(0).toInt(), basePrice);
        changesMade = true;
    }

    void ComModel::insertRefund(const int commissionId, const double refundAmount,
        const QString refundNotes) {
        insertPayment(commissionId, 0, -refundAmount, refundNotes);
    }

    void ComModel::build() {
        QSqlDatabase::database().transaction();
        sql->exec("PRAGMA foreign_keys = ON;");
        sql->exec("PRAGMA synchronous = OFF;");
        sql->exec("CREATE TABLE IF NOT EXISTS ContactType("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "type	TEXT NOT NULL"
            ");");
        sql->exec("CREATE TABLE IF NOT EXISTS Contact("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "commissioner   INTEGER NOT NULL, "
            "type	INTEGER NOT NULL, "
            "entry	TEXT NOT NULL, "
            "FOREIGN KEY(type) REFERENCES ContactType(id), "
            "FOREIGN KEY(commissioner) REFERENCES Commissioner(id)"
            ");");
        sql->exec("CREATE TABLE IF NOT EXISTS Commissioner("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name	TEXT NOT NULL, "
            "notes  TEXT "
            ");");
        sql->exec("CREATE TABLE IF NOT EXISTS Product("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name	TEXT NOT NULL, "
            "available INTEGER(1) NOT NULL"
            ");");
        sql->exec("CREATE TABLE IF NOT EXISTS ProductEvent("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "product INTEGER NOT NULL, "
            "position INTEGER NOT NULL, "
            "name TEXT NOT NULL, "
            "FOREIGN KEY(product) REFERENCES Product(id), "
            "CONSTRAINT propos UNIQUE(product, position))");
        sql->exec("CREATE TABLE IF NOT EXISTS ProductPrices("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "product INTEGER NOT NULL, "
            "price REAL NOT NULL, "
            "date TEXT NOT NULL, "
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");");
        sql->exec("CREATE TABLE IF NOT EXISTS ProductOption("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name	TEXT NOT NULL, "
            "price	REAL NOT NULL, "
            "isInt	INTEGER(1) NOT NULL, "
            "product	INTEGER NOT NULL, "
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");");
        sql->exec("CREATE TABLE IF NOT EXISTS ProductOptionPrices("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "productOption INTEGER NOT NULL, "
            "price REAL NOT NULL, "
            "date TEXT NOT NULL, "
            "FOREIGN KEY(productOption)REFERENCES ProductOption(id)"
            ");");
        sql->exec("CREATE TABLE IF NOT EXISTS Piece("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name   TEXT NOT NULL, "
            "commission   INTEGER NOT NULL, "
            "product  INTEGER NOT NULL, "
            "createDate TEXT NOT NULL, "
            "finishDate TEXT, "
            "notes TEXT NOT NULL, "
            "overridePrice REAL, "
            "FOREIGN KEY(commission) REFERENCES Commission(id), "
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");");
        sql->exec("CREATE TABLE IF NOT EXISTS PieceEvent("
            "piece INTEGER NOT NULL, "
            "event INTEGER NOT NULL, "
            "finishDate INTEGER NOT NULL, "
            "FOREIGN KEY(piece) REFERENCES piece(id), "
            "FOREIGN KEY(event) REFERENCES ProductEvent(id), "
            "CONSTRAINT pieve UNIQUE(piece, event))");
        sql->exec("CREATE TABLE IF NOT EXISTS PieceOption("
            "field	TEXT NOT NULL, "
            "piece	INTEGER NOT NULL, "
            "option	INTEGER NOT NULL, "
            "FOREIGN KEY(piece) REFERENCES Piece(id), "
            "FOREIGN KEY(option) REFERENCES ProductOption(id)"
            ");");
        sql->exec("CREATE TABLE IF NOT EXISTS Commission("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "createDate	TEXT NOT NULL, "
            "dueDate TEXT NOT NULL, "
            "paidDate	TEXT, "
            "commissioner INTEGER NOT NULL, "
            "notes TEXT NOT NULL, "
            "FOREIGN KEY(commissioner) REFERENCES Commissioner(id)"
            ");");
        sql->exec("CREATE TABLE IF NOT EXISTS PaymentType("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name	TEXT NOT NULL, "
            "deleted INTEGER(1) NOT NULL"
            ");");
        sql->exec("CREATE TABLE IF NOT EXISTS Payment("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "commission	INTEGER NOT NULL, "
            "method	INTEGER NOT NULL, "
            "date	TEXT NOT NULL, "
            "fee	REAL NOT NULL, "
            "note   TEXT NOT NULL, "
            "FOREIGN KEY(commission) REFERENCES Commission(id), "
            "FOREIGN KEY(method) REFERENCES PaymentType(id)"
            ");");
        sql->exec("INSERT INTO Commissioner(id, name, notes) "
            "VALUES(0, 'Deleted', '');");
        sql->exec("INSERT INTO Commission(id, createDate, dueDate, "
            "commissioner, notes) "
            "VALUES(0, 0, 0, 0, '');");
        sql->exec("INSERT INTO PaymentType(id, name, deleted) "
            "VALUES(0, 'Refund', 0);");
        sql->exec("CREATE TRIGGER IF NOT EXISTS deleteCommissionerContacts "
            "AFTER DELETE ON Commissioner "
            "FOR EACH ROW "
            "BEGIN "
            "DELETE FROM Contact WHERE commissioner = OLD.id; "
            "END");
        sql->exec("CREATE TRIGGER IF NOT EXISTS updateCommissionerCommissions "
            "AFTER DELETE ON Commissioner "
            "FOR EACH ROW "
            "BEGIN "
            "UPDATE Commission SET commissioner = 0 "
            "WHERE commissioner = OLD.id; "
            "END");
        sql->exec("CREATE TRIGGER IF NOT EXISTS updateCommissionPieces "
            "AFTER DELETE ON Commission "
            "FOR EACH ROW "
            "BEGIN "
            "UPDATE Piece SET commission = 0 "
            "WHERE commission = OLD.id; "
            "END");
        sql->exec("CREATE TRIGGER IF NOT EXISTS updateCommissionPaidDateOnPayment "
            "AFTER INSERT ON Payment "
            "FOR EACH ROW BEGIN "
            "UPDATE Commission SET paidDate = STRFTIME('%s', 'now') * 1000 "
            "WHERE Commission.id = NEW.commission AND "
            "Commission.paidDate IS NULL AND "
            "(SELECT COALESCE(SUM(COALESCE(a.override, a.price)) - fee, "
            "SUM(COALESCE(a.override, a.price))) FROM Commission "
            "INNER JOIN Commissioner "
            "ON Commission.commissioner = Commissioner.id "
            "LEFT JOIN "
            "(SELECT Commission.id id, ProductPrices.price price, "
            "Piece.overridePrice override "
            "FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) a "
            "ON Commission.id = a.id "
            "LEFT JOIN "
            "(SELECT Commission.id id, SUM(Payment.fee) fee FROM Payment "
            "INNER JOIN Commission ON Payment.commission = Commission.id "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "GROUP BY Commission.id) b "
            "ON Commission.id = b.id "
            "WHERE Commission.id = NEW.commission) <= 0; "
            "END");
        sql->exec("CREATE TRIGGER IF NOT EXISTS updateCommissionPaidDateOnPiece "
            "AFTER INSERT ON Piece "
            "FOR EACH ROW BEGIN "
            "UPDATE Commission SET paidDate = NULL "
            "WHERE Commission.id = NEW.commission AND "
            "(SELECT COALESCE(SUM(COALESCE(a.override, a.price)) - fee, "
            "SUM(COALESCE(a.override, a.price))) FROM Commission "
            "INNER JOIN Commissioner "
            "ON Commission.commissioner = Commissioner.id "
            "LEFT JOIN "
            "(SELECT Commission.id id, ProductPrices.price price, "
            "Piece.overridePrice override "
            "FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) a "
            "ON Commission.id = a.id "
            "LEFT JOIN "
            "(SELECT Commission.id id, SUM(Payment.fee) fee FROM Payment "
            "INNER JOIN Commission ON Payment.commission = Commission.id "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "GROUP BY Commission.id) b "
            "ON Commission.id = b.id "
            "WHERE Commission.id = NEW.commission) > 0; "
            "END");
        QSqlDatabase::database().commit();
    }

    void ComModel::cleanupQueries() {
        commissionerCommissionsModel->query().finish();
        commissionerContactsModel->query().finish();
        commissionerModel->query().finish();
        commissionerNamesModel->query().finish();
        commissionersModel->query().finish();
        commissionModel->query().finish();
        commissionPaymentsModel->query().finish();
        commissionPiecesModel->query().finish();
        commissionsModel->query().finish();
        contactTypesModel->query().exec();
        deleteCommissionerQuery->finish();
        deleteCommissionQuery->finish();
        deleteContactQuery->finish();
        editCommissionCommissionerQuery->finish();
        editCommissionNotesQuery->finish();
        editCommissionerNameQuery->finish();
        editCommissionerNotesQuery->finish();
        insertCommissionerQuery->finish();
        insertCommissionQuery->finish();
        insertContactQuery->finish();
        insertContactTypeQuery->finish();
        insertPaymentQuery->finish();
        insertPaymentTypeQuery->finish();
        insertPieceQuery->finish();
        editProductPriceQuery->finish();
        insertProductQuery->finish();
        paymentTypesModel->query().finish();
        pieceModel->query().finish();
        piecesModel->query().finish();
        productNamesModel->query().finish();
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
        QSqlQuery commissionerCommissionsQuery(*sql);
        commissionerCommissionsQuery.prepare("SELECT strftime('%m/%d/%Y', "
            "Commission.createDate / 1000, 'unixepoch', 'localtime') 'Create Date', "
            "COALESCE(strftime('%m/%d/%Y', Commission.paidDate / 1000, "
            "'unixepoch', 'localtime'), 'Unpaid') 'Paid Date', "
            "COALESCE(SUM(COALESCE(override, price)), 'No pieces') 'Total Price', "
            "COALESCE(strftime('%m/%d/%Y', max(Piece.finishDate) / 1000, "
            "'unixepoch', 'localtime'), 'Unfinished') 'Finish Date' "
            "FROM Commission "
            "LEFT JOIN Piece ON Commission.id = Piece.commission "
            "LEFT JOIN (SELECT Piece.id pId, "
            "ProductPrices.price price, Piece.overridePrice override "
            "FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "WHERE ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) Prices "
            "ON Piece.id = Prices.pId "
            "WHERE Commission.commissioner = (?) "
            "GROUP BY Commission.id;");
        commissionerCommissionsQuery.exec();
        commissionerCommissionsModel->setQuery(commissionerCommissionsQuery);
        /**
         *  initialized as a QSqlTableModel so that any proxy models created
         *  using this model can contain editable fields.
         */
		commissionerContactsModel = new QSqlTableModel(this);
        QSqlQuery commissionerContactsQuery(*sql);
        commissionerContactsQuery.prepare("SELECT Contact.id, "
            "ContactType.type 'Contact Type', "
            "Contact.entry 'Entry' FROM Contact "
            "INNER JOIN ContactType ON Contact.type = ContactType.id "
            "WHERE Contact.commissioner = (?);");
        commissionerContactsModel->setQuery(commissionerContactsQuery);
        commissionerModel = new QSqlQueryModel(this);
        QSqlQuery commissionerQuery(*sql);
        commissionerQuery.prepare("SELECT Commissioner.id, Commissioner.name, "
            "COALESCE(STRFTIME('%m/%d/%Y', min(Commission.createDate) / 1000, "
            "'unixepoch', 'localtime'), 'No Commissions'), "
            "COALESCE(SUM(COALESCE(a.override, a.price, b.price)) - c.fee, "
            "SUM(COALESCE(a.override, a.price, b.price))), Commissioner.notes "
            "FROM Commissioner "
            "LEFT JOIN Commission ON Commissioner.id = Commission.commissioner "
            "LEFT JOIN Piece ON Commission.id = Piece.commission "
            "LEFT JOIN "
            "(SELECT Piece.id id, ProductPrices.price price, "
            "Piece.overridePrice override "
            "FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) a "
            "ON Piece.id = a.id "
            "LEFT JOIN "
            "(SELECT Piece.id id, ProductPrices.price "
            "FROM Piece "
            "LEFT JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "GROUP BY Piece.id HAVING date = min(date)) b "
            "ON Piece.id = b.id "
            "LEFT JOIN "
            "(SELECT Commission.id id, SUM(Payment.fee) fee FROM Payment "
            "INNER JOIN Commission ON Payment.commission = Commission.id "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "GROUP BY Commission.id) c "
            "ON Commission.id = c.id "
            "WHERE Commissioner.id = (?)");
        commissionerModel->setQuery(commissionerQuery);
        commissionerNamesModel = new QSqlQueryModel(this);
        QSqlQuery commissionerNamesQuery("SELECT Commissioner.id, "
            "Commissioner.name FROM Commissioner "
            "WHERE Commissioner.id IS NOT 0", *sql);
        commissionerNamesQuery.exec();
        commissionerNamesModel->setQuery(commissionerNamesQuery);
        /**
         *  initialized as a QSqlTableModel so that any proxy models created
         *  using this model can contain editable fields.
         */
        commissionersModel = new QSqlTableModel(this);
        QSqlQuery commissionersQuery(*sql);
        commissionersQuery.prepare("SELECT Commissioner.id, Commissioner.name, "
            "COALESCE(STRFTIME('%m/%d/%Y', min(Commission.createDate) / 1000, "
            "'unixepoch', 'localtime'), 'No Commissions') commissionerSince, "
            "CASE WHEN(COALESCE(SUM(COALESCE(a.override, a.price, b.price)) - c.fee, "
            "SUM(COALESCE(a.override, a.price, b.price))) < 0) THEN 'Tipped ' || "
            "- COALESCE(SUM(COALESCE(a.override, a.price, b.price)) - c.fee, "
            "SUM(COALESCE(a.override, a.price, b.price))) "
            "WHEN(SUM(b.price) IS NULL) THEN 'No Commissioned Pieces' "
            "WHEN (COALESCE(SUM(COALESCE(a.override, a.price, b.price)) - c.fee, "
            "SUM(COALESCE(a.override, a.price, b.price))) = 0) THEN 'Paid off' "
            "ELSE COALESCE(SUM(COALESCE(a.override, a.price, b.price)) - c.fee, "
            "SUM(COALESCE(a.override, a.price, b.price))) || ' owed' "
            "END as amountOwed, "
            "Commissioner.notes  FROM Commissioner "
            "LEFT JOIN Commission ON Commissioner.id = Commission.commissioner "
            "LEFT JOIN Piece ON Commission.id = Piece.commission "
            "LEFT JOIN "
            "(SELECT Piece.id id, ProductPrices.price price, "
            "Piece.overridePrice override "
            "FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) a "
            "ON Piece.id = a.id "
            "LEFT JOIN "
            "(SELECT Piece.id id, ProductPrices.price "
            "FROM Piece "
            "LEFT JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "GROUP BY Piece.id HAVING date = min(date)) b "
            "ON Piece.id = b.id "
            "LEFT JOIN "
            "(SELECT Commission.id id, SUM(Payment.fee) fee FROM Payment "
            "INNER JOIN Commission ON Payment.commission = Commission.id "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "GROUP BY Commission.id) c "
            "ON Commission.id = c.id "
            "WHERE Commissioner.id IS NOT 0 AND Commissioner.name LIKE(?) "
            "AND Commissioner.notes LIKE(?) "
            "GROUP BY Commissioner.id HAVING commissionerSince like(?) "
            "AND amountOwed LIKE(?)");
        commissionersModel->setQuery(commissionersQuery);
        searchCommissioners("", "", "", "");
        commissionersModel->setHeaderData(2, Qt::Horizontal, 
            QVariant("Customer Since"), Qt::DisplayRole);
        commissionersModel->setHeaderData(3, Qt::Horizontal,
            QVariant("Amount Owed"), Qt::DisplayRole);
        commissionModel = new QSqlQueryModel(this);
        QSqlQuery commissionQuery(*sql);
        commissionQuery.prepare("SELECT Commission.id, Commissioner.id, "
            "Commissioner.name, "
            "STRFTIME('%m/%d/%Y', min(Commission.createDate) / 1000, "
            "'unixepoch', 'localtime'), "
            "STRFTIME('%m/%d/%Y', min(Commission.paidDate) / 1000, "
            "'unixepoch', 'localtime'), "
            "STRFTIME('%m/%d/%Y', min(Commission.dueDate) / 1000, "
            "'unixepoch', 'localtime'), "
            "COALESCE(SUM(COALESCE(a.override, a.price, b.price)) - c.fee, "
            "SUM(COALESCE(a.override, a.price, b.price)), ''), "
            "Commission.notes FROM Commission "
            "LEFT JOIN Commissioner "
            "ON Commission.commissioner = Commissioner.id "
            "LEFT JOIN Piece ON Commission.id = Piece.commission "
            "LEFT JOIN "
            "(SELECT Piece.id id, ProductPrices.price price, "
            "Piece.overridePrice override "
            "FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) a "
            "ON Piece.id = a.id "
            "LEFT JOIN "
            "(SELECT Piece.id id, ProductPrices.price "
            "FROM Piece "
            "LEFT JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "GROUP BY Piece.id HAVING date = min(date)) b "
            "ON Piece.id = b.id "
            "LEFT JOIN "
            "(SELECT Commission.id id, SUM(Payment.fee) fee FROM Payment "
            "INNER JOIN Commission ON Payment.commission = Commission.id "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "GROUP BY Commission.id) c "
            "ON Commission.id = c.id "
            "WHERE Commission.id = (?)");
        commissionModel->setQuery(commissionQuery);
        commissionListModel = new QSqlQueryModel(this);
        QSqlQuery commissionListQuery("SELECT Commissioner.id,"
            "Commissioner.name || ' (' || strftime('%m/%d/%Y', "
            "Commission.createDate/1000, 'unixepoch','localtime') || ' - ' || "
            "strftime('%m/%d/%Y', Commission.dueDate / 1000, 'unixepoch', "
            "'localtime') || ') (' || COUNT(Piece.id) || ' Pieces)', "
            "COALESCE(SUM(COALESCE(a.override, a.price, b.price)) - c.fee, "
            "SUM(COALESCE(a.override, a.price, b.price))), c.fee "
            "FROM Commissioner "
            "LEFT JOIN Commission ON Commissioner.id = Commission.commissioner "
            "LEFT JOIN Piece ON Commission.id = Piece.commission "
            "LEFT JOIN "
            "(SELECT Piece.id id, ProductPrices.price price, "
            "Piece.overridePrice override FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) a "
            "ON Piece.id = a.id "
            "LEFT JOIN "
            "(SELECT Piece.id id, ProductPrices.price "
            "FROM Piece "
            "LEFT JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "GROUP BY Piece.id HAVING date = min(date)) b "
            "ON Piece.id = b.id "
            "LEFT JOIN "
            "(SELECT Commission.id id, SUM(Payment.fee) fee FROM Payment "
            "INNER JOIN Commission ON Payment.commission = Commission.id "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "GROUP BY Commission.id) c "
            "ON Commission.id = c.id "
            "WHERE Commission.id > 0 "
            "GROUP BY Commission.id", *sql);
        commissionListQuery.exec();
        commissionListModel->setQuery(commissionListQuery);
		commissionPaymentsModel = new QSqlQueryModel(this);
        QSqlQuery commissionPaymentsQuery(*sql);
        commissionPaymentsQuery.prepare("SELECT PaymentType.name as 'Payment Type', "
            "strftime('%m/%d/%Y', Payment.date/1000, 'unixepoch', 'localtime') "
            "as 'Payment Date', "
            "Payment.fee as 'Payment Amount', "
            "Payment.note as 'Notes' FROM Payment "
            "INNER JOIN PaymentType ON Payment.method = PaymentType.id "
            "WHERE Payment.commission = (?);");
        commissionPaymentsModel->setQuery(commissionPaymentsQuery);
        commissionPiecesModel = new QSqlQueryModel(this);
        QSqlQuery commissionPiecesQuery(*sql);
        commissionPiecesQuery.prepare("SELECT a.id, a.product as 'Product Name', "
            "a.name as 'Piece Name', "
            "COALESCE(b.price, a.price) as 'Price', "
            "a.createDate as 'Create Date', a.finishDate as 'Finish Date' "
            "FROM "
            "(SELECT Piece.id id, Piece.commission commission, "
            "Product.name product, Piece.name name, "
            "strftime('%m/%d/%Y', Piece.createDate / 1000, 'unixepoch', "
            "'localtime') createDate, "
            "COALESCE(Piece.finishDate, 'Unfinished') finishDate, "
            "COALESCE(Piece.overridePrice, ProductPrices.price) price "
            "FROM Piece "
            "INNER JOIN Product ON Piece.product = Product.id "
            "INNER JOIN ProductPrices ON Product.id = ProductPrices.product "
            "GROUP BY Piece.id HAVING ProductPrices.date = "
            "min(ProductPrices.date)) a "
            "LEFT JOIN "
            "(SELECT Piece.id id, "
            "COALESCE(Piece.overridePrice, ProductPrices.price) price "
            "FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) b "
            "ON a.id = b.id "
            "WHERE a.commission = (?)");
        commissionPiecesModel->setQuery(commissionPiecesQuery);
        /**
         *  initialized as a QSqlTableModel so that any proxy models created
         *  using this model can contain editable fields.
         */
        commissionsModel = new  QSqlTableModel(this);
        QSqlQuery commissionsQuery(*sql);
        commissionsQuery.prepare("SELECT Commission.id, "
            "Commissioner.name, STRFTIME('%m/%d/%Y', "
            "Commission.createDate/1000, 'unixepoch', 'localtime'), "
            "COALESCE(STRFTIME('%m/%d/%Y', Commission.paidDate/1000, "
            "'unixepoch', 'localtime'), 'Unpaid'), "
            "STRFTIME('%m/%d/%Y', Commission.dueDate/1000, 'unixepoch', "
            "'localtime'), COUNT(Piece.id), "
            "CASE WHEN MIN(Piece.finishDate) IS NULL AND COUNT(Piece.id) > 0 "
            "THEN 'Unfinished' "
            "WHEN MIN(Piece.finishDate) IS NULL AND COUNT(Piece.id) = 0 "
            "THEN 'No Pieces' "
            "ELSE MAX(Piece.finishDate) "
            "END "
            "FROM Commission INNER JOIN "
            "Commissioner ON Commission.Commissioner = Commissioner.id "
            "LEFT JOIN Piece ON Commission.id = Piece.commission "
            "WHERE Commissioner.name LIKE (?) AND "
            "Commission.createDate LIKE (?) AND "
            "COALESCE(Commission.paidDate, '') LIKE (?) "
            "AND Commission.dueDate LIKE (?) "
            "AND Commission.id NOT LIKE 0 "
            "GROUP BY Commission.id "
            "HAVING COUNT(Piece.id) LIKE (?) AND "
            "COALESCE(MAX(Piece.finishDate), '') LIKE (?);");
        commissionsModel->setQuery(commissionsQuery);
        searchCommissions("", "", "", "", "", "");
        commissionsModel->setHeaderData(1, Qt::Horizontal,
            QVariant("Commissioner"), Qt::DisplayRole);
        commissionsModel->setHeaderData(2, Qt::Horizontal,
            QVariant("Create Date"), Qt::DisplayRole);
        commissionsModel->setHeaderData(3, Qt::Horizontal,
            QVariant("Paid Date"), Qt::DisplayRole);
        commissionsModel->setHeaderData(4, Qt::Horizontal,
            QVariant("Due Date"), Qt::DisplayRole);
        commissionsModel->setHeaderData(5, Qt::Horizontal,
            QVariant("Piece Count"), Qt::DisplayRole);
        commissionsModel->setHeaderData(6, Qt::Horizontal,
            QVariant("Finish Date"), Qt::DisplayRole);
        contactTypesModel = new QSqlQueryModel(this);
        contactTypesModel->setQuery(QSqlQuery("SELECT id, type FROM ContactType;", *sql));
        contactTypesModel->query().exec();
        deleteCommissionerQuery = new QSqlQuery(*sql);
        deleteCommissionerQuery->prepare("DELETE FROM Commissioner WHERE "
            "Commissioner.id = (?);");
        deleteContactQuery = new QSqlQuery(*sql);
        deleteContactQuery->prepare("DELETE FROM Contact WHERE "
            "Contact.id = (?);");
        deleteCommissionQuery = new QSqlQuery(*sql);
        deleteCommissionQuery->prepare("DELETE FROM Commission WHERE "
            "Commission.id = (?);");
        deletePieceQuery = new QSqlQuery(*sql);
        deletePieceQuery->prepare("DELETE FROM Piece WHERE "
            "Piece.id = (?);");
        editCommissionCommissionerQuery = new QSqlQuery(*sql);
        editCommissionCommissionerQuery->prepare("UPDATE Commission "
            "SET commissioner = (?) WHERE id = (?)");
        editCommissionNotesQuery = new QSqlQuery(*sql);
        editCommissionNotesQuery->prepare("UPDATE Commission "
            "SET notes = (?) WHERE id = (?)");
        editCommissionerNameQuery = new QSqlQuery(*sql);
        editCommissionerNameQuery->prepare("UPDATE Commissioner "
            "SET name = (?) WHERE id = (?)");
        editCommissionerNotesQuery = new QSqlQuery(*sql);
        editCommissionerNotesQuery->prepare("UPDATE Commissioner "
            "SET notes = (?) WHERE id = (?)");
        editProductAvailabilityQuery = new QSqlQuery(*sql);
        editProductAvailabilityQuery->prepare("UPDATE Product "
            "SET available = (?) WHERE id = (?)");
        editProductPriceQuery = new QSqlQuery(*sql);
        editProductPriceQuery->prepare("INSERT INTO "
            "ProductPrices(product, price, date) "
            "VALUES (?, ?, ?);");
        editProductNameQuery = new QSqlQuery(*sql);
        editProductNameQuery->prepare("UPDATE Product "
            "SET name = (?) WHERE id = (?)");
        insertCommissionerQuery = new QSqlQuery(*sql);
        insertCommissionerQuery->prepare("INSERT INTO "
            "Commissioner(name, notes) VALUES (?, ?);");
        insertCommissionQuery = new QSqlQuery(*sql);
        insertCommissionQuery->prepare("INSERT INTO "
            "Commission(commissioner, dueDate, notes, createDate) "
            "VALUES (?, ?, ?, ?);");
        insertContactTypeQuery = new QSqlQuery(*sql);
        insertContactTypeQuery->prepare("INSERT INTO "
            "ContactType(type) VALUES (?);");
        insertContactQuery = new QSqlQuery(*sql);
        insertContactQuery->prepare("INSERT INTO "
            "Contact(commissioner, type, entry) VALUES(?, ?, ?);");
        insertPaymentTypeQuery = new QSqlQuery(*sql);
        insertPaymentTypeQuery->prepare("INSERT INTO "
            "PaymentType(name, deleted) VALUES (?, 0);");
        insertPaymentQuery = new QSqlQuery(*sql);
        insertPaymentQuery->prepare("INSERT INTO "
            "Payment(commission, method, fee, note, date) "
            "VALUES (?, ?, ?, ?, ?);");
        insertPieceQuery = new QSqlQuery(*sql);
        insertPieceQuery->prepare("INSERT INTO "
            "Piece(commission, product, name, notes, createDate, finishDate, overridePrice) "
            "VALUES(?, ?, ?, ?, ?, ?, ?);");
        insertProductQuery = new QSqlQuery(*sql);
        insertProductQuery->prepare("INSERT INTO "
            "Product(name, available) VALUES(?, 1);");
        paymentTypesModel = new QSqlQueryModel(this);
        paymentTypesModel->setQuery(QSqlQuery("SELECT id, name FROM PaymentType "
            "WHERE deleted = 0 AND id > 0", *sql));
        paymentTypesModel->query().exec();
        pieceModel = new QSqlQueryModel(this);
        QSqlQuery pieceQuery(*sql);
        pieceQuery.prepare("SELECT Commissioner.name, Piece.name, "
            "STRFTIME('%m/%d/%Y', Piece.createDate/1000, 'unixepoch', "
            "'localtime'), COALESCE(STRFTIME('%m/%d/%Y', Piece.finishDate/1000, "
            "'unixepoch', 'localtime'), 'Unfinished'), Piece.notes FROM Piece "
            "INNER JOIN Product ON Piece.product = Product.id "
            "INNER JOIN Commission ON Piece.commission = Commission.id "
            "INNER JOIN Commissioner ON Commission.commissioner = Commissioner.id "
            "WHERE Piece.id = (?)");
        pieceModel->setQuery(pieceQuery);
        piecesModel = new QSqlQueryModel(this);
        QSqlQuery piecesQuery(*sql);
        piecesQuery.prepare("SELECT Piece.id, Commissioner.name, "
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
            "'localtime'), 0) LIKE (?);");
        piecesModel->setQuery(piecesQuery);
        searchPieces("", "", "", "");
        productModel = new QSqlQueryModel(this);
        QSqlQuery productQuery("SELECT Product.id, Product.name, "
            "COUNT(Piece.id), ProductPrices.price, Product.available "
            "FROM Product "
            "LEFT JOIN Piece ON Product.id = Piece.product "
            "INNER JOIN ProductPrices ON Product.id = ProductPrices.product "
            "WHERE Product.id = (?) "
            "GROUP BY Product.id "
            "HAVING ProductPrices.date = MAX(ProductPrices.date);");
        productModel->setQuery(productQuery);
        productNamesModel = new QSqlQueryModel(this);
        QSqlQuery productNamesQuery("SELECT Product.id, Product.name "
            "FROM Product WHERE Product.available = 1;", *sql);
        productNamesQuery.exec();
        productNamesModel->setQuery(productNamesQuery);
        /**
         *  initialized as a QSqlTableModel so that any proxy models created
         *  using this model can contain editable fields.
         */
        productsModel = new QSqlTableModel(this);
        QSqlQuery productsQuery(*sql);
        productsQuery.prepare("SELECT Product.id, Product.name Name, "
            "ProductPrices.price Price, COUNT(DISTINCT Piece.id) "
            "AS 'Number of Pieces', "
            "CASE WHEN Product.available = 1 THEN 'Available' "
            "ELSE 'Unavailable' END AS 'Available' "
            "FROM Product "
            "LEFT JOIN ProductPrices ON Product.id = ProductPrices.product "
            "LEFT JOIN Piece ON Product.id = Piece.product "
            "WHERE Product.name LIKE (?) "
            "AND ProductPrices.price LIKE (?) "
            "GROUP BY Product.id "
            "HAVING ProductPrices.date = MAX(ProductPrices.date) "
            "AND COALESCE(COUNT(Piece.id), 0) LIKE (?);");
        productsModel->setQuery(productsQuery);
        searchProducts("", "", "");
        productPiecesModel = new QSqlQueryModel(this);
        QSqlQuery productPiecesQuery(*sql);
        productPiecesQuery.prepare("SELECT Commissioner.name AS "
            "'Commissioner', Piece.name AS 'Piece Name', "
            "STRFTIME('%m/%d/%Y', Piece.createDate/ 1000, 'unixepoch', "
            "'localtime') AS 'Create Date', "
            "COALESCE(STRFTIME('%m/%d/%Y', Piece.finishDate / 1000, "
            "'unixepoch', 'localtime'), 'Unfinished') AS 'Finish Date' "
            "FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "WHERE Piece.product = (?) "
            "GROUP BY Piece.id;");
        productPiecesModel->setQuery(productPiecesQuery);
    }

    void ComModel::refreshCommissioners() {
        commissionersModel->query().exec();
        commissionersModel->setQuery(commissionersModel->query());
        commissionerModel->query().exec();
        commissionerModel->setQuery(commissionerModel->query());
        commissionerNamesModel->query().exec();
        commissionerNamesModel->setQuery(commissionerNamesModel->query());
        emit commissionerChanged();
    }

    void ComModel::refreshCommissions() {
        commissionerCommissionsModel->query().exec();
        commissionerCommissionsModel->setQuery(commissionerCommissionsModel->query());
        commissionsModel->query().exec();
        commissionsModel->setQuery(commissionsModel->query());
        commissionModel->query().exec();
        commissionModel->setQuery(commissionModel->query());
        commissionListModel->query().exec();
        commissionListModel->setQuery(commissionListModel->query());
        emit commissionChanged();
    }

    void ComModel::refreshContacts() {
        commissionerContactsModel->query().exec();
        commissionerContactsModel->setQuery(commissionerContactsModel->query());
    }


    void ComModel::refreshContactTypes() {
        contactTypesModel->query().exec();
        contactTypesModel->setQuery(contactTypesModel->query());
    }

    void ComModel::refreshPayments() {
        commissionPaymentsModel->query().exec();
        commissionPaymentsModel->setQuery(commissionPaymentsModel->query());
    }

    void ComModel::refreshPaymentTypes() {
        paymentTypesModel->query().exec();
        paymentTypesModel->setQuery(paymentTypesModel->query());
    }

    void ComModel::refreshPieces() {
        commissionPiecesModel->query().exec();
        commissionPiecesModel->setQuery(commissionPiecesModel->query());
        pieceModel->query().exec();
        pieceModel->setQuery(pieceModel->query());
        piecesModel->query().exec();
        piecesModel->setQuery(piecesModel->query());
        emit pieceChanged();
    }

    void ComModel::refreshProducts() {
        productNamesModel->query().exec();
        productNamesModel->setQuery(productNamesModel->query());
        productsModel->query().exec();
        productsModel->setQuery(productsModel->query());
        productModel->query().exec();
        productModel->setQuery(productModel->query());
        emit productChanged();
    }
}