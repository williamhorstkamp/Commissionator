#ifndef FIXEDROWTABLEDELEGATE_H
#define FIXEDROWTABLEDELEGATE_H

#include <QStyledItemDelegate>

namespace Commissionator {

    /**
     *  Class is a delegate to display buttons on a SearchTableView.
     */
    class FixedRowTableDelegate : public QStyledItemDelegate {

        Q_OBJECT

    public:       
        /**
         *  Default constructor initializes delegate
         *  
         *  @param parent - pointer to parent object
         */
        FixedRowTableDelegate(QWidget *parent = nullptr);

        /**
         *  Sets the delete message for the delegate.
         *
         *  @param deleteMessage - new delete message to be used
         */
        void setDeleteMessage(QString deleteMessage);

        /**
         *  Sets the icon to the file referenced in the QString.
         *
         *  @param iconLocation - QString containing the location of the icon
         *      on the disk
         */
        void setIcon(QString iconLocation);

        /**
         *  Sets the size of the delegate's icon
         *  Defaults to 0
         *
         *  @param newSize - size of the button's height in pixels
         */
        void setIconSize(int newSize);

        /**
         *  Overrides the default editorEvent function to handle the button.
         *
         *  @param event - pointer to the QEvent that is occuring
         *  @param model - pointer to the model the event is happening on
         *  @param option - pointer to style options
         *  @param index - model's index
         *
         *  @return - whether the event was handled or not
         */
        bool editorEvent(QEvent *event, QAbstractItemModel *model, 
            const QStyleOptionViewItem &option, const QModelIndex &index);

        /**
         *  Overrides the default paint function to draw the button.
         *
         *  @param painter - pointer to painter object that handles drawing
         *  @param option - pointer to style options
         *  @param index - index that is being drawn
         */
        void paint(QPainter *painter, const QStyleOptionViewItem &option, 
            const QModelIndex &index) const;

    private:
        int buttonSize;
        QIcon buttonIcon;
        QString deleteMessage;

    signals:
        /**
         *  Signal that is emitted when the icon has been clicked.
         *
         *  @param index - index whose button was clicked
         */
        void buttonClicked(const QModelIndex &index);
    };
}

#endif