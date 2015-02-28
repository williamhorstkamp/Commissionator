#ifndef TESTLAYOUTS
#define TESTLAYOUTS

#include <QLabel>
#include <QLayout>
#include <QStandardItemModel>
#include <QTableView>
#include <QtSql\QSqlDatabase>
#include <QtSql\QSqlQuery>
#include <QSQLQueryModel>
#include <QListView>

namespace Commissionator {

    class LeftPanel :public QWidget {

        Q_OBJECT

    private:
        QVBoxLayout *layout;
        QTableView *view;
    public:
        LeftPanel(QSqlQueryModel *model) {
            layout = new QVBoxLayout();
            view = new QTableView(); 
            view->setModel(model);
            view->setSelectionBehavior(QAbstractItemView::SelectRows);
            layout->addWidget(new QLabel("This should be a table"));
            layout->addWidget(view);
            setLayout(layout);
            connect(view, &QTableView::clicked, this, &LeftPanel::tableClicked);
        }
    signals:
        void tableClicked(const QModelIndex &index);
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

        Q_OBJECT

    private:
        QHBoxLayout *layout;
        QListView *view;
    public:
        RightPanel(QSqlQueryModel *model) {
            layout = new QHBoxLayout();
            view = new QListView();
            view->setModel(model);
            layout->addWidget(new QLabel("Here is some data:"));
            layout->addWidget(view);
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