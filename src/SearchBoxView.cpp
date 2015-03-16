#include <QKeyEvent>
#include <QHeaderView>
#include "SearchBoxView.h"

namespace Commissionator {

    SearchBoxView::SearchBoxView(QWidget *parent) : QTableView(parent) {
        setFocusPolicy(Qt::NoFocus);
        horizontalHeader()->hide();
        verticalHeader()->hide();
        verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setHorizontalScrollMode(ScrollPerPixel);

        show();
    }

    void SearchBoxView::setModel(SearchProxyModel *model) {
        QTableView::setModel(model);   
        for (int row = 1; row < this->model()->rowCount(); row++)
            setRowHidden(row, true);
    }
    
    void SearchBoxView::mousePressEvent(QMouseEvent *event) {
        if (event->button() == Qt::LeftButton) {
            QModelIndex index = indexAt(event->pos());
            setCurrentIndex(indexAt(event->pos()));
            edit(index);
        }
        QTableView::mousePressEvent(event);
    }

    void SearchBoxView::scrollTo(const QModelIndex &index, ScrollHint hint) {
        QTableView::scrollTo(indexAt(QPoint(0, index.column())), hint);
    }

    void SearchBoxView::wheelEvent(QWheelEvent */**event*/) {
    }

    void SearchBoxView::closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint) {
        QTableView::closeEditor(editor, hint);
        if (hint == QAbstractItemDelegate::SubmitModelCache) {
            ((SearchProxyModel *)model())->search();
        }
    }
}