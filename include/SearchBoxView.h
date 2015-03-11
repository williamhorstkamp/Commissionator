#ifndef SEARCHBOXVIEW_H
#define SEARCHBOXVIEW_H

#include "SearchProxyModel.h"
#include <QTableView>

namespace Commissionator {
    class SearchBoxView : public QTableView {

        Q_OBJECT
         
    public:
        SearchBoxView(QWidget *parent) : QTableView(parent) {};
        void setModel(SearchProxyModel *model);

    protected:
        void keyPressEvent(QKeyEvent *event);
        void mousePressEvent(QMouseEvent *event);

    private:
        SearchProxyModel *proxy;
        /**
        QModelIndex previousIndex(QModelIndex oldIndex);
        QModelIndex nextIndex(QModelIndex oldIndex);

    protected slots:
        void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
        */
    };
}

#endif