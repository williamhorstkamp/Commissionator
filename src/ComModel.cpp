#include <QSqlQuery>
#include "ComModel.h"

namespace Commissionator {
    ComModel::ComModel(QObject *parent) : QObject(parent) {
        sql = new QSqlDatabase();
    }

    ComModel::~ComModel() {
        delete sql;
    }

    void ComModel::newRecord() {
        build();
        prepare();
    }

    QSqlQueryModel *ComModel::getCommissions() {

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
            "note   TEXT NOT NULL,"
            "FOREIGN KEY(commissioner) REFERENCES Commissioner(id),"
            "FOREIGN KEY(method) REFERENCES PaymentMethod(id)"
            ");");
        //needs to add generics (product, commissioner, ?)
    }

    void ComModel::prepare() {
        commissionsModel = new QSqlQueryModel(this);
        QSqlQuery commissionsQuery = QSqlQuery("SELECT Commission.id, "
            "Commissioner.name, Commission.createDate, Commission.paidDate, "
            "Commission.dueDate, COUNT(Piece.id), MAX(Piece.finishDate) "
            "FROM Commission INNER JOIN "
            "Commissioner ON Commission.Commissioner = Commissioner.id "
            "INNER JOIN Piece ON Commission.id = Piece.commission "
            "WHERE Commissioner.name LIKE (?) AND "
            "Commission.createDate LIKE (?) AND "
            "Commission.paidDate LIKE (?) AND Commission.dueDate LIKE (?) "
            "GROUP BY Commission.id "
            "HAVING COUNT(Piece.id) LIKE (?) AND "
            "MAX(Piece.finishDate) LIKE (?)");
    }
}