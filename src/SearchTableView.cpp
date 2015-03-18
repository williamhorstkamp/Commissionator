#include <QHeaderView>
#include <QScrollBar>
#include <QKeyEvent>
#include "SearchTableView.h"

namespace Commissionator {
    SearchTableView::SearchTableView(QAbstractItemModel *model) {
        createProxy();
        proxy->setSourceModel(model);
        
        init();
    }

    SearchTableView::~SearchTableView() {
        delete searchBox;
        delete proxy;
        delete delegate;
    }

    void SearchTableView::setColumnHidden(int column, bool hide) {
        QTableView::setColumnHidden(column, hide);
        searchBox->setColumnHidden(column, hide);
    }

    QModelIndex SearchTableView::moveCursor(CursorAction cursorAction,
        Qt::KeyboardModifiers modifiers) {
        QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);
        if (current.row() == 0)
            return QModelIndex();
        return current;
    }

    void SearchTableView::resizeEvent(QResizeEvent * event) {
        QTableView::resizeEvent(event);
        updateSearchBoxGeometry();
    }

    void SearchTableView::scrollTo(const QModelIndex &index, ScrollHint hint) {
        if (index.row() > 0)
            QTableView::scrollTo(index, hint);
    }

    void SearchTableView::createConnections() {
        connect(horizontalHeader(), &QHeaderView::sectionResized, this, &SearchTableView::updateSectionWidth);
        connect(verticalHeader(), &QHeaderView::sectionResized, this, &SearchTableView::updateSectionHeight);
        connect(searchBox->horizontalScrollBar(), &QScrollBar::valueChanged, horizontalScrollBar(), &QScrollBar::setValue);
        connect(horizontalScrollBar(), &QScrollBar::valueChanged, searchBox->horizontalScrollBar(), &QScrollBar::setValue);
        connect(proxy, &FixedRowProxyModel::querySignal, this, &SearchTableView::searchSignal);
        connect(delegate, &SearchTableDelegate::iconClicked, this, &SearchTableView::iconClicked);
        connect(searchBox, &SearchBoxView::searchSignal, proxy, &FixedRowProxyModel::query);
    }

    void SearchTableView::createDelegate() {
        delegate = new SearchTableDelegate();
        delegate->setIconSize(24);
        setItemDelegate(delegate);
    }

    void SearchTableView::createProxy() {
        proxy = new FixedRowProxyModel(this);
        proxy->setText("Search");
    }

    void SearchTableView::createSearchBox() {
        searchBox = new SearchBoxView(this);
        searchBox->setModel(proxy);
        viewport()->stackUnder(searchBox);
        searchBox->setSelectionModel(selectionModel());
        searchBox->setColumnWidth(0, columnWidth(0));
        updateSearchBoxGeometry();
    }
    
    void SearchTableView::createTable() {
        setModel(proxy);
        setFocusPolicy(Qt::StrongFocus);
        setHorizontalScrollMode(ScrollPerPixel);
        setVerticalScrollMode(ScrollPerPixel);
        setSelectionMode(QAbstractItemView::NoSelection);
        setSelectionBehavior(QAbstractItemView::SelectRows);
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        verticalHeader()->hide();
        setSortingEnabled(true);

        for (int col = 0; col < horizontalHeader()->count(); col++)
            horizontalHeader()->setSectionResizeMode(col, QHeaderView::Stretch);
    }

    void SearchTableView::init() {
        createTable();
        createSearchBox();
        createDelegate();
        createConnections();
    }

    void SearchTableView::updateSearchBoxGeometry() {
        searchBox->setGeometry(verticalHeader()->width() + frameWidth(),
            horizontalHeader()->height() + frameWidth(), viewport()->width() + verticalHeader()->width(), rowHeight(0));
    }
    
    void SearchTableView::updateSectionWidth(int logicalIndex, int /* *oldSize*/, int newSize) {
        searchBox->setColumnWidth(logicalIndex, newSize);
    }

    void SearchTableView::updateSectionHeight(int logicalIndex, int /**oldSize*/, int newSize) {
        if (logicalIndex == 0) {
            searchBox->setRowHeight(logicalIndex, newSize);
            updateSearchBoxGeometry();
        }
    }
}