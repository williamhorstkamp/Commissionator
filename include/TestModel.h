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
        QSqlQueryModel *leftModel;
        QSqlQueryModel *rightModel;
        QSqlQuery *del;
    public slots:
        void updateRight(const QModelIndex &index) {
            rightModel->query().addBindValue(getValue(index, 0));
            rightModel->query().exec();
            rightModel->setQuery(rightModel->query());
        }

        void search(const QList<QVariant> searchQuery = QList<QVariant>()) {
            if (searchQuery.isEmpty()) {
                leftModel->query().bindValue(0, QVariant("%"));
                leftModel->query().bindValue(1, QVariant("%"));
                leftModel->query().bindValue(2, QVariant(0));
            }
            else {
                if (searchQuery[0].toString() == "")
                    leftModel->query().bindValue(0, QVariant("%"));
                else
                    leftModel->query().bindValue(0, QVariant(searchQuery[0].toString()));
                leftModel->query().bindValue(1, QVariant("%" + searchQuery[1].toString() + "%"));
                leftModel->query().bindValue(2, searchQuery[2].toInt());
            }

            leftModel->query().exec();
            leftModel->setQuery(leftModel->query());
        }

        void deleteRecord(const QModelIndex &index) {
            del->addBindValue(index.model()->index(index.row(), 0).data().toInt());
            del->exec();
            search();
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
            leftModel = new QSqlTableModel(this, db);
            QSqlQuery query = QSqlQuery("SELECT test.stuff, "
            "test.thing, count(*) FROM test2 JOIN test ON "
            "test2.stuff = test.stuff WHERE test.stuff LIKE (?) AND test.thing LIKE (?) "
            "GROUP BY test.stuff having count(*) >= (?)");
            query.addBindValue(QVariant("%"));
            query.addBindValue(QVariant("%"));
            query.addBindValue(QVariant(0));

            query.exec();
            leftModel->setQuery(query);
            leftModel->query().addBindValue(QVariant(0));
            leftModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Thing"));
            leftModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Test2 count"));
            rightModel = new QSqlQueryModel(this);
            QSqlQuery query2 = QSqlQuery("SELECT thing FROM test2 WHERE stuff = (?)");
            rightModel->setQuery(query2);

            del = new QSqlQuery("DELETE FROM test WHERE stuff = (?)");
        }
        QSqlQueryModel *getLeftModel() {
            return leftModel;
        }

        QSqlQueryModel *getRightModel() {
            return rightModel;
        }

        QVariant getValue(const QModelIndex &index, int column) {
            if (index.isValid())
                return index.model()->data(index.model()->index(index.row(), column));
            else
                return QVariant();
        }
    };
}

#endif