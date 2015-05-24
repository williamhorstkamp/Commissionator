#ifndef COMMODEL_H
#define COMMODEL_H
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QDateTime>

namespace Commissionator {

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
         *  Default constructor sets the QObject given as argument to the
         *  ComModel's parent.
         *  Initializes ComModel components by calling build and prepareModels
         */
        ComModel(QObject *parent = nullptr);

        ~ComModel();

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
         *  payment type slider to be displayed on the payment popup dialog.
         *
         *  @return - pointer to QSqlQueryModel containing payment types
         *  Display order:
         *  Index, Payment Type
         */
        QSqlQueryModel *getPaymentTypes();

        /**
         *  Function returns a pointer to a model containing data for the
         *  sales table to be displayed on the storefront panel.
         *  Can be limited with searchSales(const QList<QVariant>)
         *
         *  @return - pointer to QSqlQueryModel containing sales
         *  Display order:
         *  Index, Name, Start Date, End Date
         */
        //QSqlQueryModel *getSales();

        /**
         *  Function returns a pointer to a model containing data for the
         *  commissioner combobox to be displayed on the new commission dialog.
         *
         *  @return - pointer to QSqlQueryModel containing the commissioner names
         *  Display order:
         *  Commissioner Id, Name
         */
        QSqlQueryModel *getCommissionerNames();

        /**
         *  Function returns a pointer to a model containing data for the
         *  contact type slider to be displayed on the commissioner panel.
         *
         *  @return - pointer to QSqlQueryModel containing contact types
         *  Display order:
         *  Index, Type Name
         */
        QSqlQueryModel *getContactTypes();

        /**
         *  Function returns a QSqlQueryModel that contains data about the
         *  seleted Commission
         *
         *  @return - pointer to QSqlQueryModel containing data about the
         *      commission
         *   Data order:
         *   Commissioner Name, Create Date, Paid Date, Due Date, Amount Owed,
         *       Notes
         */
        QSqlQueryModel *getCommission();

        /**
         *  Function returns a QSqlQueryModel that contains data about the
         *  seleted Commissioner
         *
         *  @return - pointer to QSqlQueryModel containing data about the
         *      commissioner
         *   Data order:
         *   Commissioner Id, Commissioner Name, Customer Since, Amount Owed, Notes
         */
        QSqlQueryModel *getCommissioner();

        /**
         *  Function returns a QSqlQueryModel that contains data about the
         *  seleted Piece
         *
         *  @return - pointer to QSqlQueryModel containing data about the
         *      piece
         *   Data order:
         *   Commissioner Name, Piece Name, Start Date, End Date, Notes
        */
        QSqlQueryModel *getPiece();

        /**
         *  Function returns a QSqlQueryModel that contains data about the
         *  seleted Product
         *
         *  @return - pointer to QSqlQueryModel containing data about the
         *      product
         *   Data order:
         *   Product Name, Number Produced, Base Price
         */
        QSqlQueryModel *getProduct();

        /**
         *  Function returns a QDataWidgetMapper that can be connected to
         *  multiple views. The current record can be set by
         *  setSale(const QModelIndex &)
         *  Contains the data about the sale
         *
         *  @return - pointer to QDataWidgetMapper containing data about the
         *      sale
         *  Data order:
         *  Sale Name, Start Date, End Date, Notes
         */
        //QDataWidgetMapper *getSale();

        /**
         *  Function returns a pointer to a model containing data for the
         *  commission pieces table to be displayed on the commission panel.
         *  The current record can be set by setCommission(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing commission pieces
         *  Display order:
         *  Product, Name, Price, Sale, Start Date, Finish Date
         */
        //QSqlQueryModel *getCommissionPieces();

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
         *  Id, Contact Type, Entry
         */
        QSqlQueryModel *getCommissionerContacts();

        /**
         *  Function returns a pointer to a model containing data for the
         *  commissioner commissions table to be displayed on the commissioner panel.
         *  The current record can be set by setCommissioner(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing commissioner commissions
         *  Display order:
         *  Create Date, Paid Date, Cost, Finish Date
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
        //QSqlTableModel *getPieceEvents();

        /**
         *  Function returns a pointer to a model containing data for the
         *  piece references table to be displayed on the piece panel.
         *  The current record can be set by setPiece(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing piece references
         *  Display order:
         *  Reference
         */
        //QSqlQueryModel *getPieceReferences();

        /**
         *  Function returns a pointer to a model containing data for the
         *  product options table to be displayed on the product panel.
         *  The current record can be set by setProduct(const QModelIndex &)
         *
         *  @return - pointer to QSqlTableModel containing product options
         *  Display order:
         *  Name, Price, Is Numeric
         */
        //QSqlTableModel *getProductOptions();

        /**
         *  Function returns a pointer to a model containing data for the
         *  product pieces sold table to be displayed on the product panel.
         *  The current record can be set by setProduct(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing pieces sold
         *  Display order:
         *  Commissioner, Piece Name, Start Date, Finish Date
         */
        //QSqlQueryModel *getProductPiecesSold();

        /**
         *  Function returns a pointer to a model containing data for the
         *  sale deals table to be displayed on the sale panel.
         *  The current record can be set by setSale(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing sale deals
         *  Display order:
         *  Deal, Num Bought
         */
        //QSqlQueryModel *getSaleDeals();

        /**
         *  Function returns a pointer to a model containing data for the
         *  sale pieces sold table to be displayed on the sale panel.
         *  The current record can be set by setSale(const QModelIndex &)
         *
         *  @return - pointer to QSqlQueryModel containing pieces sold
         *  Display order:
         *  Commissioner, Piece Name, Start Date, Finish Date
         */
        //QSqlQueryModel *getSalePiecesSold();

    signals:
        /**
         *  Signal emmitted whenever the currently selected commission is 
         *  changed.
         */
        void commissionChanged();

        /**
         *  Signal emmitted whenever the currently selected commissioner is
         *  changed.
         */
        void commissionerChanged();

        /**
         *  Signal emmitted whenever the currently selected piece is
         *  changed.
         */
        void pieceChanged();

    public slots:

        /**
         *  Closes the open database
         */
        void close();

        /**
         *  Opens a new SQLite database in memory, including building the
         *  schema and preparing queries. 
         */
        void newRecord();

        /**
         *  Opens the SQLite database at the given filename.
         *
         *  @param fileName - fileName to open
         */
        //void open(QString fileName);
        
        /**
         *  Saves the currently open database to the file at the given filename.
         *
         *  @param fileName - the filename and location to save the file to
         */
        //void save(QString fileName);

        /**
         *  Function edits the name of the commissioner with the given id.
         *
         *  @param commissioner - commissioner id
         *  @param name - commissioner name
         */
        void editCommissionerName(const int commissioner, const QString name);

        /**
         *  Function edits the notes of the commissioner with the given id.
         *
         *  @param commissioner - commissioner id
         *  @param nnotes - commissioner nnotes
         */
        void editCommissionerNotes(const int commissioner, const QString notes);

        /**
         *  Slot limits the results of getCommissions() based on the inputs
         *  given in the searchQuery.
         *  
         *  @param commissioner - commissioner name to search for
         *  @param createDate - creation date to search for
         *  @param paidDate - payment date to search for
         *  @Param dueDate - due date to search for
         *  @Param numberOfPieces - how many pieces were in the commission
         *  @param finishDate - finish date to search for
         */
        void searchCommissions(const QString commissioner, 
            const QString createDate, const QString paidDate,
            const QString dueDate, const QString numberOfPieces,
            const QString finishDate);

        /**
         *  Slot limits the results of getCommissioners() based on the inputs
         *  given in the searchQuery.
         *
         *  @param name - the commissioner name
         *  @param dateOldest - the date of their first commission that isn't 
         *      finished
         *  @param balance - how much money they owe total
         */
        void searchCommissioners(const QString name, const QString dateOldest, 
            const QString balance);

        /**
         *  Slot limits the results of getPieces() based on the inputs
         *  given in the searchQuery.
         *
         *  @param commissionerName - the name of the commissioner of the piece
         *  @param pieceName - the name of the piece
         *  @Param startDate - the date the piece was started
         *  @Param finishDate - the date the piece was finished
         */
        void searchPieces(const QString commissionerName,
            const QString pieceName, const QString startDate,
            const QString finishDate);
            
        /**
         *  Slot limits the results of getProducts() based on the inputs
         *  given in the searchQuery.
         *
         *  @param name - name of the product
         *  @param basePrice - the price of the product without options
         *  @param numberOfPieces - the number of pieces of this product
         *      that have been commissioned
         */
        void searchProducts(const QString name, const QString basePrice,
            const QString numberOfPieces);

        /**
         *  Slot limits the results of getSales() based on the inputs
         *  given in the searchQuery.
         *
         *  @param name - name of the sale
         *  @param startDate - starting date of the sale
         *  @param endDate - ending date of the sale
         */
        //void searchSales(const QString name, const QString startDate,
            //const QString endDate);

        /**
         *  Slot sets a number of models relating to the commission panel to
         *  the commission referenced by the given index.
         *
         *  @param index - index containing the commission to set the models to
         */
        void setCommission(const QModelIndex &index);

        /**
         *  Slot sets a number of models relating to the commissioner panel to
         *  the commissioner referenced by the given index.
         *
         *  @param index - index containing the commissioner to set the models to
         */
        void setCommissioner(const QModelIndex &index);

        /**
         *  Slot sets a number of models relating to the piece panel to
         *  the piece referenced by the given index.
         *
         *  @param index - index containing the piece to set the models to
         */
        void setPiece(const QModelIndex &index);

        /**
         *  Slot sets a number of models relating to the product panel to
         *  the product referenced by the given index.
         *
         *  @param index - index containing the product to set the models to
         */
        //void setProduct(const QModelIndex &index);

        /**
         *  Slot sets a number of models relating to the sale panel to
         *  the sale referenced by the given index.
         *
         *  @param index - index containing the sale to set the models to
         */
        //void setSale(const QModelIndex &index);

        /**
         *  Deletes the commissioner at the given index.
         *
         *  @param commissioner - index of the Commissioner to delete
         */
        void deleteCommissioner(const QModelIndex &index);

        /**
         *  Deletes the contact at the given index.
         *
         *  @param contact - contact id of the contact to delete
         */
        void deleteContact(const QModelIndex &index);

        /**
         *  Deletes the contact type at the given index.
         *
         *  @param index - index of the Contact Type to delete
         */
        //void deleteContactType(const QModelIndex &index);

        /**
         *  Deletes the piece reference at the given index.
         *
         *  @param index - index of the reference to delete
         */
        //void deletePieceReference(const QModelIndex &index);

        /**
         *  Deletes the product at the given index. Product is hidden, not
         *  actually deleted, so old records aren't broken.
         *
         *  @param index - index of the product to delete
         */
        //void deleteProduct(const QModelIndex &index);

        /**
         *  Deletes the product option at the given index. Option is hidden, not
         *  actually deleted, so old records aren't broken.
         *
         *  @param index - index of the product option to delete
         */
        //void deleteProductOption(const QModelIndex &index);

        /**
         *  Deletes the sale at the given index.
         *
         *  @param index - index of the sale to delete
         */
        //void deleteSale(const QModelIndex &index);

        /**
         *  Deletes the deal at the given index.
         *
         *  @param index - index of the sale deal to delete
         */
        //void deleteDeal(const QModelIndex &index);

        /**
         *  Deletes the piece at the given index.
         *
         *  @param index - index of the piece to delete
         */
        //void deletePiece(const QModelIndex &index);

        /**
         *  Deletes the payment at the given index.
         *
         *  @param index - index of the payment to delete
         */
        //void deletePayment(const QModelIndex &index);

        /**
         *  Deletes the commission at the given index. Pieces are reassigned
         *  to a generic commission.
         *
         *  @param index - index of the commission to delete
         */
        //void deleteCommission(const QModelIndex &index);

        /**
         *  Deletes the payment type at the given index. Payment type is hidden,
         *  not actually deleted, so as to not break old records.
         *
         *  @param index - index of the sale to delete
         */
        //void deletePaymentType(const QModelIndex &index);

        /**
         *  Inserts commissioner into the database.
         *
         *  @param commissionerName - name of commissioner
         *  @param commissionerNotes - notes for commissioner
         */
        void insertCommissioner(const QString commissionerName, 
            const QString commissionerNotes);

        /**
         *  Inserts contact into the database.
         *
         *  @param commissionerId - id of commissioner the contact is for
         *  @param contactType - type of contact
         *  @param contactEntry - the entry for this contact
         */
        void insertContact(const int commissionerId, 
            const int contactType, const QString contactEntry);

        /**
         *  Inserts contact type into the database.
         *
         *  @param contactTypeName - QString representing Contact Type name
         */
        void insertContactType(const QString contactTypeName);

        /**
         *  Inserts piece reference into the database.
         *
         *  @param piece - piece the reference is for
         *  @param reference - reference to be bound
         */
        //void insertPieceReference(const QString piece, 
        //    const QString reference);

        /**
         *  Inserts product into the database.
         *
         *  @param productName - name of the product
         *  @param basePrice - base price of the product without options
         */
        void insertProduct(const QString productName, const double basePrice);

        /**
         *  Inserts new product price into database.
         *
         *  @param productId - id of the product
         *  @param basePrice - base price of the product without options
         */
        void insertProductPrice(const int productId, const double basePrice);

        /**
         *  Inserts product option type into the database.
         *
         *  @param product - product the option is for
         *  @param option - name of product option
         *  @param optionPrice - cost of the option
         *  @param isNumeric - whether the price is a numeric value or a boolean
         */
        //void insertProductOption(const QString product, const QString option,
            //const QString optionPrice, bool isNumeric);

        /**
         *  Inserts sale into the database.
         *
         *  @param name - name of the sale
         *  @param startDate - starting date of the sale
         *  @param endDate - ending date of the sale
         */
        //void insertSale(const QString name, const QDateTime startDate, 
            //const QDateTime endDate);

        /**
         *  Inserts deal into the database.
         *
         *  Is in the form of:
         *  Buy count1 of product1 at scalar1% and get count2 of product2
         *      at sclar2%.
         *
         *  @param dealName - name of the deal
         *  @param count1 - how many of product1 you have to buy to get the deal
         *  @param product1 - the product you have to buy to get the deal
         *  @param scalar1 - the percent price you pay for the first product
         *  @param count2 - the number of product2s you recieve
         *  @param product2 - the product you get with the deal
         *  @param scalar2 - the amount you pay for the second product
         */
        //void insertDeal(const QString dealName, int count1, QString product1, 
            //double scalar1, int count2, QString product2, double scalar2);

        /**
         *  Inserts piece into the database.
         *
         *  @param commission - commission the piece belongs to
         *  @param product - what type of product the piece is
         *  @param name - the name of the piece
         *  @param description - description of the piece
         */
        void insertPiece(const int commission, const int product,
            const QString name, const QString description);

        /**
         *  Inserts payment into the database.
         *
         *  @param commissionId - commission the payment is for
         *  @param paymentTypeId - type of payment that is being made
         *  @param paymentAmount - the amount the payment is made for
         *  @param paymentNotes - notes about the payment
         */
        void insertPayment(const int commissionId, const int paymentTypeId,
            const double paymentAmount, const QString paymentNotes);

        /**
         *  Inserts commission into the database.
         *
         *  @param commissionerId - id of commissioner of the commission
         *  @param dueDate - due date of the commission
         *  @param notes - notes for the commission
         */
        void insertCommission(const int commissionerId,
            const QDateTime dueDate, const QString notes);

        /**
         *  Inserts payment into the database.
         *
         *  @param typeName - name of the payment type that is being entered
         */
        void insertPaymentType(const QString typeName);

    private:
        /**
        *  Builds the database schema into the currently managed database.
        *  Ran during the create function before prepared statements and
        *  individual models are dealt with.
        */
        void build();

        /**
         *  Function finishes all queries that were setup in the
         *  prepareModels() function.
         */
        void cleanupQueries();

        /**
         *  Function returns the value of the table with the row from
         *  index and the column given.
         *  Exists as a helper function so the model can access a row's id
         *  no matter which particular column's index was passed to the model
         *  through a socket.
         *
         *  @param index - reference to the index whose row is being accessed
         *  @param column - column that contains the value to return
         */
        QVariant getValue(const QModelIndex &index, int column);

        /**
        *  Prepares the various sub-models that are managed by the ComModel.
        */
        void prepareModels();

        QSqlDatabase sql;
		QSqlQueryModel *commissionerCommissionsModel;
		QSqlQueryModel *commissionerContactsModel;
        QSqlQueryModel *commissionerModel;
        QSqlQueryModel *commissionerNamesModel;
        QSqlQueryModel *commissionersModel;
		QSqlQueryModel *commissionmodel;
		QSqlQueryModel *commissionPaymentsModel;
        QSqlQueryModel *commissionsModel;
        QSqlQueryModel *contactTypesModel;
        QSqlQuery *deleteCommissionerQuery;
        QSqlQuery *deleteContactQuery;
        QSqlQuery *editCommissionerNameQuery;
        QSqlQuery *editCommissionerNotesQuery;
        QSqlQuery *insertCommissionerQuery;
        QSqlQuery *insertCommissionQuery;
        QSqlQuery *insertContactQuery;
        QSqlQuery *insertContactTypeQuery;
        QSqlQuery *insertPaymentQuery;
        QSqlQuery *insertPaymentTypeQuery;
        QSqlQuery *insertPieceQuery;
        QSqlQuery *insertProductPriceQuery;
        QSqlQuery *insertProductQuery;
        QSqlQueryModel *paymentTypesModel;
        QSqlQueryModel *pieceModel;
        QSqlQueryModel *piecesModel;
        QSqlQueryModel *productModel;
        QSqlQueryModel *productsModel;
    };
}
#endif