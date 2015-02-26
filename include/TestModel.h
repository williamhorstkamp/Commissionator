#ifndef TESTMODEL
#define TESTMODEL

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Commissionator {
    class TestModel {
    private:
        QSqlDatabase db;
        QSqlQueryModel *model;
    public:
        TestModel() {
            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(":memory:");
            db.open();
            db.exec("CREATE TABLE test (stuff INTEGER PRIMARY KEY, thing TEXT);");
            db.exec("INSERT INTO test (stuff, thing) VALUES (1, ' a thing');");
            db.exec("INSERT INTO test (stuff, thing) VALUES (2, 'just a ting');");
            db.exec("INSERT INTO test (stuff, thing) VALUES (3, 'one more row');");
            model = new QSqlQueryModel();
            model->setQuery("SELECT * FROM test");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Index"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Thing?"));
        }
        QSqlQueryModel *getModel() {
            return model;
        }
    };
}

#endif