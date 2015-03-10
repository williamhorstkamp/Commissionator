#ifndef SEARCHTABLEVIEW_H
#define SEARCHTABLEVIEW_H

#include <QTableView>
#include "SearchProxyModel.h"

namespace Commissionator {
    class SearchTableView : public QTableView {

        Q_OBJECT

    public:
        SearchTableView(QAbstractItemModel *model);
        ~SearchTableView();

    protected:
        void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
        QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) Q_DECL_OVERRIDE;
        void scrollTo(const QModelIndex & index, ScrollHint hint = EnsureVisible) Q_DECL_OVERRIDE;
        void keyPressEvent(QKeyEvent *event);

    private:
        SearchProxyModel *proxy;
        QTableView *searchBox;

        void init();
        void updateSearchBoxGeometry();
        QModelIndex previousIndex(QModelIndex oldIndex);
        QModelIndex nextIndex(QModelIndex oldIndex);

    private slots:
        void updateSectionWidth(int logicalIndex, int oldSize, int newSize);
        void updateSectionHeight(int logicalIndex, int oldSize, int newSize);

    protected slots:
        void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
    };
}
#endif