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
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "type	TEXT PRIMARY KEY"
            ");"
            "CREATE TABLE IF NOT EXISTS Contact("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "commissioner   TEXT NOT NULL,"
            "type	TEXT NOT NULL,"
            "entry	TEXT NOT NULL,"
            "FOREIGN KEY(type) REFERENCES ContactType(id),"
            "FOREIGN KEY(commissioner) REFERENCES Commissioner(id)"
            ");"
            "CREATE TABLE IF NOT EXISTS Commissioner("
            "id	INTEGER PRIMARY KEY AUTOINCREMENT,"
            "name	TEXT PRIMARY KEY"
            ");";

            SQL->rawExec(stmt);
    }

    void ComModel::prepare() {
        SQL->rawExec("PRAGMA foreign_keys = ON;");
        SQL->prepareStatement("insertCommissioner", "INSERT INTO Commissioner(name) values (?)");
        SQL->prepareStatement("deleteCommissioner", "DELETE FROM Commissioner WHERE id = (?)");
        SQL->prepareStatement("renameCommissioner", "UPDATE Commissioner SET name = (?) WHERE id = (?)");
        SQL->prepareStatement("insertContactType", "INSERT INTO ContactType(type) values (?)");
        SQL->prepareStatement("deleteContactType", "DELETE FROM ContactType WHERE id = (?)");
        SQL->prepareStatement("renameContactType", "UPDATE ContactType SET type = (?) WHERE id = (?)");
        SQL->prepareStatement("insertContact", "INSERT INTO Contact(commissioner, type, entry) values (?, ?, ?)");
        SQL->prepareStatement("deleteContact", "DELETE FROM Contact WHERE id = (?)");
        SQL->prepareStatement("editContactType", "UPDATE Contact SET type = (?) WHERE id = (?)");
        SQL->prepareStatement("editContactEntry", "UPDATE Contact SET entry = (?) WHERE id = (?)");
    }

    void ComModel::insertCommissioner(const char *comName) {
        StatementHandler *stmt = SQL->getStatement("insertCommissioner");
        stmt->bind(1, comName);
        stmt->step();
        stmt->reset();
    }

    void ComModel::deleteCommissioner(const int id) {
        StatementHandler *stmt = SQL->getStatement("deleteCommissioner");
        stmt->bind(1, id);
        stmt->step();
        stmt->reset();
    }

    void ComModel::renameCommissioner(const int id, const char *comName) {
        StatementHandler *stmt = SQL->getStatement("renameCommissioner");
        stmt->bind(1, comName);
        stmt->bind(2, id);
        stmt->step();
        stmt->reset();
    }

    void ComModel::insertContactType(const char *typeName) {
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

    void ComModel::renameContactType(const int id, const char *typeName) {
        StatementHandler *stmt = SQL->getStatement("renameContactType");
        stmt->bind(1, typeName);
        stmt->bind(2, id);
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

    void ComModel::deleteContact(const int id) {
        StatementHandler *stmt = SQL->getStatement("deleteContact");
        stmt->bind(1, id);
        stmt->step();
        stmt->reset();
    }

    void ComModel::editContactType(const int contactId, const int typeId) {
        StatementHandler *stmt = SQL->getStatement("renameContactType");
        stmt->bind(1, typeId);
        stmt->bind(2, contactId);
        stmt->step();
        stmt->reset();
    }

    void ComModel::editContactEntry(const int contactId, const char *entry) {
        StatementHandler *stmt = SQL->getStatement("renameContactType");
        stmt->bind(1, entry);
        stmt->bind(2, contactId);
        stmt->step();
        stmt->reset();
    }
}