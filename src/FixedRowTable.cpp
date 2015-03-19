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
        delete delegate;
    }

    void FixedRowTable::setBoxBottom(const bool isOnBottom) {
        proxy->setBottom(isOnBottom);
        updateBoxGeometry();
    }

    void FixedRowTable::setBoxText(QString newText) {
        proxy->setText(newText);
    }

    void FixedRowTable::setButtonIcon(QString newIcon) {
        delegate->setIcon(newIcon);
    }

    void FixedRowTable::setButtonActivated(const bool isEnabled) {
        if (isEnabled && itemDelegate() != delegate) {
            QAbstractItemDelegate *temp = itemDelegate();
            setItemDelegate(delegate);
            delete temp;
        }
        else if (!isEnabled && itemDelegate() == delegate)
            setItemDelegate(new QStyledItemDelegate()); //the old delegate is not deleted because we don't want to lose the user's settings in case they re-enable the button
    }

    void FixedRowTable::setButtonSize(int size) {
        delegate->setIconSize(size);
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
        connect(delegate, &FixedRowTableDelegate::buttonClicked, this, &FixedRowTable::buttonClicked);
        connect(box, &FixedRowBox::boxQuery, proxy, &FixedRowProxyModel::query);
    }

    void FixedRowTable::createDelegate() {
        delegate = new FixedRowTableDelegate();
        setItemDelegate(delegate);
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
        //setSortingEnabled(true);  doesn't work because the way the proxy model works

        for (int col = 0; col < horizontalHeader()->count(); col++)
            horizontalHeader()->setSectionResizeMode(col, QHeaderView::Stretch);
    }

    void FixedRowTable::init() {
        createTable();
        createBox();
        createDelegate();
        createConnections();
    }

    void FixedRowTable::updateBoxGeometry() {
        if (proxy->isOnBottom()) {
            setViewportMargins(contentsRect().left(),
                contentsRect().top() + horizontalHeader()->height(),
                0, rowHeight(0));
            box->setGeometry(verticalHeader()->width() + frameWidth(),
                contentsRect().bottom() - rowHeight(0), 
                viewport()->width() + verticalHeader()->width(), rowHeight(0));

            //if (model() == proxy)
                //setRowHidden(0, true);
                //setModel(proxy->sourceModel());
        } else {
            box->setGeometry(verticalHeader()->width() + frameWidth(),
                horizontalHeader()->height() + frameWidth(), viewport()->width() + verticalHeader()->width(), rowHeight(0));
            //if (model() != proxy)
            //    setModel(proxy);
        } 
    }
    
    void FixedRowTable::updateSectionWidth(int logicalIndex, int /* *oldSize*/, int newSize) {
        box->setColumnWidth(logicalIndex, newSize);
    }

    void FixedRowTable::updateSectionHeight(int logicalIndex, int /**oldSize*/, int newSize) {
        if (logicalIndex == 0) {
            box->setRowHeight(logicalIndex, newSize);
            updateBoxGeometry();
        }
    }
}