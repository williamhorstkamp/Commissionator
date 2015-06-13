#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QDebug>
#include "ComModel.h"

namespace Commissionator {
    ComModel::ComModel(QObject *parent) : QObject(parent) {
        changesMade = false;
        sql = QSqlDatabase();
    }

    ComModel::~ComModel() {
        close();
    }

    bool ComModel::hasBeenChanged() {
        return changesMade;
    }

    void ComModel::close() {
        sql.exec("ROLLBACK TO SAVEPOINT sv");
        cleanupQueries();
        QString connection = sql.connectionName();
        sql.close();
        sql = QSqlDatabase();
        QSqlDatabase::removeDatabase(connection);
        changesMade = false;
        emit recordClosed();
    }

    void ComModel::open(QString fileName) {
        if (sql.isOpen())
            close();
        build(fileName);
        prepareModels();
        changesMade = false;
        emit recordOpened();
    }
    
    void ComModel::save() {
        if (changesMade){
            sql.exec("RELEASE SAVEPOINT sv");
            sql.exec("SAVEPOINT sv");
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

    QSqlQueryModel *ComModel::getProducts() {
        return productsModel;
    }

    QSqlQueryModel *ComModel::getProductNames() {
        return productNamesModel;
    }

    void ComModel::editCommissionCommissioner(const int commission,
        const int commissioner) {
        editCommissionCommissionerQuery.bindValue(0, commissioner);
        editCommissionCommissionerQuery.bindValue(1, commission);
        editCommissionCommissionerQuery.exec();
        refreshCommissions();
        refreshCommissioners();
        changesMade = true;
    }

    void ComModel::editCommissionNotes(const int commission, 
        const QString notes) {
        editCommissionNotesQuery.bindValue(0, notes);
        editCommissionNotesQuery.bindValue(1, commission);
        editCommissionNotesQuery.exec();
        refreshCommissions();
        changesMade = true;
    }

    void ComModel::editCommissionerName(const int commissioner, const QString name) {
        editCommissionerNameQuery.bindValue(0, name);
        editCommissionerNameQuery.bindValue(1, commissioner);
        editCommissionerNameQuery.exec();
        refreshCommissioners();
        refreshCommissions();
        changesMade = true;
    }

    void ComModel::editCommissionerNotes(const int commissioner, const QString notes) {
        editCommissionerNotesQuery.bindValue(0, notes);
        editCommissionerNotesQuery.bindValue(1, commissioner);
        editCommissionerNotesQuery.exec();
        refreshCommissioners();
        changesMade = true;
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
        commissionModel->query().bindValue(0, getValue(index, 0).toInt());
        commissionModel->query().exec();
        commissionModel->setQuery(commissionModel->query());
        commissionPaymentsModel->query().bindValue(0, getValue(index, 0).toInt());
        commissionPaymentsModel->query().exec();
        commissionPaymentsModel->setQuery(commissionPaymentsModel->query());
        commissionPiecesModel->query().bindValue(0, getValue(index, 0).toInt());
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
    
    void ComModel::deleteCommission(const QModelIndex &index) {
        deleteCommissionQuery.bindValue(0, getValue(index, 0));
        deleteCommissionQuery.exec();
        refreshCommissioners();
        refreshCommissions();
        changesMade = true;
        emit commissionChanged();
    }

    void ComModel::deleteCommissioner(const QModelIndex &index) {
        deleteCommissionerQuery.bindValue(0, getValue(index, 0));
        deleteCommissionerQuery.exec();
        refreshCommissioners();
        changesMade = true;
        emit commissionerChanged();
    }

    void ComModel::deleteContact(const QModelIndex &index) {
        deleteContactQuery.bindValue(0, getValue(index, 0));
        deleteContactQuery.exec();
        refreshContacts();
        changesMade = true;
    }

    void ComModel::deletePiece(const QModelIndex &index) {
        deletePieceQuery.bindValue(0, getValue(index, 0));
        deletePieceQuery.exec();
        refreshCommissioners();
        refreshCommissions();
        refreshPieces();
        changesMade = true;
    }

    int ComModel::insertCommission(const int commissionerId, 
        const QDateTime dueDate, const QString notes) {
        insertCommissionQuery.bindValue(0, commissionerId);
        insertCommissionQuery.bindValue(1, dueDate.toMSecsSinceEpoch());
        insertCommissionQuery.bindValue(2, notes);
        insertCommissionQuery.bindValue(3, 
            QDateTime::currentDateTime().toMSecsSinceEpoch());
        insertCommissionQuery.exec();
        refreshCommissions();
        refreshCommissioners();
        changesMade = true;
        return insertCommissionQuery.lastInsertId().toInt();
    }

    void ComModel::insertCommissioner(const QString commissionerName,
        const QString commissionerNotes) {
        insertCommissionerQuery.bindValue(0, commissionerName);
        insertCommissionerQuery.bindValue(1, commissionerNotes);
        insertCommissionerQuery.exec();
        refreshCommissioners();
        changesMade = true;
    }

    void ComModel::insertContact(const int commissionerId,
        const int contactType, const QString contactEntry) {
        if (contactEntry != "") {
            insertContactQuery.bindValue(0, commissionerId);
            insertContactQuery.bindValue(1, contactType);
            insertContactQuery.bindValue(2, contactEntry);
            insertContactQuery.exec();
        }
        refreshContacts();
        changesMade = true;
    }

    void ComModel::insertContactType(const QString contactTypeName) {
        insertContactTypeQuery.bindValue(0, contactTypeName);
        insertContactTypeQuery.exec();
        refreshContactTypes();
        changesMade = true;
    }

    void ComModel::insertPayment(const int commissionId, const int paymentTypeId,
        const double paymentAmount, const QString paymentNotes) {
        insertPaymentQuery.bindValue(0, commissionId);
        insertPaymentQuery.bindValue(1, paymentTypeId);
        insertPaymentQuery.bindValue(2, paymentAmount);
        insertPaymentQuery.bindValue(3, paymentNotes);
        insertPaymentQuery.bindValue(4, 
            QDateTime::currentDateTime().toMSecsSinceEpoch());
        insertPaymentQuery.exec();
        refreshPayments();
        QSqlQuery wasJustPaid(sql);
        wasJustPaid.prepare("SELECT CASE WHEN Commission.paidDate IS NULL "
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
            "WHERE Commission.id = (?)");
        wasJustPaid.bindValue(0, commissionId);
        wasJustPaid.exec();
        wasJustPaid.next();
        if (wasJustPaid.value(0).toBool() == true) {
            QSqlQuery setPaidDate("UPDATE Commission SET paidDate = (?) "
                "WHERE Commission.id = (?)", sql);
            setPaidDate.bindValue(0, QDateTime::currentDateTime().toMSecsSinceEpoch());
            setPaidDate.bindValue(1, commissionId);
            setPaidDate.exec();
            
        }
        wasJustPaid.finish();
        refreshCommissions();
        refreshCommissioners();
        changesMade = true;
    }

    void ComModel::insertPaymentType(const QString typeName) {
        insertPaymentTypeQuery.bindValue(0, typeName);
        insertPaymentTypeQuery.exec();
        refreshPaymentTypes();
        changesMade = true;
    }

    void ComModel::insertPiece(const int commission, const int product,
        const QString name, const QString description, 
        const double overridePrice) {
        insertPieceQuery.bindValue(0, commission);
        insertPieceQuery.bindValue(1, product);
        insertPieceQuery.bindValue(2, name);
        insertPieceQuery.bindValue(3, description);
        insertPieceQuery.bindValue(4, QDateTime::currentDateTime().toMSecsSinceEpoch());
        insertPieceQuery.bindValue(5, QVariant(QVariant::String));
        if (overridePrice > -1)
            insertPieceQuery.bindValue(6, overridePrice);
        else
            insertPieceQuery.bindValue(6, QVariant(QVariant::Double));
        insertPieceQuery.exec();
        QSqlQuery isPaid("SELECT CASE WHEN Commission.paidDate IS NULL "
            "THEN 'false' ELSE 'true' END "
            "FROM Commission "
            "WHERE Commission.id = (?);");
        isPaid.bindValue(0, commission);
        isPaid.exec();
        isPaid.next();
        if (isPaid.value(0).toBool() == true) {
            QSqlQuery setPaidDate("UPDATE Commission SET paidDate = NULL "
                "WHERE Commission.id = (?)", sql);
            setPaidDate.bindValue(0, commission);
            setPaidDate.exec();
        }
        refreshCommissioners();
        refreshCommissions();
        refreshPieces();
        changesMade = true;
    }

    void ComModel::insertProduct(const QString productName, const double basePrice) {
        insertProductQuery.bindValue(0, productName);
        insertProductQuery.exec();
        QSqlQuery lastId("SELECT last_insert_rowid();", sql);
        lastId.exec();
        lastId.first();
        insertProductPrice(lastId.value(0).toInt(), basePrice);
        changesMade = true;
    }

    void ComModel::insertProductPrice(const int productId, const double basePrice) {
        insertProductPriceQuery.bindValue(0, productId);
        insertProductPriceQuery.bindValue(1, basePrice);
        insertProductPriceQuery.bindValue(2,
            QDateTime::currentDateTime().toMSecsSinceEpoch());
        insertProductPriceQuery.exec();
        refreshProducts();
        changesMade = true;
    }

    void ComModel::build(const QString fileName) {
        sql = QSqlDatabase::addDatabase("QSQLITE");
        sql.setDatabaseName(fileName);
        sql.open();
        sql.exec("PRAGMA foreign_keys = ON;");
        sql.exec("PRAGMA synchronous = OFF;");
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
            ");");
        sql.exec("CREATE TABLE IF NOT EXISTS Commissioner("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name	TEXT NOT NULL, "
            "notes  TEXT "
            ");");
        sql.exec("CREATE TABLE IF NOT EXISTS Product("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name	TEXT NOT NULL"
            ");");
        sql.exec("CREATE TABLE IF NOT EXISTS ProductPrices("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "product INTEGER NOT NULL, "
            "price REAL NOT NULL, "
            "date TEXT NOT NULL, "
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");");
        sql.exec("CREATE TABLE IF NOT EXISTS ProductOption("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name	TEXT NOT NULL, "
            "price	REAL NOT NULL, "
            "isInt	BOOL NOT NULL, "
            "product	INTEGER NOT NULL, "
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");");
        sql.exec("CREATE TABLE IF NOT EXISTS ProductOptionPrices("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "productOption INTEGER NOT NULL, "
            "price REAL NOT NULL, "
            "date TEXT NOT NULL, "
            "FOREIGN KEY(productOption)REFERENCES ProductOption(id)"
            ");");
        sql.exec("CREATE TABLE IF NOT EXISTS Piece("
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
        sql.exec("CREATE TABLE IF NOT EXISTS PieceOption("
            "field	TEXT NOT NULL, "
            "piece	INTEGER NOT NULL, "
            "option	INTEGER NOT NULL, "
            "FOREIGN KEY(piece) REFERENCES Piece(id), "
            "FOREIGN KEY(option) REFERENCES ProductOption(id)"
            ");");
        sql.exec("CREATE TABLE IF NOT EXISTS Commission("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT, "
            "createDate	TEXT NOT NULL, "
            "dueDate TEXT NOT NULL, "
            "paidDate	TEXT, "
            "commissioner INTEGER NOT NULL, "
            "notes TEXT NOT NULL, "
            "FOREIGN KEY(commissioner) REFERENCES Commissioner(id)"
            ");");
        sql.exec("CREATE TABLE IF NOT EXISTS PaymentType("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "name	TEXT NOT NULL"
            ");");
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
        sql.exec("INSERT INTO Commissioner(id, name, notes) "
            "VALUES(0, 'Deleted', '');");
        sql.exec("INSERT INTO Commission(id, createDate, dueDate, "
            "commissioner, notes) "
            "VALUES(0, 0, 0, 0, '');");
        sql.exec("CREATE TRIGGER IF NOT EXISTS deleteCommissionerContacts "
            "AFTER DELETE ON Commissioner "
            "FOR EACH ROW "
            "BEGIN "
            "DELETE FROM Contact WHERE commissioner = OLD.id; "
            "END");
        sql.exec("CREATE TRIGGER IF NOT EXISTS updateCommissionerCommissions "
            "AFTER DELETE ON Commissioner "
            "FOR EACH ROW "
            "BEGIN "
            "UPDATE Commission SET commissioner = 0 "
            "WHERE commissioner = OLD.id; "
            "END");
        sql.exec("CREATE TRIGGER IF NOT EXISTS updateCommissionPieces "
            "AFTER DELETE ON Commission "
            "FOR EACH ROW "
            "BEGIN "
            "UPDATE Piece SET commission = 0 "
            "WHERE commission = OLD.id; "
            "END");
        sql.exec("SAVEPOINT sv");
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
        deleteCommissionerQuery.finish();
        deleteCommissionQuery.finish();
        deleteContactQuery.finish();
        editCommissionCommissionerQuery.finish();
        editCommissionNotesQuery.finish();
        editCommissionerNameQuery.finish();
        editCommissionerNotesQuery.finish();
        insertCommissionerQuery.finish();
        insertCommissionQuery.finish();
        insertContactQuery.finish();
        insertContactTypeQuery.finish();
        insertPaymentQuery.finish();
        insertPaymentTypeQuery.finish();
        insertPieceQuery.finish();
        insertProductPriceQuery.finish();
        insertProductQuery.finish();
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
        QSqlQuery commissionerCommissionsQuery(sql);
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
        QSqlQuery commissionerContactsQuery(sql);
        commissionerContactsQuery.prepare("SELECT Contact.id, "
            "ContactType.type 'Contact Type', "
            "Contact.entry 'Entry' FROM Contact "
            "INNER JOIN ContactType ON Contact.type = ContactType.id "
            "WHERE Contact.commissioner = (?);");
        commissionerContactsModel->setQuery(commissionerContactsQuery);
        commissionerModel = new QSqlQueryModel(this);
        QSqlQuery commissionerQuery(sql);
        commissionerQuery.prepare("SELECT c.id, c.name, c.createDate, "
            "COALESCE(c.cost, ''),"
            "c.notes FROM "
            "(SELECT Commission.id id, Commissioner.name name, "
            "COALESCE(STRFTIME('%m/%d/%Y', min(Commission.createDate) / 1000, "
            "'unixepoch', 'localtime'), 'No Commissions') createDate, "
            "Commissioner.notes notes, "
            "COALESCE(SUM(COALESCE(a.override, a.price)) - fee, "
            "SUM(COALESCE(a.override, a.price))) cost "
            "FROM Commission "
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
            "WHERE Commission.id > 0 GROUP BY Commission.id) c "
            "WHERE c.id = (?)");
        commissionerModel->setQuery(commissionerQuery);
        commissionerNamesModel = new QSqlQueryModel(this);
        QSqlQuery commissionerNamesQuery("SELECT Commissioner.id, "
            "Commissioner.name FROM Commissioner "
            "WHERE Commissioner.id IS NOT 0", sql);
        commissionerNamesQuery.exec();
        commissionerNamesModel->setQuery(commissionerNamesQuery);
        /**
         *  initialized as a QSqlTableModel so that any proxy models created
         *  using this model can contain editable fields.
         */
        commissionersModel = new QSqlTableModel(this);
        QSqlQuery commissionersQuery(sql);
        commissionersQuery.prepare("SELECT c.id,  c.name, c.commissionerSince, "
            "CASE WHEN(c.cost = 0) THEN 'Paid Off' "
            "WHEN(c.cost < 0) THEN 'Tipped ' || -c.cost "
            "WHEN(c.cost IS NULL) THEN 'No Commissioned Pieces' "
            "ELSE c.cost || ' owed' END AS amountOwed, C.notes FROM "
            "(SELECT Commissioner.id id, Commissioner.name name, "
            "COALESCE(STRFTIME('%m/%d/%Y', min(Commission.createDate)/1000, "
            "'unixepoch', 'localtime'), 'No Commissions') commissionerSince, "
            "Commissioner.notes notes, "
            "COALESCE(SUM(COALESCE(a.override, a.price)) - fee, "
            "SUM(COALESCE(a.override, a.price))) cost FROM Commission "
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
            "GROUP BY Commissioner.id) b "
            "ON Commission.id = b.id "
            "WHERE Commission.id > 0 "
            "GROUP BY Commissioner.id) c "
            "WHERE name LIKE (?) AND C.id IS NOT 0 "
            "GROUP BY C.id HAVING CommissionerSince like (?) "
            "AND amountOwed like (?);");
        commissionersModel->setQuery(commissionersQuery);
        searchCommissioners("", "", "");
        commissionersModel->setHeaderData(2, Qt::Horizontal, 
            QVariant("Customer Since"), Qt::DisplayRole);
        commissionersModel->setHeaderData(3, Qt::Horizontal,
            QVariant("Amount Owed"), Qt::DisplayRole);
        commissionModel = new QSqlQueryModel(this);
        QSqlQuery commissionQuery(sql);
        commissionQuery.prepare("SELECT c.id, c.name, c.createDate, "
            "c.paidDate, c.dueDate, "
            "COALESCE(c.cost, '') amountOwed, C.notes FROM "
            "(SELECT Commission.id id, Commissioner.name name, "
            "strftime('%m/%d/%Y', Commission.createDate / 1000, 'unixepoch', "
            "'localtime') createDate, "
            "COALESCE(strftime('%m/%d/%Y',Commission.paidDate / 1000, "
            "'unixepoch', 'localtime'), 'Unpaid') paidDate, "
            "strftime('%m/%d/%Y', Commission.dueDate / 1000,  'unixepoch', "
            "'localtime') dueDate, Commission.notes notes, "
            "COALESCE(SUM(COALESCE(a.override, a.price)) - fee, "
            "SUM(COALESCE(a.override, a.price))) cost FROM Commission "
            "INNER JOIN Commissioner "
            "ON Commission.commissioner = Commissioner.id "
            "LEFT JOIN "
            "(SELECT Commission.id id, ProductPrices.price price, "
            "Piece.overridePrice override FROM Commission "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "INNER JOIN ProductPrices ON Piece.product = ProductPrices.product "
            "AND ProductPrices.date < Commission.createDate "
            "GROUP BY Piece.id HAVING date = max(date)) a "
            "ON Commission.id = a.id LEFT JOIN "
            "(SELECT Commission.id id, SUM(Payment.fee) fee FROM Payment "
            "INNER JOIN Commission ON Payment.commission = Commission.id "
            "INNER JOIN Commissioner ON "
            "Commission.commissioner = Commissioner.id "
            "GROUP BY Commissioner.id) b "
            "ON Commission.id = b.id "
            "WHERE Commission.id > 0 "
            "GROUP BY Commission.id) c "
            "WHERE c.id = (?)");
        commissionModel->setQuery(commissionQuery);
        commissionListModel = new QSqlQueryModel(this);
        QSqlQuery commissionListQuery("SELECT Commission.id, Commissioner.name "
            "|| ' (' || strftime('%m/%d/%Y', Commission.createDate/1000, 'unixepoch', "
            "'localtime') || ' - ' || "
            "strftime('%m/%d/%Y', Commission.dueDate/1000, 'unixepoch', "
            "'localtime') || ') (' || COUNT(Piece.id) ||' Pieces)' "
            "FROM Commission "
            "INNER JOIN Commissioner "
            "ON Commission.commissioner = Commissioner.id "
            "LEFT JOIN Piece ON Commission.id = Piece.commission "
            "WHERE Commission.id IS NOT 0 "
            "GROUP BY Commission.id", sql);
        commissionListQuery.exec();
        commissionListModel->setQuery(commissionListQuery);
		commissionPaymentsModel = new QSqlQueryModel(this);
        QSqlQuery commissionPaymentsQuery(sql);
        commissionPaymentsQuery.prepare("SELECT PaymentType.name as 'Payment Type', "
            "strftime('%m/%d/%Y', Payment.date/1000, 'unixepoch', 'localtime') "
            "as 'Payment Date', "
            "Payment.fee as 'Payment Amount', "
            "Payment.note as 'Notes' FROM Payment "
            "INNER JOIN PaymentType ON Payment.method = PaymentType.id "
            "WHERE Payment.commission = (?);");
        commissionPaymentsModel->setQuery(commissionPaymentsQuery);
        commissionPiecesModel = new QSqlQueryModel(this);
        QSqlQuery commissionPiecesQuery(sql);
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
        QSqlQuery commissionsQuery(sql);
        commissionsQuery.prepare("SELECT Commission.id, "
            "Commissioner.name, STRFTIME('%m/%d/%Y', "
            "Commission.createDate/1000, 'unixepoch', 'localtime'), "
            "COALESCE(STRFTIME('%m/%d/%Y', Commission.paidDate/1000, "
            "'unixepoch', 'localtime'), 'Unpaid'), "
            "STRFTIME('%m/%d/%Y', Commission.dueDate/1000, 'unixepoch', 'localtime'), "
            "COUNT(Piece.id), "
            "CASE WHEN MIN(Piece.finishDate) LIKE '0' THEN 'Unfinished' "
            "WHEN MIN(Piece.finishDate) IS NULL THEN 'No Pieces' "
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
        contactTypesModel->setQuery(QSqlQuery("SELECT id, type FROM ContactType;", sql));
        contactTypesModel->query().exec();
        deleteCommissionerQuery = QSqlQuery(sql);
        deleteCommissionerQuery.prepare("DELETE FROM Commissioner WHERE "
            "Commissioner.id = (?);");
        deleteContactQuery = QSqlQuery(sql);
        deleteContactQuery.prepare("DELETE FROM Contact WHERE "
            "Contact.id = (?);");
        deleteCommissionQuery = QSqlQuery(sql);
        deleteCommissionQuery.prepare("DELETE FROM Commission WHERE "
            "Commission.id = (?);");
        deletePieceQuery = QSqlQuery(sql);
        deletePieceQuery.prepare("DELETE FROM Piece WHERE "
            "Piece.id = (?);");
        editCommissionCommissionerQuery = QSqlQuery(sql);
        editCommissionCommissionerQuery.prepare("UPDATE Commission "
            "SET commissioner = (?) WHERE id = (?)");
        editCommissionNotesQuery = QSqlQuery(sql);
        editCommissionNotesQuery.prepare("UPDATE Commission "
            "SET notes = (?) WHERE id = (?)");
        editCommissionerNameQuery = QSqlQuery(sql);
        editCommissionerNameQuery.prepare("UPDATE Commissioner "
            "SET name = (?) WHERE id = (?)");
        editCommissionerNotesQuery = QSqlQuery(sql);
        editCommissionerNotesQuery.prepare("UPDATE Commissioner "
            "SET notes = (?) WHERE id = (?)");
        insertCommissionerQuery = QSqlQuery(sql);
        insertCommissionerQuery.prepare("INSERT INTO "
            "Commissioner(name, notes) VALUES (?, ?);");
        insertCommissionQuery = QSqlQuery(sql);
        insertCommissionQuery.prepare("INSERT INTO "
            "Commission(commissioner, dueDate, notes, createDate) "
            "VALUES (?, ?, ?, ?);");
        insertContactTypeQuery = QSqlQuery(sql);
        insertContactTypeQuery.prepare("INSERT INTO "
            "ContactType(type) VALUES (?);");
        insertContactQuery =  QSqlQuery(sql);
        insertContactQuery.prepare("INSERT INTO "
            "Contact(commissioner, type, entry) VALUES(?, ?, ?);");
        insertPaymentTypeQuery = QSqlQuery(sql);
        insertPaymentTypeQuery.prepare("INSERT INTO "
            "PaymentType(name) VALUES (?);");
        insertPaymentQuery = QSqlQuery(sql);
        insertPaymentQuery.prepare("INSERT INTO "
            "Payment(commission, method, fee, note, date) "
            "VALUES (?, ?, ?, ?, ?);");
        insertPieceQuery = QSqlQuery(sql);
        insertPieceQuery.prepare("INSERT INTO "
            "Piece(commission, product, name, notes, createDate, finishDate, overridePrice) "
            "VALUES(?, ?, ?, ?, ?, ?, ?);");
        insertProductPriceQuery = QSqlQuery(sql);
        insertProductPriceQuery.prepare("INSERT INTO "
            "ProductPrices(product, price, date) "
            "VALUES (?, ?, ?);");
        insertProductQuery = QSqlQuery(sql);
        insertProductQuery.prepare("INSERT INTO "
            "Product(name) VALUES(?);");
        paymentTypesModel = new QSqlQueryModel(this);
        paymentTypesModel->setQuery(QSqlQuery("SELECT id, name FROM PaymentType", sql));
        paymentTypesModel->query().exec();
        pieceModel = new QSqlQueryModel(this);
        QSqlQuery pieceQuery(sql);
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
        QSqlQuery piecesQuery(sql);
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
        productNamesModel = new QSqlQueryModel(this);
        QSqlQuery productNamesQuery("SELECT Product.id, Product.name "
            "FROM Product;", sql);
        productNamesQuery.exec();
        productNamesModel->setQuery(productNamesQuery);
        productsModel = new QSqlQueryModel(this);
        QSqlQuery productsQuery(sql);
        productsQuery.prepare("SELECT Product.id, Product.name, "
            "ProductPrices.price, COUNT(DISTINCT Piece.id) "
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
    }

    void ComModel::refreshCommissioners() {
        commissionersModel->query().exec();
        commissionersModel->setQuery(commissionersModel->query());
        commissionerModel->query().exec();
        commissionerModel->setQuery(commissionerModel->query());
        commissionerNamesModel->query().exec();
        commissionerNamesModel->setQuery(commissionerNamesModel->query());
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
    }

    void ComModel::refreshProducts() {
        productNamesModel->query().exec();
        productNamesModel->setQuery(productNamesModel->query());
        productsModel->query().exec();
        productsModel->setQuery(productsModel->query());

    }
}