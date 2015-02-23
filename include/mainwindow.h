#ifndef MAINWINDOW
#define MAINWINDOW

#include <QMainWindow>
#include "TestLayouts.h"

namespace Commissionator {

    class MainWindow:public QMainWindow {
    public:
        MainWindow();

    private:
        void createMenus();
        void createActions();
        void createStatusBar();

        QWidget *window;
        QMenu *fileMenu;
        QMenu *newMenu;
        QMenu *manageMenu;
        QMenu *helpMenu;
        //QToolBar *standardToolBar;
        //QToolBar *contextToolBar;
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
        QAction *manageCommissionerAct;
        QAction *manageCommissionAct;
        QAction *managePieceAct;
        QAction *manageProductAct;
        QAction *manageSaleAct;
        QAction *managePaymentAct;
        QAction *aboutAct;
        QAction *helpAct;

        MainLayout *main;
        
    };


}

#endif // MAINWINDOW