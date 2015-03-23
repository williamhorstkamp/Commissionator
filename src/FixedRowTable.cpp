#include <QHeaderView>
#include <QScrollBar>
#include <QKeyEvent>
#include <QStyledItemDelegate>
#include "FixedRowTable.h"

namespace Commissionator {
    FixedRowTable::FixedRowTable(QAbstractItemModel *model) {
        createProxy();
        proxy->setSourceModel(model);

        init();
    }

    FixedRowTable::~FixedRowTable() {
        delete box;
        delete proxy;
        //delete tableDelegate;
        delete boxDelegate;
    }

    void FixedRowTable::setBoxBottom(const bool newOnBottom) {
        boxOnBottom = newOnBottom;
        updateBoxGeometry();
    }

    void FixedRowTable::setBoxButtonActivated(const bool isEnabled) {
        if (isEnabled && box->itemDelegate() != boxDelegate) {
            QAbstractItemDelegate *temp = box->itemDelegate();
            box->setItemDelegate(boxDelegate);
            delete temp;
        } else if (!isEnabled && box->itemDelegate() == boxDelegate)
            box->setItemDelegate(new QStyledItemDelegate()); //the old delegate is not deleted because we don't want to lose the user's settings in case they re-enable the button
    }

    void FixedRowTable::setBoxButtonIcon(QString newIcon) {
        boxDelegate->setIcon(newIcon);
    }

    void FixedRowTable::setBoxButtonSize(int size) {
        boxDelegate->setIconSize(size);
    }

    void FixedRowTable::setBoxDelegate(FixedRowTableDelegate *newDelegate) {
        FixedRowTableDelegate *temp = boxDelegate;
        boxDelegate = newDelegate;
        delete temp;
    }

    void FixedRowTable::setBoxText(QString newText) {
        proxy->setText(newText);
    }

    void FixedRowTable::setTableButtonActivated(const bool isEnabled) {
        if (isEnabled && itemDelegate() != tableDelegate) {
            QAbstractItemDelegate *temp = itemDelegate();
            setItemDelegate(tableDelegate);
            delete temp;
        }
        else if (!isEnabled && itemDelegate() == tableDelegate)
            setItemDelegate(new QStyledItemDelegate()); //the old delegate is not deleted because we don't want to lose the user's settings in case they re-enable the button
    }

    void FixedRowTable::setTableButtonIcon(QString newIcon) {
        tableDelegate->setIcon(newIcon);
    }

    void FixedRowTable::setTableButtonSize(int size) {
        tableDelegate->setIconSize(size);
    }

    void FixedRowTable::setTableDelegate(FixedRowTableDelegate *newDelegate) {
        FixedRowTableDelegate *temp = tableDelegate;
        tableDelegate = newDelegate;
        delete temp;
    }

    void FixedRowTable::setColumnHidden(int column, bool hide) {
        QTableView::setColumnHidden(column, hide);
        box->setColumnHidden(column, hide);
    }

    QModelIndex FixedRowTable::moveCursor(CursorAction cursorAction,
        Qt::KeyboardModifiers modifiers) {
        QModelIndex current = QTableView::moveCursor(cursorAction, modifiers);
        if (current.row() == 0)
            return QModelIndex();
        return current;
    }

    void FixedRowTable::resizeEvent(QResizeEvent *event) {
        QTableView::resizeEvent(event);
        updateBoxGeometry();
    }

    void FixedRowTable::scrollTo(const QModelIndex &index, ScrollHint hint) {
        if (index.row() > 0)
            QTableView::scrollTo(index, hint);
    }

    void FixedRowTable::createConnections() {
        connect(horizontalHeader(), &QHeaderView::sectionResized, this, &FixedRowTable::updateSectionWidth);
        connect(verticalHeader(), &QHeaderView::sectionResized, this, &FixedRowTable::updateSectionHeight);
        connect(box->horizontalScrollBar(), &QScrollBar::valueChanged, horizontalScrollBar(), &QScrollBar::setValue);
        connect(horizontalScrollBar(), &QScrollBar::valueChanged, box->horizontalScrollBar(), &QScrollBar::setValue);
        connect(proxy, &FixedRowProxyModel::querySignal, this, &FixedRowTable::boxQuery);
        connect(tableDelegate, &FixedRowTableDelegate::buttonClicked, this, &FixedRowTable::tableButtonClicked);
        connect(boxDelegate, &FixedRowTableDelegate::buttonClicked, this, &FixedRowTable::boxButtonClicked);
        connect(box, &FixedRowBox::boxQuery, proxy, &FixedRowProxyModel::query);
    }

    void FixedRowTable::createDelegates() {
        tableDelegate = new FixedRowTableDelegate();
        setItemDelegate(tableDelegate);
        setTableButtonActivated(false);
        boxDelegate = new FixedRowTableDelegate();
        box->setItemDelegate(boxDelegate);
        setBoxButtonActivated(false);
    }

    void FixedRowTable::createProxy() {
        proxy = new FixedRowProxyModel(this);
    }

    void FixedRowTable::createBox() {
        box = new FixedRowBox(this);
        box->setModel(proxy);
        viewport()->stackUnder(box);
        box->setSelectionModel(selectionModel());
        box->setColumnWidth(0, columnWidth(0));
        updateBoxGeometry();
        boxOnBottom = false;
    }
    
    void FixedRowTable::createTable() {
        
        setModel(proxy);
        setFocusPolicy(Qt::StrongFocus);
        setHorizontalScrollMode(ScrollPerPixel);
        setVerticalScrollMode(ScrollPerPixel);
        setSelectionMode(QAbstractItemView::NoSelection);
        setSelectionBehavior(QAbstractItemView::SelectRows);
        setEditTriggers(QAbstractItemView::NoEditTriggers);
        verticalHeader()->hide();

        for (int col = 0; col < horizontalHeader()->count(); col++)
            horizontalHeader()->setSectionResizeMode(col, QHeaderView::Stretch);
    }

    void FixedRowTable::init() {
        createTable();
        createBox();
        createDelegates();
        createConnections();
    }

    void FixedRowTable::updateBoxGeometry() {
        if (boxOnBottom) {
            setViewportMargins(contentsRect().left(),
                contentsRect().top() + horizontalHeader()->height(),
                0, rowHeight(0));
            box->setGeometry(verticalHeader()->width() + frameWidth(),
                contentsRect().bottom() - box->rowHeight(0), 
                viewport()->width() + verticalHeader()->width(), box->rowHeight(0));
            setRowHidden(0, true);  //hides the search row from the top
        } else {
            box->setGeometry(verticalHeader()->width() + frameWidth(),
                horizontalHeader()->height() + frameWidth(), viewport()->width() + verticalHeader()->width(), rowHeight(0));
            setRowHidden(0, false); //unhides the search row from the top to provide the space for the fixed row
        } 
    }
    
    void FixedRowTable::updateSectionWidth(int logicalIndex, int /*oldSize*/, int newSize) {
        box->setColumnWidth(logicalIndex, newSize);
    }

    void FixedRowTable::updateSectionHeight(int logicalIndex, int /*oldSize*/, int newSize) {
        if (logicalIndex == 0) {
            box->setRowHeight(logicalIndex, newSize);
            updateBoxGeometry();
        }
    }
}