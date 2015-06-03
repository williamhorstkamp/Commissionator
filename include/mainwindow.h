#ifndef MAINWINDOW
#define MAINWINDOW

#include <QMainWindow>
#include <QStackedWidget>
#include "LeftPanel.h"
#include "NewCommissionWindow.h"
#include "NewCommissionerWindow.h"
#include "NewPieceWindow.h"
#include "CommissionerPanel.h"
#include "CommissionPanel.h"
#include "ComModel.h"

namespace Commissionator {

    class MainWindow:public QMainWindow {

        Q_OBJECT

    public:
        MainWindow();

    public slots:

        /**
         *  Function accepts the newCommission signal from NewCommissionWindow 
         *  and inserts both the commission and the pieces into the model.
         *
         *  @param pieceName - piece name
         *  @param pieceNotes - piece notes
         *  @param productId - product id
         *  @param productName - product names
         *  @param price - override price (-1 by default)
         */
        void insertCommission(const int commissionerId,
            const QDateTime dueDate, const QString notes, 
            QList<std::tuple<int, QString, QString, double>> pieces);

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
         *  Sets panels and toolbar to the Manage Commissioner panels
         */
        void manageCommissioners();

        /**
         *  Sets panels and toolbar to the Manage Commission panels
         */
        void manageCommissions();

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

        QWidget *window;
        QHBoxLayout *layout;
        QStackedWidget *leftPanel;
        QStackedWidget *rightPanel;

        ComModel *model;

        LeftPanel *commissionerLeftPanel;
        LeftPanel *commissionLeftPanel;
        CommissionerPanel *commissionerRightPanel;
        CommissionPanel *commissionRightPanel;

        NewCommissionWindow *commissionPopup;
        NewCommissionerWindow *commissionerPopup;

        QMenu *fileMenu;
        QMenu *newMenu;
        QMenu *manageMenu;
        QMenu *helpMenu;

        QToolBar *mainToolBar;
        QToolBar *contextToolBar;
        QToolBar *commissionerToolBar;
        QToolBar *panelToolBar2;

        QAction *newAct;
        QAction *openAct;
        QAction *saveAct;
        QAction *saveAsAct;
        QAction *printRecordAct;
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
        QAction *manageSaleAct;
        QAction *managePaymentAct;
        QAction *aboutAct;
        QAction *helpAct;
    };
}

#endif // MAINWINDOW