#include <QHeaderView>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QDateEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTableView>
#include "NewCommissionWindow.h"

namespace Commissionator {

    NewCommissionWindow::NewCommissionWindow(QAbstractItemModel *commissionsModel, 
        QAbstractItemModel *namesModel,
        QAbstractItemModel *productsModel, QWidget *parent) :
        BaseNewWindow(parent) {

        mainLayout = new QVBoxLayout(this);
        comLayout = new QGridLayout();

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

        comBox = new QComboBox(this);
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
            << "Notes"
            << "Override");

        newPieceView = new QTableView(this);
        newPieceView->setModel(newPieceModel);
        delegate = new FixedRowTableDelegate(this);
        delegate->setIcon(":/Delete.png");
        delegate->setIconSize(24);
        newPieceView->setItemDelegate(delegate);
        newPieceView->setSelectionMode(QAbstractItemView::NoSelection);
        newPieceView->setColumnHidden(0, true);
        connect(delegate, &FixedRowTableDelegate::buttonClicked,
            this, &NewCommissionWindow::deletePieceSlot);

        for (int i = 0; i < newPieceView->model()->columnCount(); i++)
            newPieceView->horizontalHeader()->setSectionResizeMode(i,
            QHeaderView::Stretch);

        piecePopup = new NewPieceWindow(commissionsModel, productsModel, this);
        connect(piecePopup, &NewPieceWindow::newPiece,
            this, &NewCommissionWindow::newPieceSlot);

        newPieceButton = new QPushButton(this);
        newPieceButton->setText("Add Piece");
        connect(newPieceButton, &QPushButton::clicked,
            piecePopup, &NewPieceWindow::exec);

        submitButton = new QPushButton(this);
        submitButton->setText("Submit Commission");
        connect(submitButton, &QPushButton::clicked,
            this, &NewCommissionWindow::newItemSlot);

        mainLayout->addWidget(newComLabel);
        mainLayout->addLayout(comLayout);
        mainLayout->addWidget(pieceLabel);
        mainLayout->addWidget(newPieceView);
        mainLayout->addWidget(newPieceButton);
        mainLayout->addWidget(submitButton);

        comLayout->addWidget(comLabel, 0, 0);
        comLayout->addWidget(dueLabel, 1, 0);
        comLayout->addWidget(notesLabel, 2, 0);
        comLayout->addWidget(comBox, 0, 1);
        comLayout->addWidget(calendarEdit, 1, 1);
        comLayout->addWidget(notesEdit, 2, 1);
    }
    
    NewCommissionWindow::~NewCommissionWindow() {
        delete comLayout;
    }

    void NewCommissionWindow::clear() {
        comBox->setEnabled(true);
        comBox->setCurrentIndex(-1);
        calendarEdit->setDate(QDate::currentDate());
        notesEdit->setText("");
        newPieceModel->removeRows(0, newPieceModel->rowCount());
    }

    void NewCommissionWindow::deletePieceSlot(const QModelIndex &index) {
        newPieceModel->removeRow(index.row());
    }

    void NewCommissionWindow::newItemSlot() {
        if (comBox->currentIndex() > -1) {
            QList<std::tuple<const int, const QString, const QString, const double>> pieces;
            for (int i = 0; i < newPieceModel->rowCount(); i++) {
                double price = -1;
                if (newPieceModel->index(i, 4).data().toString() != "N/A")
                    price = newPieceModel->index(i, 4).data().toString().toDouble();
                pieces << std::make_tuple(
                    newPieceModel->index(i, 0).data().toInt(),
                    newPieceModel->index(i, 2).data().toString(),
                    newPieceModel->index(i, 3).data().toString(),
                    price);
            }
            emit newCommission(
                comBox->model()->index(comBox->currentIndex(), 0).data().toInt(),
                calendarEdit->dateTime(),
                notesEdit->text(),
                pieces);
            BaseNewWindow::newItemSlot();
        }  
    }

    void NewCommissionWindow::newPieceSlot(const QString pieceName, 
        const QString pieceNotes, const int productId, 
        const QString productName, const double price) {
        QList<QStandardItem *> row;
        row << new QStandardItem(QString::number(productId));
        row << new QStandardItem(productName);
        row << new QStandardItem(pieceName);
        row << new QStandardItem(pieceNotes);
        if (price > -1)
            row << new QStandardItem(QString::number(price));
        else 
            row << new QStandardItem("N/A");
        newPieceModel->appendRow(row);
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