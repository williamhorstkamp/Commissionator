#include <QSqlDatabase>
#include <QSqlQueryModel>

namespace Commissionator{
    class ComModel : public QObject {

        Q_OBJECT

    private:
        void build();
        void prepare();

        QSqlDatabase sql;

    public:
        QSqlQueryModel *getCommissions();
        QSqlQueryModel *getCommissioners();
        QSqlQueryModel *getPieces();
        QSqlQueryModel *getProducts();
        QSqlQueryModel *getSales();

        QSqlQueryModel *getCommission();
        QSqlQueryModel *getCommission();
        QSqlQueryModel *getPiece();
        QSqlQueryModel *getProduct();
        QSqlQueryModel *getSale();

        QSqlQueryModel *getCommissionPieces();
        QSqlQueryModel *getCommissionPayments();
        QSqlQueryModel *getCommissionNotes();

        QSqlQueryModel *getCommissionerContacts();
        QSqlQueryModel *getCommissionerCommissions();
        QSqlQueryModel *getCommissionerNotes();

        QSqlQueryModel *getPieceEvents();
        QSqlQueryModel *getPieceDescription();
        QSqlQueryModel *getPieceReferences();
        QSqlQueryModel *getPieceEventDates();

        QSqlQueryModel *getProductOptions();
        QSqlQueryModel *getProductPiecesSold();

        QSqlQueryModel *getSaleDescription();
        QSqlQueryModel *getSaleDeals();
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
        void insertContact(const QList<QVariant> contactInfo = QList<QVariant>());
        void insertPieceReference(const QList<QVariant> referenceInfo = QList<QVariant>());
        void insertProductOption(const QList<QVariant> optionInfo = QList<QVariant>());
        void insertSaleDeal(const QList<QVariant> dealInfo = QList<QVariant>());
        void insertPiece(const QList<QVariant> pieceInfo = QList<QVariant>());
        void insertPayment(const QList<QVariant> paymentInfo = QList<QVariant>());
        void insertCommission(const QList<QVariant> commissionInfo = QList<QVariant>());
    };
}