#include <QtWidgets>
#include "mainwindow.h"
#include <QSqlQueryModel>

namespace Commissionator{
    MainWindow::MainWindow() {
        createActions();
        createMenus();
        createStatusBar();
        createToolBars();
        createModel();
        createPanels();
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
        manageMenu->addAction(manageStorefrontAct);
        manageMenu->addAction(manageCommissionerAct);
        manageMenu->addAction(manageCommissionAct);
        manageMenu->addAction(managePieceAct);
        manageMenu->addAction(manageSaleAct);
        manageMenu->addAction(managePaymentAct);

        menuBar()->addSeparator();

        helpMenu = menuBar()->addMenu(tr("&Help"));
        helpMenu->addAction(helpAct);
        helpMenu->addAction(aboutAct);
    }

    void MainWindow::createActions() {
        newAct = new QAction(QIcon(":/NewFile.png"), tr("&New"), this);
        newAct->setStatusTip(tr("Create a new set of records"));
        

        openAct = new QAction(QIcon(":/OpenFile.png"), tr("&Open"), this);
        openAct->setStatusTip(tr("Open a set of records"));
        connect(openAct, &QAction::triggered, this, &MainWindow::page2);

        saveAct = new QAction(QIcon(":/SaveFile.png"), tr("&Save"), this);
        saveAct->setStatusTip(tr("Save the current set of records"));
        connect(saveAct, &QAction::triggered, this, &MainWindow::page1);

        saveAsAct = new QAction(QIcon(":/SaveAsFile.png"), tr("&Save As"), this);
        saveAsAct->setStatusTip(tr("Save the current set of records as a new file"));

        printRecordAct = new QAction(tr("&Print Records"), this);
        printRecordAct->setStatusTip(tr("Prints the entire set of data kept in the file"));

        exitAct = new QAction(tr("&Exit"), this);
        exitAct->setStatusTip(tr("Exits the program"));
        connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));
        
        newCommissionerAct = new QAction(QIcon(":/CommissionerPlus.png"), tr("&Commissioner"), this);
        newCommissionerAct->setStatusTip(tr("Create a new commissioner"));

        newCommissionAct = new QAction(QIcon(":/CommissionPlus.png"), tr("&Commission"), this);
        newCommissionAct->setStatusTip(tr("Create a new commission"));

        newProductAct = new QAction(QIcon(":/ProductPlus.png"), tr("&Product"), this);
        newProductAct->setStatusTip(tr("Create a new product"));

        newSaleAct = new QAction(QIcon(":/SalePlus.png"), tr("&Sale"), this);
        newSaleAct->setStatusTip(tr("Create a new sale"));

        newPaymentAct = new QAction(QIcon(":/PaymentPlus.png"), tr("&Payment"), this);
        newPaymentAct->setStatusTip(tr("Create a new payment"));

        manageStorefrontAct = new QAction(QIcon(":/Storefront.png"), tr("&Storefront"), this);
        manageStorefrontAct->setStatusTip(tr("Manage existing products"));

        manageCommissionerAct = new QAction(QIcon(":/Commissioner.png"), tr("&Commissioner"), this);
        manageCommissionerAct->setStatusTip(tr("Manage existing commissioners"));

        manageCommissionAct = new QAction(QIcon(":/Commission.png"), tr("&Commission"), this);
        manageCommissionAct->setStatusTip(tr("Manage existing commissions"));

        managePieceAct = new QAction(QIcon(":/Piece.png"), tr("&Piece"), this);
        managePieceAct->setStatusTip(tr("Manage existing pieces"));

        manageSaleAct = new QAction(QIcon(":/Sale.png"), tr("&Sale"), this);
        manageSaleAct->setStatusTip(tr("Manage existing sales"));

        managePaymentAct = new QAction(QIcon(":/Payment.png"), tr("&Payment"), this);
        managePaymentAct->setStatusTip(tr("Manage existing payments"));

        helpAct = new QAction(QIcon(":/Help.png"), tr("&Help"), this);
        helpAct->setStatusTip(tr("Get help about Commissionator"));

        aboutAct = new QAction(tr("&About Commissionator"), this);
        aboutAct->setStatusTip(tr("View important version and legal information about this program"));
    }

    void MainWindow::createStatusBar() {
        statusBar()->showMessage(tr("Ready"));
    }

    void MainWindow::createToolBars() {
        mainToolBar = addToolBar(tr("Main"));
        mainToolBar->addAction(openAct);
        mainToolBar->addAction(saveAct);
        panelToolBar1 = addToolBar(tr("Panel1"));
        panelToolBar1->addAction(newCommissionAct);
        contextToolBar = panelToolBar1;
        panelToolBar2 = addToolBar(tr("Panel2"));
        panelToolBar2->addAction(newCommissionerAct);
        panelToolBar2->setVisible(false);
    }

    void MainWindow::createModel() {
        model = new TestModel();
    }

    void MainWindow::createPanels() {
        layout = new QHBoxLayout();
        window = new QWidget();
        leftPanel = new QStackedWidget();
        rightPanel = new QStackedWidget();
        QList<int> hidden;
        hidden.append(0);
        lp1 = new LeftPanel("Commissioner", model->getLeftModel(), hidden);
        lp2 = new LeftPanel2();
        rp1 = new RightPanel(model->getRightModel());
        rp2 = new RightPanel2();
        leftPanel->addWidget(lp1);
        leftPanel->addWidget(lp2);
        rightPanel->addWidget(rp1);
        rightPanel->addWidget(rp2);

        QFrame *line = new QFrame();
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        connect(lp1, &LeftPanel::tableClicked, model, &TestModel::updateRight);
        connect(lp1, &LeftPanel::search, model, &TestModel::search);
        connect(lp1, &LeftPanel::iconClicked, model, &TestModel::deleteRecord);

        layout->addWidget(leftPanel);
        layout->addWidget(line);
        layout->addWidget(rightPanel);
        window->setLayout(layout);
        setCentralWidget(window);
    }

    void MainWindow::page1() {
        leftPanel->setCurrentWidget(lp1);
        rightPanel->setCurrentWidget(rp1);
        swapContextToolBar(panelToolBar1);
    }

    void MainWindow::page2() {
        leftPanel->setCurrentWidget(lp2);
        rightPanel->setCurrentWidget(rp2);
        swapContextToolBar(panelToolBar2);
    }

    void MainWindow::swapContextToolBar(QToolBar *newBar) {
        contextToolBar->setVisible(false);
        contextToolBar = newBar;
        contextToolBar->setVisible(true);
    }
}