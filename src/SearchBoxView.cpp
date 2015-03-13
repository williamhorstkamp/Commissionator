#include <QKeyEvent>
#include <QHeaderView>
#include "SearchBoxView.h"

namespace Commissionator {

    SearchBoxView::SearchBoxView(QWidget *parent) : QTableView(parent) {
    }

    void SearchBoxView::setModel(SearchProxyModel *model) {
        QTableView::setModel(model);
        
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
        if (event->key() == Qt::Key_Return) {
            setCurrentIndex(indexAt(QPoint(0, 0)));
            //edit(indexAt(QPoint(0, 0)));
            ((SearchProxyModel *)model())->search();
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
}