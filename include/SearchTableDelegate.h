#ifndef SEARCHTABLEDELEGATE_H
#define SEARCHTABLEDELEGATE_H

#include <QItemDelegate>

namespace Commissionator {
    /**
     *  Class is a delegate to display buttons on a SearchTableView.
     */
    class SearchTableDelegate : public QItemDelegate {
        Q_OBJECT

    public:       
        /**
         *  Default constructor initializes delegate
         *  
         *  @param parent - pointer to parent object
         */
        SearchTableDelegate(QObject *parent = nullptr);

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

    signals:
        /**
         *  Signal that is emitted when the icon has been clicked.
         *
         *  @param index - index whose button was clicked
         */
        void iconClicked(const QModelIndex &index);
    };
}

#endif