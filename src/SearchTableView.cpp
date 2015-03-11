#include <QHeaderView>
#include <QScrollBar>
#include <QKeyEvent>
#include "SearchTableView.h"

namespace Commissionator {
    SearchTableView::SearchTableView(QAbstractItemModel *model) {
        proxy = new SearchProxyModel(this); 
        proxy->setSourceModel(model);
        //searchBox = new SearchBoxView(this);
        setModel(proxy);
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

    void SearchTableView::resizeEvent(QResizeEvent * event)
    {
        QTableView::resizeEvent(event);
        updateSearchBoxGeometry();
    }

    QModelIndex SearchTableView::moveCursor(CursorAction cursorAction,
        Qt::KeyboardModifiers modifiers)
    {
        QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);
        if (cursorAction == MoveUp && current.row() > 0
            && visualRect(current).topLeft().y() < searchBox->rowHeight(0)) {
            const int newValue = verticalScrollBar()->value() + visualRect(current).topLeft().y()
                - searchBox->rowHeight(0);
            verticalScrollBar()->setValue(newValue);
        }
        return current;
    }

    void SearchTableView::scrollTo(const QModelIndex &index, ScrollHint hint) {
        if (index.row() > 0)
            QTableView::scrollTo(index, hint);
    }

    void SearchTableView::init() {
        searchBox = new SearchBoxView(this);
        searchBox->setModel(proxy);
        
        setFocusPolicy(Qt::StrongFocus);
        /**searchBox->setFocusPolicy(Qt::NoFocus);
        searchBox->horizontalHeader()->hide();
        searchBox->verticalHeader()->hide();
        searchBox->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        */
        viewport()->stackUnder(searchBox);
        /*
        searchBox->setSelectionModel(selectionModel());
        searchBox->setRowHeight(0, rowHeight(0));
        searchBox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        searchBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        for (int row = 1; row < model()->rowCount(); row++)
            searchBox->setRowHidden(row, true);
        searchBox->show();
        */
        updateSearchBoxGeometry();

        setHorizontalScrollMode(ScrollPerPixel);
        setVerticalScrollMode(ScrollPerPixel);
        //searchBox->setHorizontalScrollMode(ScrollPerPixel);

        setSelectionBehavior(QAbstractItemView::SelectRows);
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