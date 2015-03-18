#ifndef INSERTTABLEVIEW_H
#define INSERTTABLEVIEW_H

#include "SearchTableView.h"

namespace Commissionator {
    /**
     *  
     */
    class InsertTableView : public SearchTableView {

        Q_OBJECT

    public:
        InsertTableView(QAbstractItemModel *model);
        //~InsertTableView();

    protected:
        void createConnections();

        void createProxy();

        void init();

        QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) Q_DECL_OVERRIDE;

        void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) Q_DECL_OVERRIDE;

        void updateSearchBoxGeometry();

    signals:
        void insertSignal(const QList<QVariant> insertQuery);

        void iconClicked(const QModelIndex &index);
    };
}

#endif