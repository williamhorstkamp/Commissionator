#include <QKeyEvent>
#include <QHeaderView>
#include "SearchBoxView.h"

namespace Commissionator {

    void SearchBoxView::setModel(SearchProxyModel *model) {
        proxy = model;
        QTableView::setModel(proxy);
        
        setFocusPolicy(Qt::NoFocus);
        horizontalHeader()->hide();
        verticalHeader()->hide();
        verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        setSelectionModel(selectionModel());
        setRowHeight(0, rowHeight(0));
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        for (int row = 1; row < this->model()->rowCount(); row++)
            setRowHidden(row, true);
        setHorizontalScrollMode(ScrollPerPixel);
        show();
        
    }

    void SearchBoxView::keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Return && state() != QAbstractItemView::EditingState) {
            setCurrentIndex(indexAt(QPoint(0, 0)));
            edit(indexAt(QPoint(0, 0)));
            proxy->search();
        } else
            QTableView::keyPressEvent(event);
    }
    
    void SearchBoxView::mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            QModelIndex index = indexAt(event->pos());
            setCurrentIndex(indexAt(event->pos()));
            edit(index);
        }
        QTableView::mousePressEvent(event);
    }
    /**
    QModelIndex SearchBoxView::previousIndex(QModelIndex oldIndex) {
        if (oldIndex.column() == 0)
            return indexAt(QPoint(0, model()->columnCount() - 1));
        else
            return indexAt(QPoint(0, oldIndex.column() - 1));
    }

    QModelIndex SearchBoxView::nextIndex(QModelIndex oldIndex) {
        if (oldIndex.column() == model()->columnCount() - 1)
            return indexAt(QPoint(0, 0));
        else
            return indexAt(QPoint(0, oldIndex.column() + 1));
    }

    void SearchBoxView::closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint) {
        if (hint == QAbstractItemDelegate::NoHint)
            QTableView::closeEditor(editor, QAbstractItemDelegate::SubmitModelCache);
        else if (hint == QAbstractItemDelegate::EditNextItem || hint == QAbstractItemDelegate::EditPreviousItem) {
            QModelIndex index;
            if (hint == QAbstractItemDelegate::EditNextItem)
                index = nextIndex(currentIndex());
            else
                index = previousIndex(currentIndex());
            if (!index.isValid()) {
                QTableView::closeEditor(editor, QAbstractItemDelegate::SubmitModelCache);
            } else {
                QTableView::closeEditor(editor, QAbstractItemDelegate::NoHint);
                setCurrentIndex(index);
                edit(index);
            }
        } else {
            proxy->search();
            QTableView::closeEditor(editor, hint);
        }
    }
    */
}