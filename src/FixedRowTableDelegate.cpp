#include <QApplication>
#include <QMouseEvent>
#include <QDialog>
#include "FixedRowTableDelegate.h"

namespace Commissionator {

    FixedRowTableDelegate::FixedRowTableDelegate(QObject *parent) :
        QStyledItemDelegate(parent) {
        buttonSize = 0;
        buttonIcon = QIcon();
    }

    void FixedRowTableDelegate::setIcon(QString iconLocation) {
        buttonIcon.addFile(iconLocation);
    }

    void FixedRowTableDelegate::setIconSize(int newSize) {
        buttonSize = newSize;
    }

    bool FixedRowTableDelegate::editorEvent(QEvent *event,
        QAbstractItemModel *model, const QStyleOptionViewItem &option, 
        const QModelIndex &index) {
        if (event->type() == QEvent::MouseButtonRelease)
            if (index.column() == index.model()->columnCount() - 1) {
                QMouseEvent *mEvent = (QMouseEvent*)event;
                QRect rect = option.rect;
                int x = rect.left() + rect.width() - buttonSize;
                if (mEvent->x() > x && mEvent->x() < x + buttonSize && 
                    mEvent->y() > rect.top() &&
                    mEvent->y() < rect.top() + buttonSize) {
                    emit buttonClicked(index);
                    return true;
                }
            }
        return QStyledItemDelegate::editorEvent(event, model, option, index);
    }

    void FixedRowTableDelegate::paint(QPainter *painter,
        const QStyleOptionViewItem &option, const QModelIndex &index) const {
        if (index.column() == index.model()->columnCount() - 1) {
            QStyleOptionButton button;
            QRect rect = option.rect;
            button.rect = QRect(rect.left() + rect.width() - buttonSize, 
                rect.top() + (rect.height() - buttonSize) / 2,
                buttonSize, 
                buttonSize);

            button.icon = buttonIcon;
            
            button.state = QStyle::State_Enabled;
            button.iconSize = QSize(buttonSize * 0.9, buttonSize * 0.9);

            QApplication::style()->drawControl(QStyle::CE_PushButton,
                &button, 
                painter);
        }
        QStyledItemDelegate::paint(painter, option, index);
    }
}