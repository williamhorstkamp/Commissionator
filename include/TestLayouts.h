#ifndef TESTLAYOUTS
#define TESTLAYOUTS

#include <QLabel>
#include <QLayout>
#include <QStandardItemModel>
#include <QTableView>
#include <QtSql\QSqlDatabase>
#include <QtSql\QSqlQuery>
#include <QSQLQueryModel>

namespace Commissionator {

    class LeftPanel :public QWidget {

    private:
        QVBoxLayout *layout;
    public:
        LeftPanel() {
            layout = new QVBoxLayout();
            QSqlDatabase db;
            db = QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName(":memory:");
            db.open();
            db.exec("CREATE TABLE test (stuff INTEGER PRIMARY KEY, thing TEXT);");
            db.exec("INSERT INTO test (stuff, thing) VALUES (1, ' a thing');");
            db.exec("INSERT INTO test (stuff, thing) VALUES (2, 'just a ting');");
            db.exec("INSERT INTO test (stuff, thing) VALUES (3, 'one more row');");
            QSqlQueryModel *model = new QSqlQueryModel();
            model->setQuery("SELECT * FROM test");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Index"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Thing?"));
            QTableView *view = new QTableView();
            view->setModel(model);
            view->setSelectionBehavior(QAbstractItemView::SelectRows);
            layout->addWidget(new QLabel("This should be a table"));
            layout->addWidget(view);
            setLayout(layout);
        }
    };

    class LeftPanel2 :public QWidget {
    private:
        QHBoxLayout *layout;
    public:
        LeftPanel2() {
            layout = new QHBoxLayout();
            layout->addWidget(new QLabel("Who another horizontal one?"));
            layout->addWidget(new QLabel("this has to look hilariously bad"));
            setLayout(layout);
        }
    };

    class RightPanel :public QWidget {
    private:
        QHBoxLayout *layout;
    public:
        RightPanel() {
            layout = new QHBoxLayout();
            layout->addWidget(new QLabel("These things are horizontal"));
            layout->addWidget(new QLabel("This probably looks awful"));
            setLayout(layout);
        }
    };

    class RightPanel2 :public QWidget {
    private:
        QHBoxLayout *layout;
    public:
        RightPanel2() {
            layout = new QHBoxLayout();
            layout->addWidget(new QLabel("Woah, stuff"));
            layout->addWidget(new QLabel("New testing stuff"));
            setLayout(layout);
        }
    };
}
#endif