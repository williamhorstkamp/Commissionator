//#include "InsertProxyModel.h"
#include "InsertTableView.h"

namespace Commissionator {
    InsertTableView::InsertTableView(QAbstractItemModel *model) : SearchTableView(model) {
    }

    //InsertTableView::~InsertTableView() {
    //}

    void InsertTableView::createConnections() {
    }

    void InsertTableView::createProxy() {
        //proxy = new InsertProxyModel(this);
    }

    void InsertTableView::init() {
        SearchTableView::init();
    }

    QModelIndex InsertTableView::moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) {
        QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);
        if (current.row() == model()->rowCount() - 1)
            return QModelIndex();
        return current;
    }

    void InsertTableView::scrollTo(const QModelIndex &index, ScrollHint hint) {
        if (index.row() > model()->rowCount() - 1)
            QTableView::scrollTo(index, hint);
    }

    void InsertTableView::updateSearchBoxGeometry() {
        //searchBox->setGeometry()
        SearchTableView::updateSearchBoxGeometry();
    }
}