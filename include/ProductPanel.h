#ifndef PRODUCTPANEL_H
#define PRODUCTPANEL_H

#include <QVariant>
#include "RightPanel.h"

class QSqlQueryModel;
class QVBoxLayout;
class QGridLayout;
class QLabel;
class QComboBox;
class QPushButton;
class QLineEdit;
class QDoubleSpinBox;
class QListView;
class FixedRowTableDelegate;
class FixedRowTable;

namespace Commissionator {
    class ProductPanel : public RightPanel {

        Q_OBJECT

    public:
        /**
         *  Constructor accepts QSqlQueryModels for the selected product,
         *  the options it has, and the specific pieces sold.
         *
         *  @param productsModel - QSqlQueryModel containing data about the
         *      selected product
         *  @param eventsModel - QSqlQueryModel containing data about the
         *      selected product's events
         *  @param optionsModel - QSqlQueryModel containing data about the
         *      selected product's options
         *  @param piecesSoldModel - QSqlQueryModel containing data about the
         *      selected pieces sold for the product
         */
        ProductPanel(QSqlQueryModel *productModel,
            QSqlQueryModel *eventsModel,
            //QSqlQueryModel *optionsModel,
            QSqlQueryModel *piecesSoldModel, QWidget *parent = nullptr);

    signals:
        /**
         *  Signal emit when the productEventTable's delete button is clicked.
         *  Is a fowarded to ComModel::deleteProductEvent
         *
         *  @param index - index of the ProductEvent
         */
        void deleteProductEvent(const QModelIndex &index);

        /**
         *  Signal emit when the productOptionTable's delete button is clicked.
         *  Is a fowarded to ComModel::deleteProductOption
         *
         *  @param index - index of the ProductOption
         */
        void deleteProductOption(const QModelIndex &index);

        /**
         *  Signal emit when the product's availability has been toggled.
         *
         *  @param product - id of the product
         *  @param available - whether the product is available or not
         */
        void editAvailability(const int product, const bool available);

        /**
         *  Signal emit when the product's name has been edited during the
         *  edit mode of the panel
         *
         *  @param product - id of the product
         *  @param name - new name for the product
         *  @param price - new price for the product
         */
        void edit(const int product, const QString name, const double price);

        /**
         *  Signal emit when the productOptionTable's button is clicked.
         *  Is a modification of FixedRowTable::boxQuery and is to be forwarded to
         *  ComModel::insertProductOption
         *
         *  @param product - id of the product
         *  @param name - name of the product option
         *  @param price - cost of the option per unit
         *  @param isNumeric - whether the value is a numeric value (true) or
         *      a binary value (false)
         */
        void insertProductOption(const int product, const QString name,
            const double price, const bool isNumeric);

        /**
         *  Signal emit when the productPiecesTable's button is clicked.
         *  Is a modification of FixedRowTable::boxQuery and is to be forwarded to
         *  ComModel::searchProductPieces
         *
         *  @param commissioner - commissioner name
         *  @param piece - piece name
         *  @param createDate - date the piece was created
         *  @param finishDate - date the piece was finished
         */
        void searchProductPieces(const QString commission, const QString piece,
            const QString createDate, const QString finishDate);

    public slots:
        /**
         *  Slot connects to ComModel::productChanged.
         *  Refreshes the Widgets that display the product data to match the
         *  newly selected product.
         */
        void updatePanel();

    private slots:
        /**
         *  Slot captures FixedRowTable::boxQuery from productOptionTable and
         *  emits the corresponding insertProductOption signal.
         *
         *  @param query - QList of Qvariants containing the query variables
         *  Data order:
         *  Product id, product option name, product option price, is numeric
         */
        void insertProductOptionSlot(const QList<QVariant> query);

        /**
         *  Slot captures FixedRowTable::boxQuery from productPiecesTable and
         *  emits the corresponding searchProductPieces signal.
         *
         *  @param query - QList of Qvariants containing the query variables
         *  Data order:
         *  Commissioner Name, Piece Name, Piece Create Date, Piece Finish Date
         */
        void searchProductPiecesSlot(const QList<QVariant> query);

        /**
         *  Slot toggles between the panel's edit and display modes.
         *  Has the unlockButton plugged into it.
         */
        void toggleEdit();

        /**
         *  Toggles whether a product is available or not.
         */
        void toggleAvailable();

    private:
        /**
         *  Helpers function creates buttons and connections
         */
        void createButtons();

        /**
         *  Helper function creates QLabels and QTextEdit
         */
        void createLabels();

        /**
         *  Helper function builds panel by placing widgets into the layout and applying it
         */
        void createPanel();

        /**
         *  Helper function creates tables
         *
         *  @param contactModel - QSqlQueryModel containing data about the
         *      selected commissioner's contacts
         *  @param commissionsModel - QSqlQueryModel containing data about the
         *      selected commissioner's commissions
         *  @param contactTypesModel - QSqlQueryModel containing a list of
         *      contact types
         */
        void createTables(QSqlQueryModel *eventsModel,
            //QSqlQueryModel *optionsModel,
            QSqlQueryModel *piecesSoldModel);

        QSqlQueryModel *productModel;
        QPushButton *unlockButton;
        QPushButton *availableButton;
        QLabel *productName;
        QLabel *availableLabel;
        QLineEdit *productNameEdit;
        QLabel *numberProduced;
        QLabel *basePrice;
        QDoubleSpinBox *basePriceEdit;
        QLabel *eventsLabel;
        QListView *eventsList;
        FixedRowTableDelegate *eventsDelegate;
        QLabel *optionsLabel;
        FixedRowTable *optionsTable;
        QLabel *piecesSoldLabel;
        FixedRowTable *piecesSoldTable;
    };
}

#endif