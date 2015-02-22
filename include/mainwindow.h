#ifndef MAINWINDOW
#define MAINWINDOW

#include <QMainWindow>

namespace Commissionator {

    class MainWindow:public QMainWindow {
    public:
        MainWindow();

    private:
        void createMenus();
        void createActions();
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
    };


}

#endif // MAINWINDOW

