#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDataWidgetMapper>

namespace Commissionator{

    /**
     *  Class that manages the SQLite database through QSqlDatabase.
     *  Acts as the "model" in the programs MVC/MV design.
     *  Provides a set of functions making it easier for the to
     *  manipulate the database as well as request results of query functions.
     */
    class ComModel : public QObject {

        Q_OBJECT

    public:
        /**
         *  Function returns a pointer to a model containing data for the
         *  commission table to be displayed on the commission panel.
         *  Can be limited with searchCommissions(const QList<QVariant>)
         *
         *  @return - pointer to QSqlQueryModel containing commissions
         *  Display order:
         *  Index, Commissioner, Create Date, Paid Date, Due Date, 
         *  Number of Pieces, Finish Date
         */
        QSqlQueryModel *getCommissions();

        /**
         *  Function returns a pointer to a model containing data for the
         *  commissioner table to be displayed on the commissioner panel.
         *  Can be limited with searchCommissioners(const QList<QVariant>)
         *
         *  @return - pointer to QSqlQueryModel containing commissioners
         *  Display order:
         *  Index, Name, Date of Oldest Commission, Outstanding Balance
         */
        QSqlQueryModel *getCommissioners();

        /**
         *  Function returns a pointer to a model containing data for the
         *  pieces table to be displayed on the pieces panel.
         *  Can be limited with searchPieces(const QList<QVariant>)
         *
         *  @return - pointer to QSqlQueryModel containing pieces
         *  Display order:
         *  Index, Commissioner, Piece Name, Start Date, Finish Date
         */
        QSqlQueryModel *getPieces();

        /**
         *  Function returns a pointer to a model containing data for the
         *  product table to be displayed on the storefront panel.
         *  Can be limited with searchProducts(const QList<QVariant>)
         *
         *  @return - pointer to QSqlQueryModel containing products
         *  Display order:
         *  Index, Name, Base Price, Number of Pieces Produced
         */
        QSqlQueryModel *getProducts();

        /**
         *  Function returns a pointer to a model containing data for the
         *  sales table to be displayed on the storefront panel.
         *  Can be limited with searchSales(const QList<QVariant>)
         *
         *  @return - pointer to QSqlQueryModel containing sales
         *  Display order:
         *  Index, Name, Start Date, End Date
         */
        QSqlQueryModel *getSales();

        /**
         *  Function returns a QDataWidgetMapper that can be connected to
         *  multiple views. The current record can be set by
         *  setCommission(const QModelIndex &)
         *
         *  @return - pointer to QDataWidgetMapper containing data about the
         *      commission
         *  Data order:
         *  Name, Create Date, Paid Date, Due Date, Money Owed
         */
        QDataWidgetMapper *getCommission();

        /**
         *  Function returns a QDataWidgetMapper that can be connected to
         *  multiple views. The current record can be set by
         *  setCommissioner(const QModelIndex &)
         *
         *  @return - pointer to QDataWidgetMapper containing data about the
         *      commissioner
         *  Data order:
         *  Name, Customer Since, Money Owed, Notes
         */
        QDataWidgetMapper *getCommissioner();

        /**
         *  Function returns a QDataWidgetMapper that can be connected to
         *  multiple views. The current record can be set by
         *  setPiece(const QModelIndex &)
         *
         *  @return - pointer to QDataWidgetMapper containing data about the
         *      piece
         *  Data order:
         *  Commissioner Name, Piece Name, Start Date, Finish Date, Description
         */
        QDataWidgetMapper *getPiece();

        /**
         *  Function returns a QDataWidgetMapper that can be connected to
         *  multiple views. The current record can be set by
         *  setProduct(const QModelIndex &)
         *
         *  @return - pointer to QDataWidgetMapper containing data about the
         *      product
         *  Data order:
         *  Name, Number Produced, Base Price
         */
        QDataWidgetMapper *getProduct();

        /**
         *  Function returns a QDataWidgetMapper that can be connected to
         *  multiple views. The current record can be set by
         *  setSale(const QModelIndex &)
         *
         *  @return - pointer to QDataWidgetMapper containing data about the
         *      sale
         *  Data order:
         *  Sale Name, Start Date, End Date, Description
         */
        QDataWidgetMapper *getSale();

        /**
         *  Function returns a pointer to a model containing data for the
         *  commission pieces table to be displayed on the commission panel.
         *  The current record can be set by setCommission(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing commission pieces
         *  Display order:
         *  Product, Name, Price, Sale, Start Date, Finish Date
         */
        QSqlQueryModel *getCommissionPieces();

        /**
         *  Function returns a pointer to a model containing data for the
         *  commission payments table to be displayed on the commission panel.
         *  The current record can be set by setCommission(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing commission payments
         *  Display order:
         *  Payment Method, Date, Amount, Notes
         */
        QSqlQueryModel *getCommissionPayments();

        /**
         *  Function returns a pointer to a model containing data for the
         *  commissioner contacts table to be displayed on the commissioner panel.
         *  The current record can be set by setCommissioner(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing commissioner contacts
         *  Display order:
         *  Contact Type, Entry
         */
        QSqlQueryModel *getCommissionerContacts();

        /**
         *  Function returns a pointer to a model containing data for the
         *  commissioner commissions table to be displayed on the commissioner panel.
         *  The current record can be set by setCommissioner(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing commissioner commissions
         *  Display order:
         *  Payment Method, Date, Amount, Notes
         */
        QSqlQueryModel *getCommissionerCommissions();

        /**
         *  Function returns a pointer to a model containing data for the
         *  piece events table to be displayed on the piece panel.
         *  The current record can be set by setPiece(const QModelIndex &)
         *
         *  @return - pointer to QSqlTableModel containing piece events
         *  Display order:
         *  Event Name, Start Date, End Date
         */
        QSqlTableModel *getPieceEvents();

        /**
         *  Function returns a pointer to a model containing data for the
         *  piece references table to be displayed on the piece panel.
         *  The current record can be set by setPiece(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing piece references
         *  Display order:
         *  Reference
         */
        QSqlQueryModel *getPieceReferences();

        /**
         *  Function returns a pointer to a model containing data for the
         *  product options table to be displayed on the product panel.
         *  The current record can be set by setProduct(const QModelIndex &)
         *
         *  @return - pointer to QSqlTableModel containing product options
         *  Display order:
         *  Name, Price, Is Numeric
         */
        QSqlTableModel *getProductOptions();

        /**
         *  Function returns a pointer to a model containing data for the
         *  product pieces sold table to be displayed on the product panel.
         *  The current record can be set by setProduct(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing pieces sold
         *  Display order:
         *  Commissioner, Piece Name, Start Date, Finish Date
         */
        QSqlQueryModel *getProductPiecesSold();

        /**
         *  Function returns a pointer to a model containing data for the
         *  sale deals table to be displayed on the sale panel.
         *  The current record can be set by setSale(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing sale deals
         *  Display order:
         *  Deal, Num Bought
         */
        QSqlQueryModel *getSaleDeals();

        /**
         *  Function returns a pointer to a model containing data for the
         *  sale pieces sold table to be displayed on the sale panel.
         *  The current record can be set by setSale(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing pieces sold
         *  Display order:
         *  Commissioner, Piece Name, Start Date, Finish Date
         */
        QSqlQueryModel *getSalePiecesSold();

    public slots:
        void searchCommissions(const QList<QVariant> searchQuery 
            = QList<QVariant>());
        void searchCommissioners(const QList<QVariant> searchQuery
            = QList<QVariant>());
        void searchPieces(const QList<QVariant> searchQuery
            = QList<QVariant>());
        void searchProducts(const QList<QVariant> searchQuery
            = QList<QVariant>());
        void searchSales(const QList<QVariant> searchQuery
            = QList<QVariant>());
        void setCommission(const QModelIndex &index);
        void setCommissioner(const QModelIndex &index);
        void setPiece(const QModelIndex &index);
        void setProduct(const QModelIndex &index);
        void setSale(const QModelIndex &index);
        void insertCommissioner(const QList<QVariant> commissionerInfo = QList<QVariant>());
        void insertContact(const QList<QVariant> contactInfo = QList<QVariant>());
        void insertPieceReference(const QList<QVariant> referenceInfo = QList<QVariant>());
        void insertProduct(const QList<QVariant> productInfo = QList<QVariant>());
        void insertProductOption(const QList<QVariant> optionInfo = QList<QVariant>());
        void insertSale(const QList<QVariant> saleInfo = QList<QVariant>());
        void insertDeal(const QList<QVariant> dealInfo = QList<QVariant>());
        void insertPiece(const QList<QVariant> pieceInfo = QList<QVariant>());
        void insertPayment(const QList<QVariant> paymentInfo = QList<QVariant>());
        void insertCommission(const QList<QVariant> commissionInfo = QList<QVariant>());

    private:
        /**
        *  Builds the database schema into the currently managed database.
        *  Ran during the create function before prepared statements and
        *  individual models are dealt with.
        */
        void build();

        /**
        *  Prepares the various sub-models that are managed by the ComModel.
        */
        void prepare();

        QSqlDatabase sql;
        QSqlQueryModel *commissionsModel;
        QSqlQueryModel *commissionersModel;
        QSqlQueryModel *piecesModel;
        QSqlQueryModel *productsModel;
        QSqlQueryModel *salesModel;

        QDataWidgetMapper *commissionModel;
        QDataWidgetMapper *commissionModel;
        QDataWidgetMapper *pieceModel;
        QDataWidgetMapper *productModel;
        QDataWidgetMapper *saleModel;

        QSqlQueryModel *commissionPiecesModel;
        QSqlQueryModel *commissionPaymentsModel;

        QSqlQueryModel *commissionerContactsModel;
        QSqlQueryModel *commissionerCommissionsModel;

        QSqlQueryModel *pieceEventsModel;
        QSqlQueryModel *pieceReferencesModel;

        QSqlTableModel *productOptionsModel;
        QSqlQueryModel *productPiecesSoldModel;

        QSqlQueryModel *saleDealsModel;
        QSqlQueryModel *salePiecesSoldModel;
    };
}