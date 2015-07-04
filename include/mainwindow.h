#ifndef MAINWINDOW
#define MAINWINDOW

#include <QDateTime>
#include <QVariant>
#include <QMainWindow>

class QHBoxLayout;
class QStackedWidget;
class LeftPanel;
class StoreFrontPanel;
class NewCommissionWindow;
class NewCommissionerWindow;
class NewPaymentWindow;
class NewPieceWindow;
class NewProductWindow;
class NewRefundWindow;
class CommissionerPanel;
class CommissionPanel;
class ProductPanel;
class ComModel;
class QFrame;

namespace Commissionator {

    class MainWindow:public QMainWindow {

        Q_OBJECT

    public:
        MainWindow();

        /**
         *  Overrides default closeEvent() function by first attempting to
         *  save before closing
         *
         *  @param event - the close event that is being evaluated
         */
        void closeEvent(QCloseEvent *event);

    public slots:
        /**
         *  Closes the current record.
         */
        void closeRecord();

        /**
         *  Slot accepts the newCommission signal from NewCommissionWindow 
         *  and inserts both the commission and the pieces into the model.
         *
         *  @param pieceName - piece name
         *  @param pieceNotes - piece notes
         *  @param productId - product id
         *  @param productName - product names
         *  @param price - override price (-1 by default)
         *  @param pieces - list of tuples representing each piece in the commission
         *  Tuple Order:
         *  Product Id, Piece Name, Piece Notes, Override Price (default -1)
         */
        void insertCommission(const int commissionerId,
            const QDateTime dueDate, const QString notes, 
            QList<std::tuple
                <const int, const QString, const QString, const double>> pieces);

        /**
         *  Slot accepts the newPiece signal from NewPieceWindow and inserts
         *  the piece into the currently selected commission.
         *
         *  @param pieceName - piece name
         *  @param pieceNotes - piece notes
         *  @param productId - product id
         *  @param productName - product names
         *  @param price - override price (-1 by default)
         */
        void insertPiece(const QString pieceName, const QString pieceNotes,
            const int productId, const QString productName,
            const double price);

        /**
         *  Sets panels and toolbar to the Manage Commissioner panels
         */
        void manageCommissioners();

        /**
         *  Sets panels and toolbar to the Manage Commission panels
         */
        void manageCommissions();

        /**
         *  Sets panels and toolbar to the Manage StoreFront panels
         */
        void manageStoreFront();

        /**
         *  Function opens the dialog window to create a new commission.
         *  Takes control away from the MainWindow for the duration of the
         *  new commission window's lifetime. Depending on whether a commission
         *  is created or not, the models may be refreshed.
         */
        void newCommission();

        /**
         *  Function opens the dialog window to create a new commissioner.
         *  Takes control away from the MainWindow for the duration of the
         *  new commissioner window's lifetime. Depending on whether a commissioner
         *  is created or not, the models may be refreshed.
         */
        void newCommissioner();

        /**
         *  Function opens the dialog window to create a new commission.
         *  Takes control away from the MainWindow for the duration of the
         *  new commission window's lifetime. Depending on whether a commission
         *  is created or not, the models may be refreshed. Prevents editing
         *  the commissioner and sets it to the given commissioner id
         *
         *  @param frozen - commissioner id if the commission is for a specific
         *      commissioner
         */
        void newCommissionWithCommissioner(const QVariant &commissioner);

        /**
         *  Function opens the dialog window to create a new payment.
         *  Takes control away from the MainWindow for the duration of the
         *  new payment window's lifetime. Depending on whether a payment
         *  is made or not, the models may be refreshed.
         *
         *  @param commission - commission id for the payment
         */
        void newPayment(const QVariant &commission);

        /**
         *  Function opens the dialog window to create a new piece.
         *  Takes control away from the MainWindow for the duration of the
         *  new piece window's lifetime. Depending on whether a piece
         *  is created or not, the models may be refreshed.
         */
        void newPiece();

        /**
         *  Function opens the dialog window to create a new product.
         *  Takes control away from the MainWindow for the duration of the
         *  new product window's lifetime. Depending on whether a product
         *  is created or not, the models may be refreshed.
         */
        void newProduct();

        /**
        *  Function opens the dialog window the create a new record.
        *  Takes control away from the MainWindow for the duration of the
        *  new record window's lifetime.
         */
        void newRecord();

        /**
         *  Function opens the dialog window to create a new refund.
         *  Takes control away from the MainWindow for the duration of the
         *  new product window's lifetime. Depending on whether a refund
         *  is created or not, the models may be refreshed.
         *
         *  @param commission - commission id for the payment
         */
        void newRefund(const QVariant &commission);

        /**
         *  Function opens the dialog window the open a record.
         *  Takes control away from the MainWindow for the duration of the
         *  open record window's lifetime.
         */
        void open();

        /**
         *  Function prepares panels and connections when a record is opened.
         */
        void recordClosed();

        /**
         *  Function disables buttons that can't work without a record.
         */
        void recordOpened();

        /**
         *  Function attempts to save to the last saved file. If no file has
         *  been saved to during this session, runs saveAs.
         */
        void save();

        /**
         *  Functions searches for commissioners with given arguements
         *
         *  Argument order:
         *  Commissioner Name, Customer Since, Amount Owed
         */
        void searchCommission(const QList<QVariant> query);

        /**
         *  Functions searches for commissioners with given arguements
         *
         *  Argument order:
         *  Commissioner Name, Customer Since, Amount Owed
         */
        void searchCommissioner(const QList<QVariant> query);

        /**
         *  Functions searches for products with given arguements
         *
         *  Argument order:
         *  Product Name, Base Price, Number Produced
         */
        void searchProducts(const QList<QVariant> query);

    private:
        /**
         *  Initializes menus
         */
        void createMenus();

        /**
         *  Initializes actions
         */
        void createActions();

        /**
         *  Initializes status bar
         */
        void createStatusBar();

        /**
         *  Initializes toolbar
         */
        void createToolBars();

        /**
         *  Initializes model
         */
        void createModel();

        /**
         *  Initializes panels
         */
        void createPanels();

        /**
         *  Initiliazes popups
         */
        void createPopups();

        /**
         *  Switches the context toolbar to what is pointed to in newBar
         *
         *  @param newBar - pointer to the bar to set the context bar to
         */
        void swapContextToolBar(QToolBar *newBar);

        /**
         *  Function toggles whether actions and panels are visible or not
         *  and manages their connections. Helper function of recordOpened and 
         *  recordClosed.
         *
         *  @param isEnabled - whether the components should be enabled or not
         */
        void toggleComponents(const bool isEnabled);

        QWidget *window;
        QHBoxLayout *layout;
        QStackedWidget *leftPanel;
        QStackedWidget *rightPanel;

        ComModel *model;

        LeftPanel *commissionerLeftPanel;
        LeftPanel *commissionLeftPanel;
        StoreFrontPanel *storefrontLeftPanel;
        CommissionerPanel *commissionerRightPanel;
        CommissionPanel *commissionRightPanel;
        ProductPanel *productRightPanel;
        QFrame *line;

        NewCommissionWindow *commissionPopup;
        NewCommissionerWindow *commissionerPopup;
        NewPaymentWindow *paymentPopup;
        NewPieceWindow *piecePopup;
        NewProductWindow *productPopup;
        NewRefundWindow *refundPopup;

        QMenu *fileMenu;
        QMenu *newMenu;
        QMenu *manageMenu;
        QMenu *helpMenu;

        QToolBar *mainToolBar;
        QToolBar *contextToolBar;
        QToolBar *commissionerToolBar;
        QToolBar *commissionToolBar;

        QAction *newAct;
        QAction *openAct;
        QAction *saveAct;
        QAction *saveAsAct;
        QAction *printRecordAct;
        QAction *closeAct;
        QAction *exitAct;
        QAction *newCommissionerAct;
        QAction *newCommissionAct;
        QAction *newProductAct;
        QAction *newSaleAct;
        QAction *newPaymentAct;
        QAction *manageStorefrontAct;
        QAction *manageCommissionerAct;
        QAction *manageCommissionAct;
        QAction *managePieceAct;
        QAction *aboutAct;
        QAction *helpAct;

        QString currentFile;
    };
}
#endif