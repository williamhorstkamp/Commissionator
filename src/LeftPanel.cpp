#include <QHeaderView>
#include <QAbstractProxyModel>
#include "LeftPanel.h"


namespace Commissionator {
    LeftPanel::LeftPanel(QString title, QSqlQueryModel *model, QList<int> hiddenColumns) {
        layout = new QVBoxLayout();
        createTitle(title);
        createTable(model, hiddenColumns);
        layout->addWidget(titleLabel);
        layout->addWidget(view);
        setLayout(layout);
        connect(view, &SearchTableView::searchSignal, this, &LeftPanel::search);
        connect(view, &SearchTableView::iconClicked, this, &LeftPanel::iconClicked);
        connect(view, &SearchTableView::clicked, this, &LeftPanel::tableClicked);
    }

    LeftPanel::~LeftPanel() {
        delete layout;
        delete view;
        delete titleLabel;
    }

    void LeftPanel::createTitle(QString title) {
        titleLabel = new QLabel(title);
        titleLabel->setAlignment(Qt::AlignCenter);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        titleLabel->setFont(font);
    }

    void LeftPanel::createTable(QSqlQueryModel *model, QList<int> hiddenColumns) {
        view = new SearchTableView(model);
        
        foreach(int col, hiddenColumns) {
            view->setColumnHidden(col, true);
        }
        
    }
}