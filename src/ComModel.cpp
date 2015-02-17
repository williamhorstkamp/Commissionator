#include "ComModel.h"

namespace Commissionator {

    ComModel::ComModel() {
        SQL = new SQLiteHandler();
        SQL->createDatabase();
        build();
        prepare();
   }

    ComModel::~ComModel() {
        close();
        delete SQL;
    }

    void ComModel::save(const std::string fileName) {
        SQL->save(fileName);
    }

    void ComModel::open(const std::string fileName) {
        SQL->load(fileName);
        prepare();
    }

    void ComModel::close() {
        SQL->closeDatabase();
    }

    void ComModel::build() {
        std::string stmt = "CREATE TABLE IF NOT EXISTS ContactType("
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
            "name	TEXT NOT NULL"
            ");"
            "CREATE TABLE IF NOT EXISTS Product("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name	TEXT NOT NULL,"
            "price	REAL NOT NULL"
            ");"
            "CREATE TABLE IF NOT EXISTS Piece("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "description    TEXT,"
            "commission   INTEGER NOT NULL,"
            "product  INTEGER NOT NULL,"
            "FOREIGN KEY(commission) REFERENCES Commission(id),"
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS Commission("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "createDate	TEXT NOT NULL,"
            "dueDate TEXT NOT NULL, "
            "paidDate	TEXT,"
            "commissioner INTEGER NOT NULL,"
            "FOREIGN KEY(commissioner) REFERENCES Commissioner(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS PaymentMethod("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name	TEXT NOT NULL"
            ");"
            "CREATE TABLE IF NOT EXISTS Payment("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "commissioner	INTEGER NOT NULL,"
            "method	INTEGER NOT NULL,"
            "date	TEXT NOT NULL,"
            "fee	REAL NOT NULL,"
            "note   TEXT,"
            "FOREIGN KEY(commissioner) REFERENCES Commissioner(id),"
            "FOREIGN KEY(method) REFERENCES PaymentMethod(id)"
            ");";
            SQL->rawExec(stmt);
            SQL->rawExec("PRAGMA foreign_keys = ON;");
            SQL->rawExec("INSERT INTO Product(id, name, price) VALUES (0, 'Generic', 0)");
            SQL->rawExec("INSERT INTO Commissioner(id, name) VALUES (0, 'None')");
    }

    void ComModel::prepare() {
        SQL->prepareStatement("insertCommissioner", 
            "INSERT INTO Commissioner(name) values (?)");
        SQL->prepareStatement("deleteCommissioner", 
            "DELETE FROM Commissioner WHERE id = (?)");
        SQL->prepareStatement("setCommissionerName", 
            "UPDATE Commissioner SET name = (?) WHERE id = (?)");
        SQL->prepareStatement("getCommissioners", 
            "SELECT id, name FROM Commissioner");
        SQL->prepareStatement("getCommissioner",
            "SELECT name FROM Commissioner WHERE id = (?)");
        SQL->prepareStatement("insertContactType", 
            "INSERT INTO ContactType(type) values (?)");
        SQL->prepareStatement("deleteContactType",
            "DELETE FROM ContactType WHERE id = (?)");
        SQL->prepareStatement("setContactTypeName",
            "UPDATE ContactType SET type = (?) WHERE id = (?)");
        SQL->prepareStatement("getContactTypes", 
            "SELECT id, type FROM ContactType");
        SQL->prepareStatement("getContactType",
            "SELECT type FROM ContactType WHERE id = (?)");
        SQL->prepareStatement("insertContact",
            "INSERT INTO Contact(commissioner, type, entry) values (?, ?, ?)");
        SQL->prepareStatement("deleteContact", 
            "DELETE FROM Contact WHERE id = (?)");
        SQL->prepareStatement("setContactType",
            "UPDATE Contact SET type = (?) WHERE id = (?)");
        SQL->prepareStatement("setContactEntry",
            "UPDATE Contact SET entry = (?) WHERE id = (?)");
        SQL->prepareStatement("getContacts",
            "SELECT Contact.id, Contact.type, Contact.entry FROM Contact JOIN "
            "Commissioner ON Contact.commissioner = Commissioner.id "
            "WHERE Contact.id = (?)");
        SQL->prepareStatement("getContact",
            "SELECT commissioner, type, entry FROM Contact WHERE id = (?)");
        SQL->prepareStatement("insertProduct",
            "INSERT INTO Product(name, price) values (?, ?)");
        SQL->prepareStatement("deleteProduct",
            "DELETE FROM Product WHERE id = (?)");
        SQL->prepareStatement("setProductPrice",
            "UPDATE Product SET price = (?) WHERE id = (?)");
        SQL->prepareStatement("setProductName",
            "UPDATE Product SET name = (?) WHERE id = (?)");
        SQL->prepareStatement("getProducts",
            "SELECT id, name, price FROM Product");
        SQL->prepareStatement("getProduct",
            "SELECT name, price FROM Product WHERE id = (?)");
        SQL->prepareStatement("insertPieceWithDescription",
            "INSERT INTO Piece(commission, product, description) values (?, ?, ?)");
        SQL->prepareStatement("insertPieceWithoutDescription",
            "INSERT INTO Piece(commission, product) values (?, ?)");
        SQL->prepareStatement("deletePiece",
            "DELETE FROM Piece WHERE id = (?)");
        SQL->prepareStatement("deletePieceByCommission",
            "DELETE FROM Piece WHERE commission = (?)");
        SQL->prepareStatement("setPieceDescription",
            "UPDATE Piece SET description = (?) WHERE id = (?)");
        SQL->prepareStatement("getPieces",
            "SELECT id, commission, product, description FROM Piece");
        SQL->prepareStatement("getPiece",
            "SELECT commission, product, description FROM Piece WHERE id = (?)");
        SQL->prepareStatement("searchPieces",
            "SELECT id, commission, product, description FROM Piece "
            "WHERE description LIKE (?)");
        SQL->prepareStatement("setPiecesToGeneric",
            "UPDATE Piece SET product = 0 WHERE product = (?)");
        SQL->prepareStatement("insertCommission",
            "INSERT INTO Commission(createDate, dueDate, commissioner) VALUES (?, ?, ?)");
        SQL->prepareStatement("deleteCommission",
            "DELETE FROM Commission WHERE id = (?)");
        SQL->prepareStatement("setCommissionDueDate",
            "UPDATE Commission SET dueDate = (?) WHERE id = (?)");
        SQL->prepareStatement("setCommissionPaidDate",
            "UPDATE Commission SET paidDate = (?) WHERE id = (?)");
        SQL->prepareStatement("setCommissionToNone",
            "UPDATE Commission SET commissioner = 0 WHERE commissioner = (?)");
        SQL->prepareStatement("getCommissions",
            "SELECT id, createDate, dueDate, paidDate, commissioner FROM Commission");
        SQL->prepareStatement("getCommission",
            "SELECT createDate, dueDate, paidDate, commissioner FROM Commission WHERE id = (?)");
        SQL->prepareStatement("insertPaymentMethod",
            "INSERT INTO PaymentMethod(name) VALUES (?)");
        SQL->prepareStatement("deletePaymentMethod",
            "DELETE FROM PaymentMethod WHERE id = (?)");
        SQL->prepareStatement("setPaymentMethodName",
            "UPDATE PaymentMethod SET name = (?) WHERE id = (?)");
        SQL->prepareStatement("getPaymentMethods",
            "SELECT id, name FROM PaymentMethods");
        SQL->prepareStatement("getPaymentMethod",
            "SELECT name FROM PaymentMethod WHERE id = (?)");
        SQL->prepareStatement("insertPaymentWithNote",
            "INSERT INTO Payment(commissioner, method, date, fee, note) VALUES (?, ?, ?, ?, ?)");
        SQL->prepareStatement("insertPaymentWithoutNote",
            "INSERT INTO Payment(commissioner, method, date, fee) VALUES (?, ?, ?, ?)");
        SQL->prepareStatement("setPaymentMethod",
            "UPDATE Payment SET method = (?) WHERE id = (?)");
        SQL->prepareStatement("setPaymentDate",
            "UPDATE Payment SET date = (?) WHERE id = (?)");
        SQL->prepareStatement("setPaymentAmount",
            "UPDATE Payment SET fee = (?) WHERE id = (?)");
        SQL->prepareStatement("setPaymentCommissioner",
            "UPDATE Payment SET commissioner = (?) WHERE id = (?)");
        SQL->prepareStatement("getPayments",
            "SELECT id, commissioner, method, date, fee, note FROM Payment");
        SQL->prepareStatement("getPaymentById",
            "SELECT commissioner, method, date, fee, note FROM Payment WHERE id = (?)");
        SQL->prepareStatement("getPaymentByCommissioner",
            "SELECT id, method, date, fee, note FROM Payment WHERE commissioner = (?)");
    }

    void ComModel::insertCommissioner(const std::string comName) {
        StatementHandler *stmt = SQL->getStatement("insertCommissioner");
        stmt->bind(1, comName);
        stmt->step();
        stmt->reset();
    }

    void ComModel::deleteCommissioner(const int id) {
        if (id != 0) {  //id of 'None' commissioner
            StatementHandler *stmt = SQL->getStatement("setCommissionToNone");
            stmt->bind(1, id);
            stmt->step();
            stmt->reset();
            stmt = SQL->getStatement("deleteCommissioner");
            stmt->bind(1, id);
            stmt->step();
            stmt->reset();
        }
    }

    void ComModel::setCommissionerName(const int id, const std::string comName) {
        StatementHandler *stmt = SQL->getStatement("setCommissionerName");
        stmt->bind(1, comName);
        stmt->bind(2, id);
        stmt->step();
        stmt->reset();
    }

    const std::vector<const std::tuple<const int, const std::string>>ComModel::getCommissioners() {
        std::vector<const std::tuple<const int, const std::string>> comList;
        StatementHandler *stmt = SQL->getStatement("getCommissioners");
        while (stmt->step()) {
            comList.push_back(
                std::tuple<int, std::string>(
                stmt->getInt(0), stmt->getString(1)));
        }
        stmt->reset();
        return comList;
    }

    const std::string ComModel::getCommissioner(const int id) {
        StatementHandler *stmt = SQL->getStatement("getCommissioner");
        stmt->bind(1, id);
        stmt->step();
        std::string output(stmt->getString(0));
        stmt->reset();
        return output;
    }

    void ComModel::insertContactType(const std::string typeName) {
        StatementHandler *stmt = SQL->getStatement("insertContactType");
        stmt->bind(1, typeName);
        stmt->step();
        stmt->reset();
    }

    void ComModel::deleteContactType(const int id) {
        StatementHandler *stmt = SQL->getStatement("deleteContactType");
        stmt->bind(1, id);
        stmt->step();
        stmt->reset();
    }

    void ComModel::setContactTypeName(const int id, const std::string typeName) {
        StatementHandler *stmt = SQL->getStatement("setContactTypeName");
        stmt->bind(1, typeName);
        stmt->bind(2, id);
        stmt->step();
        stmt->reset();
    }

    const std::vector<const std::tuple<const int, const std::string> > ComModel::getContactTypes() {
        std::vector<const std::tuple<const int, const std::string>> typeList;
        StatementHandler *stmt = SQL->getStatement("getContactTypes");
        while (stmt->step()) {
            typeList.push_back(
                std::tuple<int, std::string>(
                stmt->getInt(0), stmt->getString(1)));
        }
        stmt->reset();
        return typeList;
    }

    const std::string ComModel::getContactType(const int id) {
        StatementHandler *stmt = SQL->getStatement("getContactType");
        stmt->bind(1, id);
        stmt->step();
        std::string output(stmt->getString(0));
        stmt->reset();
        return output;
    }

    void ComModel::insertContact(const int comId, const int typeId, const std::string entry) {
        StatementHandler *stmt = SQL->getStatement("insertContact");
        stmt->bind(1, comId);
        stmt->bind(2, typeId);
        stmt->bind(3, entry);
        stmt->step();
        stmt->reset();
    }

    void ComModel::deleteContact(const int id) {
        StatementHandler *stmt = SQL->getStatement("deleteContact");
        stmt->bind(1, id);
        stmt->step();
        stmt->reset();
    }

    void ComModel::setContactType(const int contactId, const int typeId) {
        StatementHandler *stmt = SQL->getStatement("setContactType");
        stmt->bind(1, typeId);
        stmt->bind(2, contactId);
        stmt->step();
        stmt->reset();
    }

    void ComModel::setContactEntry(const int contactId, const std::string entry) {
        StatementHandler *stmt = SQL->getStatement("setContactEntry");
        stmt->bind(1, entry);
        stmt->bind(2, contactId);
        stmt->step();
        stmt->reset();
    }

    const std::vector<const std::tuple<const int, const int, const std::string>> ComModel::
        getContacts(const int comId) {
        std::vector<const std::tuple<const int, const int, const std::string>> contactList;
        StatementHandler *stmt = SQL->getStatement("getContacts");
        stmt->bind(1, comId);
        while (stmt->step()) {
            contactList.push_back(
                std::tuple<int, int, std::string>(
                stmt->getInt(0), stmt->getInt(1), stmt->getString(2)));
        }
        stmt->reset();
        return contactList;
    }

    const std::tuple<const int, const int, const std::string> ComModel::
        getContact(const int id) {
        StatementHandler *stmt = SQL->getStatement("getContact");
        stmt->bind(1, id);
        stmt->step();
        std::tuple<int, int, std::string> contactInfo(
            stmt->getInt(0), stmt->getInt(1), stmt->getString(2));
        stmt->reset();
        return contactInfo;
    }

    void ComModel::insertProduct(const std::string name, const double price) {
        StatementHandler *stmt = SQL->getStatement("insertProduct");
        stmt->bind(1, name);
        stmt->bind(2, price);
        stmt->step();
        stmt->reset();
    }

    void ComModel::deleteProduct(const int id) {
        if (id != 0) {  //HERESY! A magic number? SQL value of generic product - deleting it would be bad
            StatementHandler *stmt = SQL->getStatement("setPiecesToGeneric");
            stmt->bind(1, id);
            stmt->step();
            stmt->reset();
            stmt = SQL->getStatement("deleteProduct");
            stmt->bind(1, id);
            stmt->step();
            stmt->reset();
        }
    }

    void ComModel::setProductPrice(const int id, const double price) {
        StatementHandler *stmt = SQL->getStatement("setProductPrice");
        stmt->bind(1, price);
        stmt->bind(2, id);
        stmt->step();
        stmt->reset();
    }

    void ComModel::setProductName(const int id, const std::string name) {
        StatementHandler *stmt = SQL->getStatement("setProductName");
        stmt->bind(1, name);
        stmt->bind(2, id);
        stmt->step();
        stmt->reset();
    }

    const std::vector<const std::tuple<const int, const std::string, const double>> ComModel::
        getProducts() {
        std::vector<const std::tuple<const int, const std::string, const double>> products;
        StatementHandler *stmt = SQL->getStatement("getProducts");
        while (stmt->step()) {
            products.push_back(
                std::tuple<int, std::string, double>(
                stmt->getInt(0), stmt->getString(1), stmt->getDouble(2)));
        }
        stmt->reset();
        return products;
    }

    const std::tuple<const std::string, const double> ComModel::getProduct(const int id) {
        StatementHandler *stmt = SQL->getStatement("getProduct");
        stmt->bind(1, id);
        stmt->step();
        std::tuple<std::string, double> product(
                stmt->getString(0), stmt->getDouble(1));
        stmt->reset();
        return product;
    }

    void ComModel::insertPiece(const int commissionId, const int productId,
        const std::string description ) {
        StatementHandler *stmt = SQL->getStatement("insertPieceWithDescription");
        stmt->bind(1, commissionId);
        stmt->bind(2, productId);
        stmt->bind(3, description);
        stmt->step();
        stmt->reset();
    }

    void ComModel::insertPiece(const int commissionId, const int productId) {
        StatementHandler *stmt = SQL->getStatement("insertPieceWithoutDescription");
        stmt->bind(1, commissionId);
        stmt->bind(2, productId);
        stmt->step();
        stmt->reset();
    }

    void ComModel::deletePiece(const int id) {
        StatementHandler *stmt = SQL->getStatement("deletePiece");
        stmt->bind(1, id);
        stmt->step();
        stmt->reset();
    }

    void ComModel::deletePieceByCommission(const int id) {
        StatementHandler *stmt = SQL->getStatement("deletePieceByCommission");
        stmt->bind(1, id);
        stmt->step();
        stmt->reset();
    }

    void ComModel::setPieceDescription(const int id, const std::string description) {
        StatementHandler *stmt = SQL->getStatement("setPieceDescription");
        stmt->bind(1, description);
        stmt->bind(2, id);
        stmt->step();
        stmt->reset();
    }

    const std::vector<const std::tuple<const int, const int, const int, const std::string>> ComModel::
        getPieces() {
        std::vector<const std::tuple<const int, const int, const int, const std::string>> pieces;
        StatementHandler *stmt = SQL->getStatement("getPieces");
        while (stmt->step()) {
            pieces.push_back(
                std::tuple<int, int, int, std::string>(
                stmt->getInt(0), stmt->getInt(1), stmt->getInt(2),
                stmt->getString(3)));
        }
        stmt->reset();
        return pieces;
    }

    const std::tuple<const int, const int, const std::string>
        ComModel::getPiece(const int id) {
        StatementHandler *stmt = SQL->getStatement("getPiece");
        stmt->bind(1, id);
        stmt->step();
        std::tuple<int, int, std::string> piece(stmt->getInt(0), stmt->getInt(1), stmt->getString(2));
        stmt->reset();
        return piece;
    }

    const std::vector<const std::tuple<const int, const int, const int, const std::string>> ComModel::
        searchPieces(const std::string description) {
        std::vector<const std::tuple<const int, const int, const int, const std::string>> pieces;
        StatementHandler *stmt = SQL->getStatement("searchPieces");
        stmt->bind(1, "%" + description + "%");
        while (stmt->step()) {
            pieces.push_back(
                std::tuple<int, int, int, std::string>(
                stmt->getInt(0), stmt->getInt(1), stmt->getInt(2),
                stmt->getString(3)));
        }
        stmt->reset();
        return pieces;
    }


    void ComModel::insertCommission(const int commissioner, const std::string createDate, const std::string dueDate) {
        StatementHandler *stmt = SQL->getStatement("insertCommission");
        stmt->bind(1, createDate);
        stmt->bind(2, dueDate);
        stmt->bind(3, commissioner);
        stmt->step();
        stmt->reset();
    }

    void ComModel::deleteCommission(const int id) {
        StatementHandler *stmt = SQL->getStatement("deleteCommission");
        stmt->bind(1, id);
        stmt->step();
        stmt->reset();
    }

    void ComModel::setCommissionDueDate(const int id, const std::string dueDate) {
        StatementHandler *stmt = SQL->getStatement("setCommissionDueDate");
        stmt->bind(1, dueDate);
        stmt->bind(2, id);
        stmt->step();
        stmt->reset();
    }

    void ComModel::setCommissionPaidDate(const int id, const std::string paidDate) {
        StatementHandler *stmt = SQL->getStatement("setCommissionPaidDate");
        stmt->bind(1, paidDate);
        stmt->bind(2, id);
        stmt->step();
        stmt->reset();
    }

    const std::vector<const std::tuple<const int, const int, const std::string,
        const std::string, const std::string >> ComModel::getCommissions() {
        std::vector<const std::tuple<const int, const int, const std::string,
            const std::string, const std::string >> commissions;
        StatementHandler *stmt = SQL->getStatement("getCommissions");
        while (stmt->step()) {
            commissions.push_back(
                std::tuple<int, int, std::string, std::string, std::string>(
                stmt->getInt(0), stmt->getInt(4), stmt->getString(1), 
                stmt->getString(2), stmt->getString(3)));
        }
        stmt->reset();
        return commissions;
    }

    const std::tuple<const int, const std::string, const std::string, 
        const std::string> ComModel::getCommission(const int id) {
        StatementHandler *stmt = SQL->getStatement("getCommission");
        stmt->bind(1, id);
        stmt->step();
        std::tuple<int, std::string, std::string, std::string> commission(
            stmt->getInt(3), stmt->getString(0), stmt->getString(1), 
            stmt->getString(2));
        stmt->reset();
        return commission;
    }
}