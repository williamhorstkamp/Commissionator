#include <QStatusBar>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QToolBar>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QStackedWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include "LeftPanel.h"
#include "NewCommissionWindow.h"
#include "NewCommissionerWindow.h"
#include "NewPaymentWindow.h"
#include "NewPieceWindow.h"
#include "CommissionerPanel.h"
#include "CommissionPanel.h"
#include "ComModel.h"
#include "mainwindow.h"

namespace Commissionator{
    MainWindow::MainWindow() {
        createModel();
        createActions();
        createMenus();
        createStatusBar();
        createToolBars();

        setMinimumSize(1020, 800);
    }

    void MainWindow::closeRecord() {
        if (model->hasBeenChanged()) {
            int ret = QMessageBox::question(this, tr("Save File?"),
                tr("The database has been modified.\n"
                "Would you like to save your changes?"),
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);
            if (ret == QMessageBox::Save)
                save();
            else if (ret == QMessageBox::Cancel)
                return;
        }
        model->close();
    }

    void MainWindow::createMenus() {
        fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addAction(newAct);
        fileMenu->addAction(openAct);
        fileMenu->addSeparator();
        fileMenu->addAction(saveAct);
        fileMenu->addSeparator();
        fileMenu->addAction(printRecordAct);
        fileMenu->addAction(closeAct);
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
        manageMenu->addAction(managePaymentAct);

        menuBar()->addSeparator();

        helpMenu = menuBar()->addMenu(tr("&Help"));
        helpMenu->addAction(helpAct);
        helpMenu->addAction(aboutAct);
    }

    void MainWindow::createActions() {
        newAct = new QAction(QIcon(":/NewFile.png"), tr("&New"), this);
        newAct->setStatusTip(tr("Create a new set of records"));
        connect(newAct, &QAction::triggered,
            this, &MainWindow::newRecord);

        openAct = new QAction(QIcon(":/OpenFile.png"), tr("&Open"), this);
        openAct->setStatusTip(tr("Open a set of records"));
        connect(openAct, &QAction::triggered,
            this, &MainWindow::open);

        saveAct = new QAction(QIcon(":/SaveFile.png"), tr("&Save"), this);
        saveAct->setStatusTip(tr("Save the current set of records"));
        saveAct->setEnabled(false);

        printRecordAct = new QAction(tr("&Print Records"), this);
        printRecordAct->setStatusTip(tr("Prints the entire set of data kept in the file"));
        printRecordAct->setEnabled(false);

        closeAct = new QAction(tr("&Close"), this);
        closeAct->setStatusTip(tr("Closes current record"));
        closeAct->setEnabled(false);

        exitAct = new QAction(tr("&Exit"), this);
        exitAct->setStatusTip(tr("Exits the program"));
        connect(exitAct, &QAction::triggered,
            this, &MainWindow::close);
        
        newCommissionerAct = new QAction(QIcon(":/CommissionerPlus.png"), tr("&Commissioner"), this);
        newCommissionerAct->setStatusTip(tr("Create a new commissioner"));
        newCommissionerAct->setEnabled(false);

        newCommissionAct = new QAction(QIcon(":/CommissionPlus.png"), tr("&Commission"), this);
        newCommissionAct->setStatusTip(tr("Create a new commission"));
        newCommissionAct->setEnabled(false);

        newProductAct = new QAction(QIcon(":/ProductPlus.png"), tr("&Product"), this);
        newProductAct->setStatusTip(tr("Create a new product"));
        newProductAct->setEnabled(false);

        newSaleAct = new QAction(QIcon(":/SalePlus.png"), tr("&Sale"), this);
        newSaleAct->setStatusTip(tr("Create a new sale"));
        newSaleAct->setEnabled(false);

        newPaymentAct = new QAction(QIcon(":/PaymentPlus.png"), tr("&Payment"), this);
        newPaymentAct->setStatusTip(tr("Create a new payment"));
        newPaymentAct->setEnabled(false);

        manageStorefrontAct = new QAction(QIcon(":/Storefront.png"), tr("&Storefront"), this);
        manageStorefrontAct->setStatusTip(tr("Manage existing products"));
        manageStorefrontAct->setEnabled(false);

        manageCommissionerAct = new QAction(QIcon(":/Commissioner.png"), tr("&Commissioner"), this);
        manageCommissionerAct->setStatusTip(tr("Manage existing commissioners"));
        manageCommissionerAct->setEnabled(false);

        manageCommissionAct = new QAction(QIcon(":/Commission.png"), tr("&Commission"), this);
        manageCommissionAct->setStatusTip(tr("Manage existing commissions"));
        manageCommissionAct->setEnabled(false);

        managePieceAct = new QAction(QIcon(":/Piece.png"), tr("&Piece"), this);
        managePieceAct->setStatusTip(tr("Manage existing pieces"));
        managePieceAct->setEnabled(false);

        managePaymentAct = new QAction(QIcon(":/Payment.png"), tr("&Payment"), this);
        managePaymentAct->setStatusTip(tr("Manage existing payments"));
        managePaymentAct->setEnabled(false);

        helpAct = new QAction(QIcon(":/Help.png"), tr("&Help"), this);
        helpAct->setStatusTip(tr("Get help about Commissionator"));
        helpAct->setEnabled(false); //not yet implemented

        aboutAct = new QAction(tr("&About Commissionator"), this);
        aboutAct->setStatusTip(tr("View important version and legal information about this program"));
        aboutAct->setEnabled(false); //not yet implemented   
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
        commissionToolBar = addToolBar(tr("Commission"));
        commissionToolBar->addAction(newCommissionerAct);
        commissionToolBar->setMovable(false);
        commissionToolBar->setVisible(false);
        setContextMenuPolicy(Qt::NoContextMenu);
    }

    void MainWindow::createModel() {
        model = new ComModel();
        connect(model, &ComModel::recordClosed,
            this, &MainWindow::recordClosed);
        connect(model, &ComModel::recordOpened,
            this, &MainWindow::recordOpened);
    }

    void MainWindow::createPanels() {
        layout = new QHBoxLayout();
        window = new QWidget();
        leftPanel = new QStackedWidget();
        rightPanel = new QStackedWidget();
        
        line = new QFrame(this);
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

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
        rightPanel->addWidget(commissionRightPanel);

        connect(commissionerLeftPanel, &LeftPanel::tableClicked,
            model, &ComModel::setCommissioner);
        connect(commissionerLeftPanel, &LeftPanel::search,
            this, &MainWindow::searchCommissioner);
        connect(commissionerLeftPanel, &LeftPanel::iconClicked,
            model, &ComModel::deleteCommissioner);

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

        connect(commissionLeftPanel, &LeftPanel::tableClicked,
            model, &ComModel::setCommission);
        connect(commissionLeftPanel, &LeftPanel::search,
            this, &MainWindow::searchCommission);
        connect(commissionLeftPanel, &LeftPanel::iconClicked,
            model, &ComModel::deleteCommission);

        connect(model, &ComModel::commissionChanged,
            commissionRightPanel, &CommissionPanel::updatePanel);
        connect(commissionRightPanel, &CommissionPanel::deletePiece,
            model, &ComModel::deletePiece);
        connect(commissionRightPanel, &CommissionPanel::editCommissioner,
            model, &ComModel::editCommissionCommissioner);
        connect(commissionRightPanel, &CommissionPanel::editNotes,
            model, &ComModel::editCommissionNotes);
        connect(commissionRightPanel, &CommissionPanel::newPayment,
            this, &MainWindow::newPayment);
        connect(commissionRightPanel, &CommissionPanel::newPiece,
            this, &MainWindow::newPiece);

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
        paymentPopup = new NewPaymentWindow(model->getCommissionList(),
            model->getPaymentTypes(), this);
        connect(paymentPopup, &NewPaymentWindow::newPayment,
            model, &ComModel::insertPayment);
        piecePopup = new NewPieceWindow(model->getProductNames(), this);
        connect(piecePopup, &NewPieceWindow::newPiece,
            this, &MainWindow::insertPiece);
    }

    void MainWindow::insertCommission(const int commissionerId,
        const QDateTime dueDate, const QString notes,
        const QList<std::tuple<const int, const QString, const QString,
            const double>> pieces) {
        const int id = model->insertCommission(commissionerId, dueDate, notes);
        for (int i = 0; i < pieces.length(); i++)
            model->insertPiece(id, std::get<0>(pieces[i]),
            std::get<1>(pieces[i]), std::get<2>(pieces[i]),
            std::get<3>(pieces[i]));
        commissionerRightPanel->updatePanel();
    }

    void MainWindow::insertPiece(const QString pieceName, const QString pieceNotes,
        const int productId, const QString productName,
        const double price) {
        model->insertPiece(model->getCommission()->record(0).value(0).toInt(),
            productId, pieceName, pieceNotes, price);
        commissionRightPanel->updatePanel();
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

    void MainWindow::newPayment(const QVariant &commission) {
        paymentPopup->setCommission(commission);
        paymentPopup->exec();
    }

    void MainWindow::newPiece() {
        piecePopup->exec();
    }

    void MainWindow::newRecord() {
        QString newFile = QFileDialog::getSaveFileName(this, tr("Create a new file"),
            "", tr("Commissioner Files (*.cdb)"));
        if (newFile != NULL) {
            QFileInfo file(newFile);
            if (file.exists())
                QFile::remove(newFile);
            model->open(newFile, true);
        }
    }

    void MainWindow::open() {
        if (model->hasBeenChanged()) {
            int ret = QMessageBox::question(this, tr("Save File?"),
                tr("The database has been modified.\n"
                "Would you like to save your changes?"),
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);
            if (ret == QMessageBox::Save)
                save();
            else if (ret == QMessageBox::Cancel)
                return;
        }
        QString openFile = QFileDialog::getOpenFileName(this, tr("Open File"),
            "", tr("Commissioner Files (*.cdb)"));
        if (openFile != NULL)
            model->open(openFile, false);
    }

    void MainWindow::recordClosed() { 
        toggleComponents(false);
    }

    void MainWindow::recordOpened() {
        toggleComponents(true);
    }

    void MainWindow::save() {
        model->save();
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
        //commissionerRightPanel->updatePanel();
    }

    void MainWindow::manageCommissions() {
        leftPanel->setCurrentWidget(commissionLeftPanel);
        rightPanel->setCurrentWidget(commissionRightPanel);
        swapContextToolBar(commissionToolBar);
        //commissionRightPanel->updatePanel();
    }

    void MainWindow::swapContextToolBar(QToolBar *newBar) {
        contextToolBar->setVisible(false);
        contextToolBar = newBar;
        contextToolBar->setVisible(true);
    }

    void MainWindow::toggleComponents(const bool isEnabled) {
        if (isEnabled) {
            createPanels();
            createPopups();

            connect(saveAct, &QAction::triggered,
                this, &MainWindow::save);
            connect(closeAct, &QAction::triggered,
                this, &MainWindow::closeRecord);
            connect(newCommissionerAct, &QAction::triggered,
                this, &MainWindow::newCommissioner);
            connect(newCommissionAct, &QAction::triggered,
                this, &MainWindow::newCommission);
            connect(newPaymentAct, &QAction::triggered,
                this, &MainWindow::newPayment);
            connect(manageCommissionerAct, &QAction::triggered,
                this, &MainWindow::manageCommissioners);
            connect(manageCommissionAct, &QAction::triggered,
                this, &MainWindow::manageCommissions);

            manageCommissioners();
            currentFile = "";
        } else {
            delete commissionerLeftPanel;
            delete commissionerRightPanel;
            delete commissionLeftPanel;
            delete commissionRightPanel;
            delete line;

            delete commissionPopup;
            delete commissionerPopup;
            delete paymentPopup;
            delete piecePopup;

            saveAct->disconnect();
            closeAct->disconnect();
            printRecordAct->disconnect();
            newCommissionerAct->disconnect();
            newCommissionAct->disconnect();
            newProductAct->disconnect();
            newSaleAct->disconnect();
            newPaymentAct->disconnect();
            manageStorefrontAct->disconnect();
            manageCommissionerAct->disconnect();
            manageCommissionAct->disconnect();
            managePieceAct->disconnect();
            managePaymentAct->disconnect();

            model->disconnect();
            connect(model, &ComModel::recordClosed,
                this, &MainWindow::recordClosed);
            connect(model, &ComModel::recordOpened,
                this, &MainWindow::recordOpened);
        }

        saveAct->setEnabled(isEnabled);
        closeAct->setEnabled(isEnabled);
        //printRecordAct->setEnabled(isEnabled);
        newCommissionerAct->setEnabled(isEnabled);
        newCommissionAct->setEnabled(isEnabled);
        //newProductAct->setEnabled(isEnabled);
        //newSaleAct->setEnabled(isEnabled);
        newPaymentAct->setEnabled(isEnabled);
        //manageStorefrontAct->setEnabled(isEnabled);
        manageCommissionerAct->setEnabled(isEnabled);
        manageCommissionAct->setEnabled(isEnabled);
        //managePieceAct->setEnabled(isEnabled);
        //managePaymentAct->setEnabled(isEnabled);
    }
}