#include <QHeaderView>
#include <QAbstractProxyModel>
#include <QVBoxLayout>
#include <QSqlQueryModel>
#include <QLabel>
#include <QVariant>
#include "FixedRowTable.h"
#include "LeftPanel.h"


namespace Commissionator {
    LeftPanel::LeftPanel(QString title, QSqlQueryModel *model, 
        QList<int> hiddenColumns, QWidget *parent) : QWidget(parent) {
        layout = new QVBoxLayout(this);
        createTitle(title);
        createTable(model, hiddenColumns);
        layout->addWidget(titleLabel);
        layout->addWidget(view);
        setLayout(layout);
        connect(view, &FixedRowTable::boxQuery, this, &LeftPanel::search);
        connect(view, &FixedRowTable::tableButtonClicked, this, &LeftPanel::iconClicked);
        connect(view, &FixedRowTable::clicked, this, &LeftPanel::tableClicked);
    }

    void LeftPanel::createTitle(QString title) {
        titleLabel = new QLabel(title, this);
        titleLabel->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        titleLabel->setFont(font);
    }

    void LeftPanel::createTable(QSqlQueryModel *model, QList<int> hiddenColumns) {
        view = new FixedRowTable(model, this);
        view->setTableButtonActivated(true);
        view->setTableButtonIcon(":/Delete.png");
        view->setTableButtonSize(24);
        view->setBoxText("Search");
        view->setSelectionMode(QAbstractItemView::NoSelection);

        foreach(int i, hiddenColumns)
            view->setColumnHidden(i, true);

        for (int i = 0; i < view->model()->columnCount() - 1; ++i)
            view->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
        view->horizontalHeader()->setSectionResizeMode(
            view->model()->columnCount() - 1, 
            QHeaderView::Stretch);
    }
}