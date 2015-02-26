#ifndef MAINWINDOW
#define MAINWINDOW

#include <QMainWindow>
#include <QStackedWidget>
#include "TestLayouts.h"

namespace Commissionator {

    class MainWindow:public QMainWindow {

        Q_OBJECT

    public:
        MainWindow();

    public slots:
        void page1();
        void page2();

    private:
        void createMenus();
        void createActions();
        void createStatusBar();
        void createToolBar();
        void createPanels();

        QWidget *window;
        QHBoxLayout *layout;
        QStackedWidget *leftPanel;
        QStackedWidget *rightPanel;

        LeftPanel *lp1;
        LeftPanel2 *lp2;
        RightPanel *rp1;
        RightPanel2 *rp2;

        QMenu *fileMenu;
        QMenu *newMenu;
        QMenu *manageMenu;
        QMenu *helpMenu;
        QToolBar *mainToolBar;
        QToolBar *contextToolBar;
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