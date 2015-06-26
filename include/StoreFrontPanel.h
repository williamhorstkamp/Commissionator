#ifndef STOREFRONTPANEL_H
#define STOREFRONTPANEL_H

#include <QWidget>
#include <QVariant>

class QLabel;
class QVBoxLayout;
class QSqlQueryModel;
class QPushButton;
class FixedRowTable;
class QFrame;

namespace Commissionator {
    /**
     *  Class represents the storefront left panel. 
     */
    class StoreFrontPanel : public QWidget {
        Q_OBJECT

    public:
        /**
        *  Constructor takes initializes Panel.
        *
        *   @param productsModel - pointer to list of productgs
        *   @param parent - pointer to parent widget
        */
        StoreFrontPanel(QSqlQueryModel *productsModel, QWidget *parent = nullptr);

    signals:
        /**
         *  Signal that is thrown when when one of the SearchTableDelegate
         *  icons in the product table was clicked.
         *  Is a forwarded version of SearchTableDelegate::iconClicked
         *
         *   @param index - index whose button was clicked and that should
         *      be deleted
         */
        void productDelete(const QModelIndex &index);

        /**
         *  Signal that is sent whenever the product table has been clicked on.
         *  Used to updated the various right panels based on the user's input
         *  to the StoreFront panel.
         *
         *  @param index - reference to the index that was clicked by the user
         */
        void productTableClicked(const QModelIndex &index);

        /**
         *  Signal that contains the search query.
         *  Is a forwarded version of SearchProxyModel::searchSignal
         *
         *  @param searchQuery - QList of QVariants containing the search query
         */
        void productSearch(const QList<QVariant> searchQuery);

    private:
        /**
         *  Initializes the panels various labels
         */
        void createLabels();

        /**
         *  Initializes the panels title based on the given model.
         *
         *  @param model - pointer to the model to set the table view to
         */
        void createTables(QSqlQueryModel *productModel);

        QVBoxLayout *layout;
        QLabel *titleLabel;
        QFrame *line;
        QLabel *productLabel;
        FixedRowTable *productTable;
        QPushButton *insertProductButton;
        
    };
}
#endif