#include <QtWidgets>
#include "mainwindow.h"

namespace Commissionator{
    MainWindow::MainWindow() {
        createActions();
        createMenus();
        createStatusBar();
        layout = new QHBoxLayout();
        window = new QWidget();
        leftPanel = new QStackedWidget();
        rightPanel = new QStackedWidget();
        lp1 = new LeftPanel();
        lp2 = new LeftPanel2();
        rp1 = new RightPanel();
        rp2 = new RightPanel2();
        leftPanel->addWidget(lp1);
        leftPanel->addWidget(lp2);
        rightPanel->addWidget(rp1);
        rightPanel->addWidget(rp2);
        layout->addWidget(leftPanel);
        layout->addWidget(rightPanel);
        window->setLayout(layout);
        setCentralWidget(window);
    }

    void MainWindow::createMenus() {
        fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addAction(newAct);
        fileMenu->addAction(openAct);
        fileMenu->addSeparator();
        fileMenu->addAction(saveAct);
        fileMenu->addAction(saveAsAct);
        fileMenu->addSeparator();
        fileMenu->addAction(printRecordAct);
        fileMenu->addSeparator();
        fileMenu->addAction(exitAct);

        newMenu = menuBar()->addMenu(tr("&New"));
        newMenu->addAction(newCommissionerAct);
        newMenu->addAction(newCommissionAct);
        newMenu->addAction(newProductAct);
        newMenu->addAction(newSaleAct);
        newMenu->addAction(newPaymentAct);

        manageMenu = menuBar()->addMenu(tr("&Manage"));
        manageMenu->addAction(manageCommissionerAct);
        manageMenu->addAction(manageCommissionAct);
        manageMenu->addAction(managePieceAct);
        manageMenu->addAction(manageProductAct);
        manageMenu->addAction(manageSaleAct);
        manageMenu->addAction(managePaymentAct);

        menuBar()->addSeparator();

        helpMenu = menuBar()->addMenu(tr("&Help"));
        helpMenu->addAction(helpAct);
        helpMenu->addAction(aboutAct);
    }

    void MainWindow::createActions() {
        newAct = new QAction(tr("&New"), this);
        newAct->setStatusTip(tr("Create a new set of records"));
        connect(newAct, SIGNAL(triggered()), this, SLOT(page1()));

        openAct = new QAction(tr("&Open"), this);
        openAct->setStatusTip(tr("Open a set of records"));
        connect(openAct, SIGNAL(triggered()), this, SLOT(page2()));

        saveAct = new QAction(tr("&Save"), this);
        saveAct->setStatusTip(tr("Save the current set of records"));

        saveAsAct = new QAction(tr("&Save As"), this);
        saveAsAct->setStatusTip(tr("Save the current set of records as a new file"));

        printRecordAct = new QAction(tr("&Print Records"), this);
        printRecordAct->setStatusTip(tr("Prints the entire set of data kept in the file"));

        exitAct = new QAction(tr("&Exit"), this);
        exitAct->setStatusTip(tr("Exits the program"));
        connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

        newCommissionerAct = new QAction(tr("&Commissioner"), this);
        newCommissionerAct->setStatusTip(tr("Create a new commissioner"));

        newCommissionAct = new QAction(tr("&Commission"), this);
        newCommissionAct->setStatusTip(tr("Create a new commission"));

        newProductAct = new QAction(tr("&Product"), this);
        newProductAct->setStatusTip(tr("Create a new product"));

        newSaleAct = new QAction(tr("&Sale"), this);
        newSaleAct->setStatusTip(tr("Create a new sale"));

        newPaymentAct = new QAction(tr("&Payment"), this);
        newPaymentAct->setStatusTip(tr("Create a new payment"));

        manageCommissionerAct = new QAction(tr("&Commissioner"), this);
        manageCommissionerAct->setStatusTip(tr("Manage existing commissioners"));

        manageCommissionAct = new QAction(tr("&Commission"), this);
        manageCommissionAct->setStatusTip(tr("Manage existing commissions"));

        managePieceAct = new QAction(tr("&Piece"), this);
        managePieceAct->setStatusTip(tr("Manage existing pieces"));

        manageProductAct = new QAction(tr("&Product"), this);
        manageProductAct->setStatusTip(tr("Manage existing products"));

        manageSaleAct = new QAction(tr("&Sale"), this);
        manageSaleAct->setStatusTip(tr("Manage existing sales"));

        managePaymentAct = new QAction(tr("&Payment"), this);
        managePaymentAct->setStatusTip(tr("Manage existing payments"));

        helpAct = new QAction(tr("&Help"), this);
        helpAct->setStatusTip(tr("Get help about Commissionator"));

        aboutAct = new QAction(tr("&About Commissionator"), this);
        aboutAct->setStatusTip(tr("View important version and legal information about this program"));
    }

    void MainWindow::createStatusBar() {
        statusBar()->showMessage(tr("Ready"));
    }

    void MainWindow::page1() {
        leftPanel->setCurrentWidget(lp1);
        rightPanel->setCurrentWidget(rp1);
    }

    void MainWindow::page2() {
        leftPanel->setCurrentWidget(lp2);
        rightPanel->setCurrentWidget(rp2);
    }
}