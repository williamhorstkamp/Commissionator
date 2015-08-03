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
#include <QCloseEvent>
#include "LeftPanel.h"
#include "StoreFrontPanel.h"
#include "NewCommissionWindow.h"
#include "NewCommissionerWindow.h"
#include "NewPaymentWindow.h"
#include "NewPieceWindow.h"
#include "NewProductWindow.h"
#include "NewRefundWindow.h"
#include "OptionsDialog.h"
#include "CommissionerPanel.h"
#include "CommissionPanel.h"
#include "PiecePanel.h"
#include "ProductPanel.h"
#include "ComModel.h"
#include "mainwindow.h"

namespace Commissionator{
    MainWindow::MainWindow() {
        createModel();
        createActions();
        createMenus();
        createStatusBar();
        createToolBars();

        setMinimumSize(1024, 768);
        setWindowIcon(QIcon(":/Commissionator.png"));
    }

    void MainWindow::closeEvent(QCloseEvent *event) {
        if (model->hasBeenChanged()) {
            int ret = QMessageBox::question(this, tr("Save File?"),
                tr("The database has been modified.\n"
                "Would you like to save your changes?"),
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);
            if (ret == QMessageBox::Save) {
                save();
            } else if (ret == QMessageBox::Cancel)
                event->ignore();
        }
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
        //newMenu->addAction(newSaleAct);   //not implemented
        newMenu->addAction(newPaymentAct);

        manageMenu = menuBar()->addMenu(tr("&Manage"));
        manageMenu->addAction(manageOptionsAct);
        manageMenu->addAction(manageStorefrontAct);
        manageMenu->addAction(manageCommissionerAct);
        manageMenu->addAction(manageCommissionAct);
        manageMenu->addAction(managePieceAct);

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
        
        newCommissionerAct = new QAction(QIcon(":/CommissionerPlus.png"), tr("&New Commissioner"), this);
        newCommissionerAct->setStatusTip(tr("Create a new commissioner"));
        newCommissionerAct->setEnabled(false);

        newCommissionAct = new QAction(QIcon(":/CommissionPlus.png"), tr("&New Commission"), this);
        newCommissionAct->setStatusTip(tr("Create a new commission"));
        newCommissionAct->setEnabled(false);

        newProductAct = new QAction(QIcon(":/ProductPlus.png"), tr("&New Product"), this);
        newProductAct->setStatusTip(tr("Create a new product"));
        newProductAct->setEnabled(false);

        newSaleAct = new QAction(QIcon(":/SalePlus.png"), tr("&New Sale"), this);
        newSaleAct->setStatusTip(tr("Create a new sale"));
        newSaleAct->setEnabled(false);

        newPaymentAct = new QAction(QIcon(":/PaymentPlus.png"), tr("&New Payment"), this);
        newPaymentAct->setStatusTip(tr("Create a new payment"));
        newPaymentAct->setEnabled(false);

        manageOptionsAct = new QAction(QIcon(":/Options.png"), tr("&Store Options"), this);
        manageOptionsAct->setStatusTip(tr("Manage store options"));
        manageOptionsAct->setEnabled(false);

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
        commissionerToolBar->addAction(newCommissionerAct);
        commissionerToolBar->setMovable(false);
        contextToolBar = commissionerToolBar;
        commissionToolBar = addToolBar(tr("Commission"));
        commissionToolBar->addAction(newCommissionAct);
        commissionToolBar->setMovable(false);
        commissionToolBar->setVisible(false);
        pieceToolBar = addToolBar(tr("Piece"));
        pieceToolBar->setMovable(false);
        pieceToolBar->setVisible(false);
        storefrontToolBar = addToolBar(tr("StoreFront"));
        storefrontToolBar->addAction(newProductAct);
        storefrontToolBar->setMovable(false);
        storefrontToolBar->setVisible(false);
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
        pieceLeftPanel = new LeftPanel("Piece",
            model->getPieces(), hidden);
        storefrontLeftPanel = new StoreFrontPanel(model->getProducts());
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
        pieceRightPanel = new PiecePanel(
            model->getPiece(),
            model->getPieceEvents());
        productRightPanel = new ProductPanel(
            model->getProduct(), 
            model->getProductEvents(),
            model->getProductPiecesSold(), 
            this);

        leftPanel->addWidget(commissionerLeftPanel);
        leftPanel->addWidget(commissionLeftPanel);
        leftPanel->addWidget(pieceLeftPanel);
        leftPanel->addWidget(storefrontLeftPanel);
        rightPanel->addWidget(commissionerRightPanel);
        rightPanel->addWidget(commissionRightPanel);
        rightPanel->addWidget(pieceRightPanel);
        rightPanel->addWidget(productRightPanel);

        connect(commissionerLeftPanel, &LeftPanel::tableClicked,
            model, &ComModel::setCommissioner);
        connect(commissionerLeftPanel, &LeftPanel::search,
            this, &MainWindow::searchCommissioners);
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
        connect(commissionerRightPanel, &CommissionerPanel::edit,
            model, &ComModel::editCommissioner);
        connect(commissionerRightPanel, &CommissionerPanel::setCommission,
            model, &ComModel::setCommission);
        connect(commissionerRightPanel, &CommissionerPanel::setCommission,
            this, &MainWindow::manageCommissions);

        connect(commissionLeftPanel, &LeftPanel::tableClicked,
            model, &ComModel::setCommission);
        connect(commissionLeftPanel, &LeftPanel::search,
            this, &MainWindow::searchCommissions);
        connect(commissionLeftPanel, &LeftPanel::iconClicked,
            model, &ComModel::deleteCommission);

        connect(model, &ComModel::commissionChanged,
            commissionRightPanel, &CommissionPanel::updatePanel);
        connect(commissionRightPanel, &CommissionPanel::deletePiece,
            model, &ComModel::deletePiece);
        connect(commissionRightPanel, &CommissionPanel::edit,
            model, &ComModel::editCommission);
        connect(commissionRightPanel, &CommissionPanel::newPayment,
            this, &MainWindow::newPayment);
        connect(commissionRightPanel, &CommissionPanel::newRefund,
            this, &MainWindow::newRefund);
        connect(commissionRightPanel, &CommissionPanel::newPiece,
            this, &MainWindow::newPiece);
        connect(commissionRightPanel, &CommissionPanel::setPiece,
            model, &ComModel::setPiece);
        connect(commissionRightPanel, &CommissionPanel::setPiece,
            this, &MainWindow::managePieces);

        connect(pieceLeftPanel, &LeftPanel::tableClicked,
            model, &ComModel::setPiece);
        connect(pieceLeftPanel, &LeftPanel::search,
            this, &MainWindow::searchPieces);
        connect(pieceLeftPanel, &LeftPanel::iconClicked,
            model, &ComModel::deletePiece);

        connect(model, &ComModel::pieceChanged,
            pieceRightPanel, &PiecePanel::updatePanel);
        connect(pieceRightPanel, &PiecePanel::edit,
            model, &ComModel::editPiece);

        connect(storefrontLeftPanel, &StoreFrontPanel::productTableClicked,
            model, &ComModel::setProduct);
        connect(storefrontLeftPanel, &StoreFrontPanel::productSearch,
            this, &MainWindow::searchProducts);
        connect(storefrontLeftPanel, &StoreFrontPanel::productDelete,
            model, &ComModel::deleteProduct);

        connect(model, &ComModel::productChanged,
            productRightPanel, &ProductPanel::updatePanel);
        connect(productRightPanel, &ProductPanel::editAvailability,
            model, &ComModel::editProductAvailability);
        connect(productRightPanel, &ProductPanel::edit,
            model, &ComModel::editProduct);
        connect(productRightPanel, &ProductPanel::searchProductPieces,
            model, &ComModel::searchProductPieces);
        connect(productRightPanel, &ProductPanel::deleteProductEvent,
            model, &ComModel::deleteProductEvent);
        connect(productRightPanel, &ProductPanel::setPiece,
            model, &ComModel::setPiece);
        connect(productRightPanel, &ProductPanel::setPiece,
            this, &MainWindow::managePieces);

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
        productPopup = new NewProductWindow(this);
        connect(productPopup, &NewProductWindow::newProduct,
            this, &MainWindow::insertProduct);
        refundPopup = new NewRefundWindow(model->getCommissionList(), this);
        connect(refundPopup, &NewRefundWindow::newRefund,
            model, &ComModel::insertRefund);
        optionsPopup = new OptionsDialog(model->getContactTypes(), 
            model->getPaymentTypes(), this);
        connect(model, &ComModel::optionChanged,
            optionsPopup, &OptionsDialog::updateGeometry);
        connect(optionsPopup, &OptionsDialog::deleteContactType,
            model, &ComModel::deleteContactType);
        connect(optionsPopup, &OptionsDialog::insertContactType,
            model, &ComModel::insertContactType);
        connect(optionsPopup, &OptionsDialog::deletePaymentType,
            model, &ComModel::deletePaymentType);
        connect(optionsPopup, &OptionsDialog::insertPaymentType,
            model, &ComModel::insertPaymentType);
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
    }

    void MainWindow::insertPiece(const QString pieceName, const QString pieceNotes,
        const int productId, const QString productName,
        const double price) {
        model->insertPiece(model->getCommission()->record(0).value(0).toInt(),
            productId, pieceName, pieceNotes, price);
    }

    void MainWindow::insertProduct(const QString productName, const double basePrice,
        QList<QString> events) {
        const int id = model->insertProduct(productName, basePrice);
        for (int i = 0; i < events.length(); i++)
            model->insertProductEvent(id, events[i]);
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

    void MainWindow::newProduct() {
        productPopup->exec();
    }

    void MainWindow::newRefund(const QVariant &commission) {
        refundPopup->setCommission(commission);
        refundPopup->exec();
    }

    void MainWindow::newRecord() {
        QString newFile = QFileDialog::getSaveFileName(this, tr("Create a new file"),
            "", tr("Commissioner Files (*.cdb)"));
        if (newFile != NULL) {
            QFileInfo file(newFile);
            if (file.exists()) {
                model->close();
                QFile::remove(newFile);
            }     
            model->open(newFile, true);
        }
    }

    void MainWindow::open() {
        if (model->hasBeenChanged()) {
            switch (QMessageBox::question(this, tr("Save File?"),
                tr("The database has been modified.\n"
                "Would you like to save your changes?"),
                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                QMessageBox::Save)) {
            case QMessageBox::Save:
                save();
                break;
            case QMessageBox::Cancel:
                return;
            default:    //discard was hit
                break;
            }
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

    void MainWindow::searchCommissions(const QList<QVariant> query) {
        if (query.length() == 7)    //id, commissioner, create date, paid date, due date, piece count, finish date
            model->searchCommissions(query[1].toString(), query[2].toString(),
            query[3].toString(), query[4].toString(), query[5].toString(),
            query[6].toString());
    }

    void MainWindow::searchCommissioners(const QList<QVariant> query) {
        if (query.length() == 5)    //id, name, commissioner since, amounted owed, notes
            model->searchCommissioners(query[1].toString(), query[2].toString(),
            query[3].toString(), query[4].toString());
    }

    void MainWindow::searchPieces(const QList<QVariant> query) {
        if (query.length() == 6)    //id, commissioner, piece, product, create, finish
            model->searchPieces(query[1].toString(), query[2].toString(),
            query[3].toString(), query[4].toString(), query[5].toString());
    }

    void MainWindow::searchProducts(const QList<QVariant> query) {
        if (query.length() == 5)    //id, name, base price, number produced
            model->searchProducts(query[1].toString(), query[2].toString(),
            query[3].toString());
    }

    void MainWindow::manageCommissioners() {
        leftPanel->setCurrentWidget(commissionerLeftPanel);
        rightPanel->setCurrentWidget(commissionerRightPanel);
        swapContextToolBar(commissionerToolBar);
        commissionerRightPanel->updatePanel();
    }

    void MainWindow::manageCommissions() {
        leftPanel->setCurrentWidget(commissionLeftPanel);
        rightPanel->setCurrentWidget(commissionRightPanel);
        swapContextToolBar(commissionToolBar);
        commissionRightPanel->updatePanel();
    }

    void MainWindow::manageOptions() {
        optionsPopup->exec();
    }

    void MainWindow::managePieces() {
        leftPanel->setCurrentWidget(pieceLeftPanel);
        rightPanel->setCurrentWidget(pieceRightPanel);
        swapContextToolBar(pieceToolBar);
        pieceRightPanel->updatePanel();
    }

    void MainWindow::manageStoreFront() {
        leftPanel->setCurrentWidget(storefrontLeftPanel);
        rightPanel->setCurrentWidget(productRightPanel);
        swapContextToolBar(storefrontToolBar);
        productRightPanel->updatePanel();
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
            connect(newProductAct, &QAction::triggered,
                this, &MainWindow::newProduct);
            connect(manageOptionsAct, &QAction::triggered,
                this, &MainWindow::manageOptions);
            connect(manageCommissionerAct, &QAction::triggered,
                this, &MainWindow::manageCommissioners);
            connect(manageCommissionAct, &QAction::triggered,
                this, &MainWindow::manageCommissions);
            connect(managePieceAct, &QAction::triggered,
                this, &MainWindow::managePieces);
            connect(manageStorefrontAct, &QAction::triggered,
                this, &MainWindow::manageStoreFront);

            manageCommissioners();
            currentFile = "";
        } else {
            delete commissionerLeftPanel;
            delete commissionerRightPanel;
            delete commissionLeftPanel;
            delete commissionRightPanel;
            delete pieceLeftPanel;
            delete pieceRightPanel;
            delete productRightPanel;
            delete storefrontLeftPanel;

            delete line;

            delete commissionPopup;
            delete commissionerPopup;
            delete paymentPopup;
            delete piecePopup;
            delete productPopup;
            delete refundPopup;
            delete optionsPopup;

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
            manageOptionsAct->disconnect();

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
        newProductAct->setEnabled(isEnabled);
        //newSaleAct->setEnabled(isEnabled);
        newPaymentAct->setEnabled(isEnabled);
        manageOptionsAct->setEnabled(isEnabled);
        manageStorefrontAct->setEnabled(isEnabled);
        manageCommissionerAct->setEnabled(isEnabled);
        manageCommissionAct->setEnabled(isEnabled);
        managePieceAct->setEnabled(isEnabled);
    }
}