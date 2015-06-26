#include "ProductPanel.h"
#include <QSqlQueryModel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QSqlRecord>
#include "FixedRowTable.h"

namespace Commissionator {
    ProductPanel::ProductPanel(QSqlQueryModel *productModel,
        //QSqlQueryModel *productOptionsModel,
        QSqlQueryModel *piecesSoldModel, QWidget *parent) : RightPanel(parent) {
        this->productModel = productModel;

        createLabels();
        createButtons();
        createTables(/*productOptionsModel, */piecesSoldModel);
        createPanel();
    }


    void ProductPanel::createButtons() {
        unlockButton = new QPushButton(this);
        unlockButton->setIcon(QIcon(":/NewFile.png"));
        unlockButton->hide();
        connect(unlockButton, &QPushButton::clicked,
            this, &ProductPanel::toggleEdit);
    }

    void ProductPanel::createLabels() {
        productName = new QLabel(this);
        productName->setAlignment(Qt::AlignCenter);
        productName->setFont(*titleFont);

        productNameEdit = new QLineEdit(this);
        connect(productNameEdit, &QLineEdit::returnPressed,
            this, &ProductPanel::toggleEdit);
        productNameEdit->hide();

        numberProduced = new QLabel(this);
        numberProduced->setAlignment(Qt::AlignCenter);
        numberProduced->setFont(*standardFont);

        basePrice = new QLabel(this);
        basePrice->setAlignment(Qt::AlignCenter);
        basePrice->setFont(*standardFont);

        basePriceEdit = new QDoubleSpinBox(this);
        basePriceEdit->setDecimals(2);
        basePriceEdit->setMinimum(0);
        basePriceEdit->setMaximum(999999);
        basePriceEdit->hide();

        productOptionsLabel = new QLabel(this);
        productOptionsLabel->setAlignment(Qt::AlignCenter);
        productOptionsLabel->setFont(*standardFont);

        piecesSoldLabel = new QLabel(this);
        piecesSoldLabel->setAlignment(Qt::AlignCenter);
        piecesSoldLabel->setFont(*standardFont);
    }

    void ProductPanel::createPanel() {
        layout = new QVBoxLayout(this);
        titleLayout = new QGridLayout();

        titleLayout->addWidget(productName, 0, 4);
        titleLayout->addWidget(productNameEdit, 0, 4);
        titleLayout->addWidget(unlockButton, 0, 8);
        titleLayout->setColumnStretch(0, 1);
        titleLayout->setColumnStretch(1, 1);
        titleLayout->setColumnStretch(2, 1);
        titleLayout->setColumnStretch(3, 1);
        titleLayout->setColumnStretch(4, 1);
        titleLayout->setColumnStretch(5, 1);
        titleLayout->setColumnStretch(6, 1);
        titleLayout->setColumnStretch(7, 1);
        titleLayout->setColumnStretch(8, 1);

        layout->addLayout(titleLayout);
        layout->addWidget(numberProduced);
        layout->addWidget(basePrice);
        layout->addWidget(basePriceEdit);
        //layout->addWidget(productOptionsLabel);
        //layout->addWidget(productOptionsTable);
        layout->addWidget(piecesSoldLabel);
        layout->addWidget(piecesSoldTable);
    }

    void ProductPanel::createTables(//QSqlQueryModel *productOptionsModel,
        QSqlQueryModel *piecesSoldModel) {
        piecesSoldTable = new QTableView(this);
        piecesSoldTable->setModel(piecesSoldModel);
        piecesSoldTable->setSelectionMode(QAbstractItemView::NoSelection);
        piecesSoldTable->hide();
    }

    void ProductPanel::insertProductOptionSlot(const QList<QVariant> query) {
        if (query.length() == 4)    //product id, option name, option price, is numeric
            emit insertProductOption(query[0].toInt(), query[1].toString(),
            query[2].toDouble(), query[3].toBool());
    }

    void ProductPanel::toggleEdit() {
        if (productName->isHidden()) {
            if (productNameEdit->text() != productName->text())
                emit editName(productModel->record(0).value(0).toInt(), 
                    productNameEdit->text());
            if (basePriceEdit->text() != basePrice->text())
                emit editPrice(productModel->record(0).value(0).toInt(), 
                    basePriceEdit->text().toInt());
            updatePanel();
        } else {
            productName->hide();
            productNameEdit->show();
            basePrice->hide();
            basePriceEdit->show();
        }
    }

    void ProductPanel::updatePanel() {

    }
}