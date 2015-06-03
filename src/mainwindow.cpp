#include <QtWidgets>
#include <QComboBox>
#include <QSqlQueryModel>
#include "mainwindow.h"

namespace Commissionator{
    MainWindow::MainWindow() {
        createActions();
        createMenus();
        createStatusBar();
        createToolBars();
        createModel();
        createPanels();
        createPopups();

        setMinimumSize(700, 550);

        model->insertCommissioner("Test", "wutdo");
        model->insertContactType("type");
        model->insertContact(1, 1, "entry");
        model->insertProduct("thing", 1.0);
        model->insertCommission(1, QDateTime::currentDateTime(), "");
        model->insertCommission(2, QDateTime::currentDateTime(), "");
        model->insertPiece(1, 1, "piece", "", -1);
        model->insertPiece(2, 1, "piece", "", -1);
        model->insertPaymentType("payment type");
        model->insertPayment(1, 1, 1.0, "");
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
        connect(openAct, &QAction::triggered, 
            this, &MainWindow::manageCommissions);

        saveAct = new QAction(QIcon(":/SaveFile.png"), tr("&Save"), this);
        saveAct->setStatusTip(tr("Save the current set of records"));
        connect(saveAct, &QAction::triggered, 
            this, &MainWindow::manageCommissioners);

        saveAsAct = new QAction(QIcon(":/SaveAsFile.png"), tr("&Save As"), this);
        saveAsAct->setStatusTip(tr("Save the current set of records as a new file"));

        printRecordAct = new QAction(tr("&Print Records"), this);
        printRecordAct->setStatusTip(tr("Prints the entire set of data kept in the file"));

        exitAct = new QAction(tr("&Exit"), this);
        exitAct->setStatusTip(tr("Exits the program"));
        connect(exitAct, &QAction::triggered, 
            this, &MainWindow::close);
        
        newCommissionerAct = new QAction(QIcon(":/CommissionerPlus.png"), tr("&Commissioner"), this);
        newCommissionerAct->setStatusTip(tr("Create a new commissioner"));
        connect(newCommissionerAct, &QAction::triggered, 
            this, &MainWindow::newCommissioner);

        newCommissionAct = new QAction(QIcon(":/CommissionPlus.png"), tr("&Commission"), this);
        newCommissionAct->setStatusTip(tr("Create a new commission"));
        connect(newCommissionAct, &QAction::triggered, 
            this, &MainWindow::newCommission);

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
        mainToolBar->setMovable(false);
        commissionerToolBar = addToolBar(tr("Commissioner"));
        commissionerToolBar->addAction(newCommissionAct);
        commissionerToolBar->setMovable(false);
        contextToolBar = commissionerToolBar;
        panelToolBar2 = addToolBar(tr("Panel2"));
        panelToolBar2->addAction(newCommissionerAct);
        panelToolBar2->setMovable(false);
        panelToolBar2->setVisible(false);
        setContextMenuPolicy(Qt::NoContextMenu);
    }

    void MainWindow::createModel() {
        model = new ComModel();
    }

    void MainWindow::createPanels() {
        layout = new QHBoxLayout();
        window = new QWidget();
        leftPanel = new QStackedWidget();
        rightPanel = new QStackedWidget();
        QList<int> hidden;
        hidden.append(0);
        commissionerLeftPanel = new LeftPanel("Commissioner", 
            model->getCommissioners(), hidden);
        commissionLeftPanel = new LeftPanel("Commission",
            model->getCommissions(), hidden);
        commissionerRightPanel = new CommissionerPanel(
            model->getCommissioner(),
            model->getCommissionerContacts(),
            model->getCommissionerCommissions(),
            model->getContactTypes(),
            this);
        commissionRightPanel = new CommissionPanel(
            model->getCommission(),
            model->getCommissionPieces(),
            model->getCommissionPayments(),
            model->getCommissionerNames(),
            this);
        leftPanel->addWidget(commissionerLeftPanel);
        leftPanel->addWidget(commissionLeftPanel);
        rightPanel->addWidget(commissionerRightPanel);
        rightPanel->addWidget(commissionerRightPanel);

        QFrame *line = new QFrame(this);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        connect(commissionerLeftPanel, &LeftPanel::tableClicked, 
            model, &ComModel::setCommissioner);
        connect(commissionerLeftPanel, &LeftPanel::search, 
            this, &MainWindow::searchCommissioner);
        connect(commissionerLeftPanel, &LeftPanel::iconClicked,
            model, &ComModel::deleteCommissioner);
        connect(commissionLeftPanel, &LeftPanel::search,
            this, &MainWindow::searchCommission);
        connect(commissionLeftPanel, &LeftPanel::iconClicked,
            model, &ComModel::deleteCommission);
        connect(model, &ComModel::commissionerChanged, 
            commissionerRightPanel, &CommissionerPanel::updatePanel);
        connect(commissionerRightPanel, &CommissionerPanel::newCommission, 
            this, &MainWindow::newCommissionWithCommissioner);
        connect(commissionerRightPanel, &CommissionerPanel::insertContact,
            model, &ComModel::insertContact);
        connect(commissionerRightPanel, &CommissionerPanel::deleteContact,
            model, &ComModel::deleteContact);
        connect(commissionerRightPanel, &CommissionerPanel::editName,
            model, &ComModel::editCommissionerName);
        connect(commissionerRightPanel, &CommissionerPanel::editNotes,
            model, &ComModel::editCommissionerNotes);

        layout->addWidget(leftPanel);
        layout->addWidget(line);
        layout->addWidget(rightPanel);
        window->setLayout(layout);
        setCentralWidget(window);
    }

    void MainWindow::createPopups() {
        commissionPopup = new NewCommissionWindow(
            model->getCommissionerNames(),
            model->getProductNames(),
            this);
        connect(commissionPopup, &NewCommissionWindow::newCommission, 
            this, &MainWindow::insertCommission);
        commissionerPopup = new NewCommissionerWindow(this);
        connect(commissionerPopup, &NewCommissionerWindow::newCommissioner,
            model, &ComModel::insertCommissioner);
    }

    void MainWindow::insertCommission(const int commissionerId,
        const QDateTime dueDate, const QString notes,
        QList<std::tuple<int, QString, QString, double>> pieces) {
        const int id = model->insertCommission(commissionerId, dueDate, notes);
        for (int i = 0; i < pieces.length(); i++)
            model->insertPiece(id, std::get<0>(pieces[i]),
            std::get<1>(pieces[i]), std::get<2>(pieces[i]),
            std::get<3>(pieces[i]));
        commissionerRightPanel->updatePanel();
    }

    void MainWindow::newCommission() {
        commissionPopup->exec();
    }

    void MainWindow::newCommissioner() {
        commissionerPopup->exec();
    }

    void MainWindow::newCommissionWithCommissioner(const QVariant &commissioner) {
        commissionPopup->setCommissioner(commissioner);
        newCommission();
    }

    void MainWindow::searchCommission(const QList<QVariant> query) {
        if (query.length() == 7)    //id, commissioner, create date, paid date, due date, piece count, finish date
            model->searchCommissions(query[1].toString(), query[2].toString(),
            query[3].toString(), query[4].toString(), query[5].toString(),
            query[6].toString());
    }

    void MainWindow::searchCommissioner(const QList<QVariant> query) {
        if (query.length() == 4)    //id, name, commissioner since, amounted owed
            model->searchCommissioners(query[1].toString(), query[2].toString(),
            query[3].toString());
    }

    void MainWindow::manageCommissioners() {
        leftPanel->setCurrentWidget(commissionerLeftPanel);
        rightPanel->setCurrentWidget(commissionerRightPanel);
        swapContextToolBar(commissionerToolBar);
    }

    void MainWindow::manageCommissions() {
        leftPanel->setCurrentWidget(commissionLeftPanel);
        rightPanel->setCurrentWidget(commissionRightPanel);
        swapContextToolBar(panelToolBar2);
    }

    void MainWindow::swapContextToolBar(QToolBar *newBar) {
        contextToolBar->setVisible(false);
        contextToolBar = newBar;
        contextToolBar->setVisible(true);
    }
}