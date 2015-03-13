#include <QApplication>
#include <QMouseEvent>
#include "SearchTableDelegate.h"

namespace Commissionator {

    SearchTableDelegate::SearchTableDelegate(QObject *parent) : QItemDelegate(parent){
    }

    bool SearchTableDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) {
        if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mEvent = (QMouseEvent*)event;
            QRect rect = option.rect;
            int x = rect.left() + rect.width() - 30;
            if (mEvent->x() > x && mEvent->x() < x + 16 && mEvent->y() > rect.top() && mEvent->y() < rect.top() + 16) {
                return true;
            }
            return QItemDelegate::editorEvent(event, model, option, index);
        }
    }

    void SearchTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        if (index.column() == index.model()->columnCount() - 1) {
            QStyleOptionButton button;
            QRect r = option.rect;
            button.rect = QRect(r.left() + r.width() - 16, r.top(), 16, 16);

            button.icon = QIcon(":/Delete.png");
            button.state = QStyle::State_Enabled;
            button.iconSize = QSize(12, 12);

            QApplication::style()->drawControl(QStyle::CE_PushButton, &button, painter);
        } //else
            QItemDelegate::paint(painter, option, index);
    }
}