#include "ComModel.h"

namespace Commissionator {

    ComModel::ComModel() {
        SQL = new SQLiteHandler();
    }

    ComModel::~ComModel() {
        delete SQL;
    }

    void ComModel::create(const char *fileName) {
        SQL->createDatabase(fileName);
        build();
        prepare();
    }

    void ComModel::open(const char *fileName) {
        SQL->openDatabase(fileName);
        prepare();
    }

    void ComModel::close() {
        SQL->closeDatabase();
    }

    void ComModel::build() {
        char *stmt = "CREATE TABLE IF NOT EXISTS ContactType("
            "type	TEXT PRIMARY KEY"
            ");"
            "CREATE TABLE IF NOT EXISTS Contact("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "commissioner   INTEGER NOT NULL,"
            "type	TEXT NOT NULL,"
            "entry	TEXT NOT NULL,"
            "FOREIGN KEY(type) REFERENCES ContactType(type),"
            "FOREIGN KEY(commissioner) REFERENCES Commissioner(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS Commissioner("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name	TEXT NOT NULL"
            ");"
            "CREATE TABLE IF NOT EXISTS PaymentMethod("
            "name	TEXT PRIMARY KEY"
            ");"
            "CREATE TABLE IF NOT EXISTS Commission("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "createDate	TEXT NOT NULL,"
            "paidDate	TEXT"
            ");"
            "CREATE TABLE IF NOT EXISTS Payment("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "method	TEXT NOT NULL,"
            "date	TEXT NOT NULL,"
            "fee	INTEGER NOT NULL,"
            "FOREIGN KEY(method) REFERENCES PaymentMethod(name)"
            ");"
            "CREATE TABLE IF NOT EXISTS CommissionToTransaction("
            "commission	TEXT NOT NULL,"
            "payment	TEXT NOT NULL,"
            "FOREIGN KEY(commission) REFERENCES Commission(id),"
            "FOREIGN KEY(payment) REFERENCES Payment(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS Piece("
            "id INTEGER PRIMARY KEY AUTOINCREMENT"
            ");"
            "CREATE TABLE IF NOT EXISTS Reference("
            "location TEXT PRIMARY KEY"
            ");"
            "CREATE TABLE IF NOT EXISTS PieceToReference("
            "piece INTEGER NOT NULL,"
            "reference TEXT NOT NULL,"
            "pose BOOL NOT NULL,"
            "FOREIGN KEY(piece) REFERENCES Piece(id),"
            "FOREIGN KEY(reference) REFERENCES Reference(location)"
            ");"
            "CREATE TABLE IF NOT EXISTS EventType("
            "type	TEXT PRIMARY KEY"
            ");"
            "CREATE TABLE IF NOT EXISTS Product("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name	TEXT NOT NULL,"
            "price	REAL NOT NULL"
            ");"
            "CREATE TABLE IF NOT EXISTS ProductOption("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name	TEXT NOT NULL,"
            "price	REAL NOT NULL,"
            "isInt	BOOL NOT NULL,"
            "product	INTEGER NOT NULL,"
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS PieceOptions("
            "field	TEXT NOT NULL,"
            "piece	INTEGER NOT NULL,"
            "option	INTEGER NOT NULL,"
            "FOREIGN KEY(piece) REFERENCES Piece(id),"
            "FOREIGN KEY(option) REFERENCES ProductOption(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS EventTypeToProduct("
            "type	TEXT NOT NULL,"
            "product	INTEGER NOT NULL,"
            "FOREIGN KEY(type) REFERENCES EventType(type),"
            "FOREIGN KEY(product) REFERENCES Product(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS Event("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "type	TEXT NOT NULL,"
            "commission	INTEGER NOT NULL,"
            "start	TEXT NOT NULL,"
            "end	TEXT NOT NULL,"
            "FOREIGN KEY(type) REFERENCES EventType(type),"
            "FOREIGN KEY(commission) REFERENCES Commission(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS Sale("
            "startDate 	TEXT,"
            "endDate 	TEXT,"
            "PRIMARY 	KEY(startDate, endDate)"
            ");"
            "CREATE TABLE IF NOT EXISTS Deal("
            "id	INTEGER PRIMARY KEY,"
            "startDate	TEXT NOT NULL,"
            "endDate	TEXT NOT NULL,"
            "buyProduct	INTEGER,"
            "buyOption	INTEGER,"
            "buyCount	INTEGER NOT NULL,"
            "getProduct	INTEGER,"
            "getOption	INTEGER,"
            "getCount	INTEGER NOT NULL,"
            "priceAdjustment	REAL NOT NULL,"
            "FOREIGN KEY(startDate, endDate) REFERENCES Sale(startDate, endDate)"
            "CHECK((buyProduct IS NULL and buyOption IS NOT NULL) OR"
            "(buyProduct IS NOT NULL and buyOption IS NULL))"
            "CHECK((getProduct IS NULL and getOption IS NOT NULL) OR"
            "(getProduct IS NOT NULL and getOption IS NULL))"
            "); ";

            SQL->rawExec(stmt);
    }

    void ComModel::prepare() {
        SQL->prepareStatement("insertCommissioner", "INSERT INTO Commissioner(name) values (?)");
        SQL->prepareStatement("insertContactType", "INSERT INTO ContactType(type) values (?)");
        SQL->prepareStatement("insertContact", "INSERT INTO Contact(commissioner, type, entry) values (?, ?, ?)");
    }

    void ComModel::insertCommissioner(const char *comName) {
        StatementHandler *stmt = SQL->getStatement("insertCommissioner");
        stmt->bind(1, comName);
        stmt->step();
        stmt->reset();
    }

    void ComModel::insertContactType(const char *typeName) {
        StatementHandler *stmt = SQL->getStatement("insertContactType");
        stmt->bind(1, typeName);
        stmt->step();
        stmt->reset();
    }

    void ComModel::insertContact(const char *comName, const char *typeName, const char *entry) {
        StatementHandler *stmt = SQL->getStatement("insertContact");
        stmt->bind(1, comName);
        stmt->bind(2, typeName);
        stmt->bind(3, entry);
        stmt->step();
        stmt->reset();
    }
}