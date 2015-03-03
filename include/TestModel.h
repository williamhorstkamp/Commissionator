#ifndef TESTMODEL
#define TESTMODEL

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QModelIndex>

namespace Commissionator {
    class TestModel:public QObject {

        Q_OBJECT

    private:
        QSqlDatabase db;
        QSqlTableModel *leftModel;
        QSqlQueryModel *rightModel;
    public slots:
        void updateRight(const QModelIndex &index) {
            rightModel->query().addBindValue(getValue(index, 0));
            rightModel->query().exec();
            rightModel->setQuery(rightModel->query());
        }
    public:
        TestModel() {
            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(":memory:");
            db.open();
            db.exec("PRAGMA foreign_keys = ON;");
            db.exec("CREATE TABLE test (stuff INTEGER PRIMARY KEY, thing TEXT);");
            db.exec("CREATE TABLE test2 (stuff INTEGER, thing TEXT);");
            db.exec("INSERT INTO test (stuff, thing) VALUES (1, 'a thing');");
            db.exec("INSERT INTO test2 (stuff, thing) VALUES (1, 'some data');");
            db.exec("INSERT INTO test2 (stuff, thing) VALUES (1, 'more data');");
            db.exec("INSERT INTO test2 (stuff, thing) VALUES (1, 'stuff everywhere');");
            db.exec("INSERT INTO test (stuff, thing) VALUES (2, 'just a ting');");
            db.exec("INSERT INTO test2 (stuff, thing) VALUES (2, 'various bits');");
            db.exec("INSERT INTO test2 (stuff, thing) VALUES (2, 'maybe a byte');");
            db.exec("INSERT INTO test (stuff, thing) VALUES (3, 'one more row');");
            db.exec("INSERT INTO test2 (stuff, thing) VALUES (3, 'stuff stuff more stuff');");
            db.exec("CREATE VIEW IF NOT EXISTS testview AS SELECT test.stuff, test.thing, count(*) FROM test2 JOIN test ON test2.stuff = test.stuff GROUP BY test.stuff");
            leftModel = new QSqlTableModel(this, db);
            leftModel->setTable("testview");
            leftModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Thing"));
            leftModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Test2 count"));
            leftModel->setEditStrategy(QSqlTableModel::OnFieldChange);
            leftModel->select();
            rightModel = new QSqlQueryModel(this);
            QSqlQuery *query = new QSqlQuery("SELECT thing FROM test2 WHERE stuff = (?)");
            rightModel->setQuery(*query);
        }
        QSqlTableModel *getLeftModel() {
            return leftModel;
        }

        QSqlQueryModel *getRightModel() {
            return rightModel;
        }

        QVariant getValue(const QModelIndex &index, int column) {
            return index.model()->data(index.model()->index(index.row(), column));
        }
    };
}

#endif