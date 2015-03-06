#include <QHeaderView>
#include <QAbstractProxyModel>
#include "LeftPanel.h"
#include "LeftProxyModel.h"

namespace Commissionator {
    LeftPanel::LeftPanel(QString title, QSqlTableModel *model, QList<int> hiddenColumns) {
        layout = new QVBoxLayout();
        createTitle(title);
        createTable(model, hiddenColumns);
        layout->addWidget(titleLabel);
        layout->addWidget(view);
        setLayout(layout);
        connect(view, &QTableView::clicked, this, &LeftPanel::tableClicked);
    }

    void LeftPanel::createTitle(QString title) {
        titleLabel = new QLabel(title);
        titleLabel->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        titleLabel->setFont(font);
    }

    void LeftPanel::createTable(QSqlTableModel *model, QList<int> hiddenColumns) {
        view = new QTableView();
        LeftProxyModel *proxy = new LeftProxyModel(this);
        proxy->setSourceModel(model);
        view->setModel(proxy);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);
        view->setEditTriggers(QAbstractItemView::AllEditTriggers);
        view->verticalHeader()->hide();
        view->setSortingEnabled(true);
        foreach(int col, hiddenColumns) {
            view->setColumnHidden(col, true);
        }
        for (int col = 0; col < view->horizontalHeader()->count(); col++) {
            view->horizontalHeader()->setSectionResizeMode(col, QHeaderView::Stretch);
        }
    }
}