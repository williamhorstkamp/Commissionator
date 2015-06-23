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
        createTitle();
        createTables(productsModel);
        layout->addWidget(titleLabel);
        layout->addWidget(productTable);
        setLayout(layout);
        connect(productTable, &FixedRowTable::boxQuery, this, &StoreFrontPanel::productSearch);
        connect(productTable, &QTableView::clicked, this, &StoreFrontPanel::productTableClicked);
    }

    void StoreFrontPanel::createTitle() {
        titleLabel = new QLabel("StoreFront", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        titleLabel->setFont(font);
    }

    void StoreFrontPanel::createTables(QSqlQueryModel *productModel) {
        productTable = new FixedRowTable(productModel, this);
        productTable->setBoxText("Search");
        productTable->setSelectionMode(QAbstractItemView::NoSelection);

        productTable->setColumnHidden(0, true);

        for (int i = 0; i < productTable->model()->columnCount() - 1; ++i)
            productTable->horizontalHeader()->setSectionResizeMode(
                i, QHeaderView::ResizeToContents);
        productTable->horizontalHeader()->setSectionResizeMode(
            productTable->model()->columnCount() - 1,
            QHeaderView::Stretch);
    }
}