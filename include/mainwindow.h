#ifndef MAINWINDOW
#define MAINWINDOW

#include <QMainWindow>
#include <QStackedWidget>
#include "TestLayouts.h"
#include "LeftPanel.h"
#include "CommissionerPanel.h"
#include "ComModel.h"

namespace Commissionator {

    class MainWindow:public QMainWindow {

        Q_OBJECT

    public:
        MainWindow();

    public slots:
        /**
         *  Function opens the dialog window to create a new commission.
         *  Takes control away from the MainWindow for the duration of the
         *  new commission window's lifetime. Depending on whether a commission
         *  is created or not, the models may be refreshed.
         */
        void newCommission();

        /**
         *  Functions searches for commissioners with given arguements
         *
         *  Argument order:
         *  Commissioner Name, Customer Since, Amount Owed
         */
        void searchCommissioner(const QList<QVariant> query);

        //temp slots for testing
        void page1();
        void page2();

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
        LeftPanel2 *lp2;
        CommissionerPanel *commissionerRightPanel;
        RightPanel2 *rp2;

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