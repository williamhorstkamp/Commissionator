#include <QKeyEvent>
#include <QHeaderView>
#include "FixedRowProxyModel.h"
#include "FixedRowTableDelegate.h"
#include "FixedRowBox.h"

namespace Commissionator {

    FixedRowBox::FixedRowBox(QWidget *parent) : QTableView(parent) {
        setFocusPolicy(Qt::NoFocus);
        horizontalHeader()->hide();
        verticalHeader()->hide();
        verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollMode(ScrollPerPixel);

        show();
    }

    void FixedRowBox::setModel(FixedRowProxyModel *model) {
        QTableView::setModel(model);   
        for (int row = 1; row < this->model()->rowCount(); row++)
            setRowHidden(row, true);
    }
    
    void FixedRowBox::mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            QModelIndex index = indexAt(event->pos());
            setCurrentIndex(indexAt(event->pos()));
            edit(index);
        }
        QTableView::mousePressEvent(event);
    }

    void FixedRowBox::scrollTo(const QModelIndex &index, ScrollHint hint) {
        QTableView::scrollTo(indexAt(QPoint(0, index.column())), hint);
    }

    void FixedRowBox::wheelEvent(QWheelEvent * /**event*/) {
    }

    void FixedRowBox::closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint) {
        QTableView::closeEditor(editor, hint);
        if (hint == QAbstractItemDelegate::SubmitModelCache) {
            emit boxQuery();
        }
    }
}