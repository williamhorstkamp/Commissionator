#include <QHeaderView>
#include <QAbstractProxyModel>
#include <QVBoxLayout>
#include <QSqlQueryModel>
#include <QLabel>
#include "FixedRowTable.h"
#include "StoreFrontPanel.h"


namespace Commissionator {
    StoreFrontPanel::StoreFrontPanel(QSqlQueryModel *productsModel,
        QWidget *parent) : QWidget(parent) {
        layout = new QVBoxLayout(this);
        createLabels();
        createTables(productsModel);
        line = new QFrame(this);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        layout->addWidget(titleLabel);
        layout->addWidget(line);
        layout->addWidget(productLabel);
        layout->addWidget(productTable);
        setLayout(layout);
        connect(productTable, &FixedRowTable::boxQuery, this, &StoreFrontPanel::productSearch);
        connect(productTable, &FixedRowTable::clicked, this, &StoreFrontPanel::productTableClicked);
        connect(productTable, &FixedRowTable::tableButtonClicked, this, &StoreFrontPanel::productDelete);
    }

    void StoreFrontPanel::createLabels() {
        QFont titleFont;
        titleFont.setPointSize(12);
        titleFont.setBold(true);
        QFont font;
        font.setPointSize(10);
        titleLabel = new QLabel("StoreFront", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setFont(titleFont);
        productLabel = new QLabel("Products:", this);
        productLabel->setAlignment(Qt::AlignCenter);
        productLabel->setFont(font);
    }

    void StoreFrontPanel::createTables(QSqlQueryModel *productModel) {
        productTable = new FixedRowTable(productModel, this);
        productTable->setTableButtonActivated(true);
        productTable->setTableButtonIcon(":/Delete.png");
        productTable->setTableButtonSize(24);
        productTable->setBoxText("Search");
        productTable->setSelectionMode(QAbstractItemView::NoSelection);
        productTable->setDeleteMessage("Toggle availability? \n"
            "Will delete product if no pieces for it exist.");

        productTable->setColumnHidden(0, true);

        for (int i = 0; i < productTable->model()->columnCount() - 1; ++i)
            productTable->horizontalHeader()->setSectionResizeMode(
                i, QHeaderView::ResizeToContents);
        productTable->horizontalHeader()->setSectionResizeMode(
            productTable->model()->columnCount() - 1,
            QHeaderView::Stretch);
    }
}