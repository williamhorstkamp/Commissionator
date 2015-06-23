#ifndef STOREFRONTPANEL_H
#define STOREFRONTPANEL_H

#include <QWidget>
#include <QVariant>

class QLabel;
class QVBoxLayout;
class QSqlQueryModel;
class QPushButton;
class FixedRowTable;

namespace Commissionator {
    /**
    *  Class represents the left panel for many of the programs viewpoints,
    *  including commissioner and commission
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
         *  Initializes the panels title label based on QString input
         *
         *  @param title - QString containing text to set the panel label to
         */
        void createTitle();

        /**
         *  Initializes the panels title based on the given model.
         *
         *  @param model - pointer to the model to set the table view to
         */
        void createTables(QSqlQueryModel *productModel);

        QVBoxLayout *layout;
        FixedRowTable *productTable;
        QPushButton *insertProductButton;
        QLabel *titleLabel;
    };
}
#endif