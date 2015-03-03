#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QVBoxLayout>
#include <QTableView>
#include <QSqlRelationalTableModel>
#include <QList>
#include <QLabel>

namespace Commissionator {
    class LeftPanel :public QWidget {
        Q_OBJECT

    private:
        QVBoxLayout *layout;
        QTableView *view;
        QLabel *titleLabel;

        void createTitle(QString title);
        void createTable(QSqlTableModel *model, QList<int> hiddenColumns);
    public:
        LeftPanel(QString title, QSqlTableModel *model, QList<int> hiddenColumns);
    signals:
        void tableClicked(const QModelIndex &index);
    };
}
#endif