#include <QHeaderView>
#include <QScrollBar>
#include <QKeyEvent>
#include "SearchTableDelegate.h"
#include "SearchTableView.h"

namespace Commissionator {
    SearchTableView::SearchTableView(QAbstractItemModel *model) {
        proxy = new SearchProxyModel(this); 
        proxy->setSourceModel(model);
        
        init();

        connect(horizontalHeader(), &QHeaderView::sectionResized, this, &SearchTableView::updateSectionWidth);
        connect(verticalHeader(), &QHeaderView::sectionResized, this, &SearchTableView::updateSectionHeight);
        connect(searchBox->horizontalScrollBar(), &QScrollBar::valueChanged, horizontalScrollBar(), &QScrollBar::setValue);
        connect(horizontalScrollBar(), &QScrollBar::valueChanged, searchBox->horizontalScrollBar(), &QScrollBar::setValue);
    }

    SearchTableView::~SearchTableView() {
        delete searchBox;
        delete proxy;
    }

    void SearchTableView::resizeEvent(QResizeEvent * event) {
        QTableView::resizeEvent(event);
        updateSearchBoxGeometry();
    }

    void SearchTableView::scrollTo(const QModelIndex &index, ScrollHint hint) {
        if (index.row() > 0)
            QTableView::scrollTo(index, hint);
    }

    void SearchTableView::init() {
        setModel(proxy);
        searchBox = new SearchBoxView(this);
        searchBox->setModel(proxy);
        
        setFocusPolicy(Qt::StrongFocus);
        viewport()->stackUnder(searchBox);
        updateSearchBoxGeometry();

        setHorizontalScrollMode(ScrollPerPixel);
        setVerticalScrollMode(ScrollPerPixel);

        setSelectionBehavior(QAbstractItemView::SelectRows);
        SearchTableDelegate *delegate = new SearchTableDelegate();
        delegate->setIconSize(24);
        setItemDelegate(delegate);

        setEditTriggers(QAbstractItemView::AllEditTriggers);
        verticalHeader()->hide();
        setSortingEnabled(true);

        for (int col = 0; col < horizontalHeader()->count(); col++) {
            horizontalHeader()->setSectionResizeMode(col, QHeaderView::Stretch);
        }
    }

    void SearchTableView::updateSearchBoxGeometry() {
        searchBox->setGeometry(verticalHeader()->width() + frameWidth(),
            horizontalHeader()->height() + frameWidth(), viewport()->width() + verticalHeader()->width(), rowHeight(0));
    }
    
    void SearchTableView::updateSectionWidth(int logicalIndex, int /**oldSize*/, int newSize) {
        searchBox->setColumnWidth(logicalIndex, newSize);
    }

    void SearchTableView::updateSectionHeight(int logicalIndex, int /**oldSize*/, int newSize) {
        if (logicalIndex == 0) {
            searchBox->setRowHeight(logicalIndex, newSize);
            updateSearchBoxGeometry();
        }
    }
}