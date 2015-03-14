#include <QApplication>
#include <QMouseEvent>
#include <QDialog>
#include "SearchTableDelegate.h"

namespace Commissionator {

    SearchTableDelegate::SearchTableDelegate(QObject *parent) : 
        QItemDelegate(parent) {
        buttonSize = 0;
    }

    void SearchTableDelegate::setIconSize(int newSize) {
        buttonSize = newSize;
    }

    bool SearchTableDelegate::editorEvent(QEvent *event, 
        QAbstractItemModel *model, const QStyleOptionViewItem &option, 
        const QModelIndex &index) {
        if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mEvent = (QMouseEvent*)event;
            QRect rect = option.rect;
            int x = rect.left() + rect.width() - buttonSize;
            if (mEvent->x() > x && mEvent->x() < x + buttonSize && 
                mEvent->y() > rect.top() &&
                mEvent->y() < rect.top() + buttonSize) {
                emit iconClicked(index);
                return true;
            } else
                return QItemDelegate::editorEvent(event, model, option, index);
        }
    }

    void SearchTableDelegate::paint(QPainter *painter,
        const QStyleOptionViewItem &option, const QModelIndex &index) const {
        if (index.column() == index.model()->columnCount() - 1) {
            QStyleOptionButton button;
            QRect rect = option.rect;
            button.rect = QRect(rect.left() + rect.width() - buttonSize, 
                rect.top() + (rect.height() - buttonSize) / 2,
                buttonSize, 
                buttonSize);

            button.icon = QIcon(":/Delete.png");
            
            button.state = QStyle::State_Enabled;
            button.iconSize = QSize(buttonSize * 0.9, buttonSize * 0.9);

            QApplication::style()->drawControl(QStyle::CE_PushButton,
                &button, 
                painter);
        }
        QItemDelegate::paint(painter, option, index);
    }
}