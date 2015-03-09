#include <QHeaderView>
#include <QScrollBar>
#include "LeftProxyModel.h"
#include "SearchTableView.h"

namespace Commissionator {
    SearchTableView::SearchTableView(QAbstractItemModel *model) {
        setModel(model);
        searchBox = new QTableView(this);

        init();
        connect(horizontalHeader(), &QHeaderView::sectionResized, this, &SearchTableView::updateSectionWidth);
        connect(verticalHeader(), &QHeaderView::sectionResized, this, &SearchTableView::updateSectionHeight);
        connect(searchBox->horizontalScrollBar(), &QScrollBar::valueChanged, horizontalScrollBar(), &QScrollBar::setValue);
        connect(horizontalScrollBar(), &QScrollBar::valueChanged, searchBox->horizontalScrollBar(), &QScrollBar::setValue);
    }

    SearchTableView::~SearchTableView() {
        delete searchBox;
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
        
        if (cursorAction == MoveLeft && current.column() > 0
            && visualRect(current).topLeft().x() < searchBox->columnWidth(0)) {
            const int newValue = horizontalScrollBar()->value() + visualRect(current).topLeft().x()
                - searchBox->columnWidth(0);
            horizontalScrollBar()->setValue(newValue);
        }
        
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
        searchBox->setModel(model());
        searchBox->setFocusPolicy(Qt::NoFocus);
        searchBox->horizontalHeader()->hide();
        searchBox->verticalHeader()->hide();
        searchBox->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
        viewport()->stackUnder(searchBox);
        searchBox->setSelectionModel(selectionModel());
        searchBox->setRowHeight(0, rowHeight(0));
        searchBox->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        searchBox->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        for (int row = 1; row < model()->rowCount(); row++)
            searchBox->setRowHidden(row, true);
        searchBox->show();
        updateSearchBoxGeometry();

        setHorizontalScrollMode(ScrollPerPixel);
        setVerticalScrollMode(ScrollPerPixel);
        searchBox->setHorizontalScrollMode(ScrollPerPixel);
    }

    void SearchTableView::updateSearchBoxGeometry() {
        searchBox->setGeometry(verticalHeader()->width() + frameWidth(),
            horizontalHeader()->height() + frameWidth(), viewport()->width() + verticalHeader()->width(), rowHeight(0));
    }

    QModelIndex SearchTableView::firstIndex() {

    }
    QModelIndex SearchTableView::previousIndex(QModelIndex oldIndex) {

    }
    QModelIndex SearchTableView::nextIndex(QModelIndex oldIndex) {

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

    void SearchTableView::closeEditor(QWidget * editor, QAbstractItemDelegate::EndEditHint hint) {
        if (hint == QAbstractItemDelegate::NoHint)
            QTableView::closeEditor(editor, QAbstractItemDelegate::SubmitModelCache);
        else if (hint == QAbstractItemDelegate::EditNextItem || hint == QAbstractItemDelegate::EditPreviousItem) {
            QModelIndex index;
            if (hint == QAbstractItemDelegate::EditNextItem)
                index = nextIndex(currentIndex());
            else
                index = previousIndex(currentIndex());
            if (!index.isValid())
                QTableView::closeEditor(editor, QAbstractItemDelegate::SubmitModelCache);
            else {
                QTableView::closeEditor(editor, QAbstractItemDelegate::NoHint);
                setCurrentIndex(index);
                edit(index);
            }
        } else
            QTableView::closeEditor(editor, hint);
    }
}