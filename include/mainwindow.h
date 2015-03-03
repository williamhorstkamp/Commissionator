#ifndef MAINWINDOW
#define MAINWINDOW

#include <QMainWindow>
#include <QStackedWidget>
#include "TestLayouts.h"
#include "LeftPanel.h"
#include "TestModel.h"

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
        void createToolBars();
        void createModel();
        void createPanels();
        void swapContextToolBar(QToolBar *newBar);

        QWidget *window;
        QHBoxLayout *layout;
        QStackedWidget *leftPanel;
        QStackedWidget *rightPanel;

        TestModel *model;

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
        QToolBar *panelToolBar1;
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