#include <QHeaderView>
#include "NewCommissionWindow.h"

namespace Commissionator {

    NewCommissionWindow::NewCommissionWindow(QAbstractItemModel *namesModel,
        QAbstractItemModel *productsModel, QWidget *parent) : QDialog(parent) {
        init(namesModel, productsModel);
    }

    NewCommissionWindow::~NewCommissionWindow() {
        delete titleFont;
        delete font;
    }

    void NewCommissionWindow::closeEvent(QCloseEvent *e) {
        clear();
        QDialog::closeEvent(e);
    }

    void NewCommissionWindow::clear() {
        comBox->setEnabled(true);
        comBox->setCurrentIndex(-1);
        calendarEdit->setDate(QDate::currentDate());
        notesEdit->setText("");
        newPieceModel->removeRows(0, newPieceModel->rowCount());
    }

    void NewCommissionWindow::init(QAbstractItemModel *namesModel,
        QAbstractItemModel *productsModel) {
        pieceProductsModel = productsModel;

        mainLayout = new QVBoxLayout(this);
        comLayout = new QGridLayout(this);

        titleFont = new QFont();
        titleFont->setPointSize(12);
        titleFont->setBold(true);

        font = new QFont();
        font->setPointSize(10);

        newComLabel = new QLabel(this);
        newComLabel->setAlignment(Qt::AlignCenter);
        newComLabel->setFont(*titleFont);
        newComLabel->setText("Insert Commission");

        comLabel = new QLabel(this);
        comLabel->setFont(*font);
        comLabel->setText("Commissioner:");

        dueLabel = new QLabel(this);
        dueLabel->setFont(*font);
        dueLabel->setText("Due Date:");

        notesLabel = new QLabel(this);
        notesLabel->setFont(*font);
        notesLabel->setText("Notes:");

        pieceLabel = new QLabel(this);
        pieceLabel->setAlignment(Qt::AlignCenter);
        pieceLabel->setFont(*font);
        pieceLabel->setText("Commissioned Pieces:");

        comBox = new QComboBox(this); //just for testing purposes, going to have to eventually subclass combobox to get desired functionality
        comBox->setModel(namesModel);
        comBox->setModelColumn(1);
        
        calendarEdit = new QDateEdit(this);
        calendarEdit->setDate(QDate::currentDate());
        calendarEdit->setCalendarPopup(true);

        notesEdit = new QLineEdit(this);

        newPieceModel = new QStandardItemModel(this);
        newPieceModel->setHorizontalHeaderLabels(QStringList() 
            << "Product Id"
            << "Product"
            << "Name"
            << "Notes");

        newPieceView = new FixedRowTable(newPieceModel, this);
        pieceTypeDelegate = new ComboEditorDelegate(this);
        pieceTypeDelegate->setEditorModel(productsModel);
        pieceTypeDelegate->setDisplayColumn(1);
        pieceTypeDelegate->setColumn(1);
        newPieceView->setBoxDelegate(pieceTypeDelegate);
        //newPieceView->setBoxBottom(true);
        newPieceView->setBoxButtonActivated(true);
        newPieceView->setBoxButtonWidth(1.25);
        newPieceView->setBoxButtonText(tr("Insert"));
        newPieceView->setBoxText("Empty");
        newPieceView->setTableButtonActivated(true);
        newPieceView->setTableButtonIcon(":/Delete.png");
        newPieceView->setTableButtonSize(24);
        newPieceView->setSelectionMode(QAbstractItemView::NoSelection);
        newPieceView->openBoxPersistentEditor(1);
        newPieceView->setColumnHidden(0, true);
        connect(newPieceView, &FixedRowTable::boxQuery,
            this, &NewCommissionWindow::newPieceSlot);
        connect(newPieceView, &FixedRowTable::tableButtonClicked,
            this, &NewCommissionWindow::deletePieceSlot);

        for (int i = 0; i < newPieceView->model()->columnCount(); i++)
            newPieceView->horizontalHeader()->setSectionResizeMode(i,
            QHeaderView::Stretch);

        submitButton = new QPushButton(this);
        submitButton->setText("Submit Commission");
        connect(submitButton, &QPushButton::clicked, 
            this, &NewCommissionWindow::newCommissionSlot);

        mainLayout->addWidget(newComLabel);
        mainLayout->addLayout(comLayout);
        mainLayout->addWidget(pieceLabel);
        mainLayout->addWidget(newPieceView);
        mainLayout->addWidget(submitButton);

        comLayout->addWidget(comLabel, 0, 0);
        comLayout->addWidget(dueLabel, 1, 0);
        comLayout->addWidget(notesLabel, 2, 0);
        comLayout->addWidget(comBox, 0, 1);
        comLayout->addWidget(calendarEdit, 1, 1);
        comLayout->addWidget(notesEdit, 2, 1);

        setLayout(mainLayout);
    }

    void NewCommissionWindow::deletePieceSlot(const QModelIndex &index) {
        newPieceModel->removeRow(index.row());
    }

    void NewCommissionWindow::newCommissionSlot() {
        emit newCommission(
            comBox->model()->index(comBox->currentIndex(), 0).data().toInt(),
            calendarEdit->dateTime(),
            notesEdit->text());
        clear();
        emit done(0);
    }

    void NewCommissionWindow::newPieceSlot(const QList<QVariant> query) {
        if (query.length() == 4) {  //Product Id, Product Id (as name), Piece Name, Piece Notes
            int rowCount = newPieceModel->rowCount();
            newPieceModel->setItem(rowCount, 0,
                new QStandardItem(query[1].toString()));
            newPieceModel->setItem(rowCount, 1,
                new QStandardItem(pieceProductsModel->index(
                pieceProductsModel->match(
                    pieceProductsModel->index(0, 0),
                    Qt::EditRole,
                    query[1])[0].data().toInt(), 1).data().toString()));
            newPieceModel->setItem(rowCount, 2, new QStandardItem(query[2].toString()));
            newPieceModel->setItem(rowCount, 3, new QStandardItem(query[3].toString())); 
            /*QList<QStandardItem *> row;
            row << new QStandardItem(query[1].toString());
            row << new QStandardItem(pieceProductsModel->index(
                pieceProductsModel->match(
                pieceProductsModel->index(0, 0),
                Qt::DisplayRole,
                query[1])[0].data().toInt(), 1).data().toString());
            row << new QStandardItem(query[2].toString());
            row << new QStandardItem(query[3].toString());
            newPieceModel->insertRow(0, row);*/
            //newPieceView->setModel(newPieceModel);
        }
    }

    void NewCommissionWindow::setCommissioner(const QVariant &commissioner) {
        comBox->setModelColumn(0);
        int index = comBox->findText(commissioner.toString());
        if (index >= 0) {
            comBox->setCurrentIndex(index);
            comBox->setEnabled(false);
        }
        comBox->setModelColumn(1);
    }
}