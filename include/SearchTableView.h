#ifndef SEARCHTABLEVIEW_H
#define SEARCHTABLEVIEW_H

#include <QTableView>

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

    private:
        QTableView *searchBox;
        void init();
        void updateSearchBoxGeometry();

    private slots:
        void updateSectionWidth(int logicalIndex, int oldSize, int newSize);
        void updateSectionHeight(int logicalIndex, int oldSize, int newSize);
    };
}
#endif