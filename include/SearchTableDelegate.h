#ifndef SEARCHTABLEDELEGATE_H
#define SEARCHTABLEDELEGATE_H

#include <QItemDelegate>

namespace Commissionator {
    class SearchTableDelegate : public QItemDelegate {
        Q_OBJECT

    public:
        SearchTableDelegate(QObject *parent = nullptr);
        void setIconSize(int newSize);
        bool editorEvent(QEvent *event, QAbstractItemModel *model, 
            const QStyleOptionViewItem &option, const QModelIndex &index);
        void paint(QPainter *painter, const QStyleOptionViewItem &option, 
            const QModelIndex &index) const;

    private:
        int buttonSize;

    signals:
        void iconClicked(const QModelIndex &index);
    };
}

#endif