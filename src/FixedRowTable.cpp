#include <QHeaderView>
#include <QScrollBar>
#include <QKeyEvent>
#include <QPushButton>
#include <QStyledItemDelegate>
#include "FixedRowTable.h"

namespace Commissionator {
    FixedRowTable::FixedRowTable(QAbstractItemModel *model, QWidget *parent) :
    QTableView(parent) {
        init(model);
    }

    void FixedRowTable::closeBoxPersistentEditor(const int column) {
        persistentEditors.removeAll(column);
        box->closePersistentEditor(box->model()->index(0, column));
    }

    void FixedRowTable::openBoxPersistentEditor(const int column) {
        persistentEditors.append(column);
        box->openPersistentEditor(box->model()->index(0, column));
    }

    void FixedRowTable::setBoxBottom(const bool newOnBottom) {
        boxOnBottom = newOnBottom;
        updateBoxGeometry();
    }

    void FixedRowTable::setBoxButtonActivated(const bool isEnabled) {
        boxButtonOn = isEnabled;
    }

    void FixedRowTable::setBoxButtonIcon(QString newIcon) {
        boxButton->setIcon(QIcon(newIcon));
    }

    void FixedRowTable::setBoxButtonText(QString newText) {
        boxButton->setText(newText);
    }

    void FixedRowTable::setBoxButtonWidth(double widthFactor) {
        boxButtonWidth = widthFactor;
    }

    void FixedRowTable::setBoxDelegate(QAbstractItemDelegate *newDelegate) {
        QAbstractItemDelegate *temp = box->itemDelegate();
        box->setItemDelegate(newDelegate);
        delete temp;
    }

    void FixedRowTable::setBoxText(QString newText) {
        proxy->setText(newText);
    }

    void FixedRowTable::boxQuerySlot(const QList<QVariant> query) {
        emit boxQuery(query);
        foreach(int i, persistentEditors) {
            box->openPersistentEditor(box->indexAt(QPoint(i, 0)));
        }
    }

    void FixedRowTable::tableButtonSlot(const QModelIndex &index) {
        emit tableButtonClicked(index);
        foreach(int i, persistentEditors) {
            box->openPersistentEditor(box->indexAt(QPoint(i, 0)));
        }
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

    void FixedRowTable::setColumnCount(const int count) {
        proxy->setColumnCount(count);
    }

    void FixedRowTable::setColumnHidden(int column, bool hide) {
        QTableView::setColumnHidden(column, hide);
        box->setColumnHidden(column, hide);
    }

    void FixedRowTable::setDeleteMessage(QString deleteMessage) {
        tableDelegate->setDeleteMessage(deleteMessage);
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
        connect(proxy, &FixedRowProxyModel::querySignal, this, &FixedRowTable::boxQuerySlot);
        connect(tableDelegate, &FixedRowTableDelegate::buttonClicked, this, &FixedRowTable::tableButtonSlot);
        connect(box, &FixedRowBox::boxQuery, proxy, &FixedRowProxyModel::query);
        connect(boxButton, &QPushButton::clicked, proxy, &FixedRowProxyModel::query);
    }

    void FixedRowTable::createDelegates() {
        tableDelegate = new FixedRowTableDelegate(this);
        setItemDelegate(tableDelegate);
        setTableButtonActivated(false);
        setBoxButtonActivated(false);
    }

    void FixedRowTable::createProxy(QAbstractItemModel *model) {
        proxy = new FixedRowProxyModel(this);
        proxy->setSourceModel(model);
    }

    void FixedRowTable::createBox() {
        box = new FixedRowBox(this);
        boxButton = new QPushButton(this);
        box->setModel(proxy);
        viewport()->stackUnder(box);
        box->setSelectionModel(selectionModel());
        box->setColumnWidth(0, columnWidth(0));
        updateBoxGeometry();
        boxOnBottom = false;
        boxButtonOn = false;
        boxButtonWidth = 0;
    }
    
    void FixedRowTable::createTable() {
        setModel(proxy);
        setFocusPolicy(Qt::StrongFocus);
        setHorizontalScrollMode(ScrollPerPixel);
        setVerticalScrollMode(ScrollPerPixel);
        verticalHeader()->hide();
    }

    void FixedRowTable::init(QAbstractItemModel *model) {
        createProxy(model);
        createTable();
        createBox();
        createDelegates();
        createConnections();
    }

    void FixedRowTable::updateBoxGeometry() {
        if (boxOnBottom) {
            setViewportMargins(contentsRect().left(),
                contentsRect().top() + horizontalHeader()->height(),
                0, box->rowHeight(0));
            setRowHidden(0, true);  //hides the search row from the top
            if (boxButtonOn) {
                if (boxButtonWidth == 0) {
                    if (horizontalScrollBar()->isVisible()) {
                        box->setGeometry(verticalHeader()->width() + frameWidth(),
                            contentsRect().bottom() - box->rowHeight(0) - horizontalScrollBar()->height(),
                            viewport()->width() + verticalHeader()->width() - columnWidth(columnAt(
                            viewport()->width() + verticalHeader()->width() - 1)),
                            box->rowHeight(0));
                        boxButton->setGeometry(
                            viewport()->width() + verticalHeader()->width() - columnWidth(columnAt(
                            viewport()->width() + verticalHeader()->width() - 1)),
                            contentsRect().bottom() - box->rowHeight(0) - 1 - horizontalScrollBar()->height(),
                            columnWidth(columnAt(viewport()->width() + verticalHeader()->width() - 1)) + 2,
                            box->rowHeight(0) + 2);
                    } else {
                        box->setGeometry(verticalHeader()->width() + frameWidth(),
                            contentsRect().bottom() - box->rowHeight(0),
                            viewport()->width() + verticalHeader()->width() - columnWidth(columnAt(
                            viewport()->width() + verticalHeader()->width() - 1)),
                            box->rowHeight(0));
                        boxButton->setGeometry(
                            viewport()->width() + verticalHeader()->width() - columnWidth(columnAt(
                            viewport()->width() + verticalHeader()->width() - 1)),
                            contentsRect().bottom() - box->rowHeight(0) - 1,
                            columnWidth(columnAt(viewport()->width() + verticalHeader()->width() - 1)) + 2,
                            box->rowHeight(0) + 2);
                    }
                } else {
                    if (horizontalScrollBar()->isVisible()) {
                        box->setGeometry(verticalHeader()->width() + frameWidth(),
                            contentsRect().bottom() - box->rowHeight(0) - horizontalScrollBar()->height(),
                            viewport()->width() + verticalHeader()->width()
                            - box->rowHeight(0)*boxButtonWidth,
                            box->rowHeight(0));
                        boxButton->setGeometry(
                            viewport()->width() + verticalHeader()->width()
                            - box->rowHeight(0)*boxButtonWidth,
                            contentsRect().bottom() - box->rowHeight(0) - 1 - horizontalScrollBar()->height(),
                            box->rowHeight(0)*boxButtonWidth + 2,
                            box->rowHeight(0) + 2);
                    } else {
                        box->setGeometry(verticalHeader()->width() + frameWidth(),
                            contentsRect().bottom() - box->rowHeight(0),
                            viewport()->width() + verticalHeader()->width()
                            - box->rowHeight(0)*boxButtonWidth,
                            box->rowHeight(0));
                        boxButton->setGeometry(
                            viewport()->width() + verticalHeader()->width()
                            - box->rowHeight(0)*boxButtonWidth,
                            contentsRect().bottom() - box->rowHeight(0) - 1,
                            box->rowHeight(0)*boxButtonWidth + 2,
                            box->rowHeight(0) + 2);
                    }
                }
                boxButton->show();
            } else {
                box->setGeometry(verticalHeader()->width() + frameWidth(),
                    contentsRect().bottom() - box->rowHeight(0),
                    viewport()->width() + verticalHeader()->width(),
                    box->rowHeight(0));
                boxButton->hide();
            }
        } else {
            setViewportMargins(contentsRect().left(),
                contentsRect().top() + horizontalHeader()->height(),
                0, 0);
            setRowHidden(0, false);
            if (boxButtonOn) {
                if (boxButtonWidth == 0) {
                    box->setGeometry(verticalHeader()->width() + frameWidth(),
                        contentsRect().top() + horizontalHeader()->height(),
                        viewport()->width() + verticalHeader()->width() - columnWidth(columnAt(
                        viewport()->width() + verticalHeader()->width() - 1)),
                        box->rowHeight(0));
                    boxButton->setGeometry(
                        viewport()->width() + verticalHeader()->width() - columnWidth(columnAt(
                        viewport()->width() + verticalHeader()->width() - 1)),
                        contentsRect().top() + horizontalHeader()->height() - 1,
                        columnWidth(columnAt(viewport()->width() + verticalHeader()->width() - 1)) + 2,
                        box->rowHeight(0) + 2);
                } else {
                    box->setGeometry(verticalHeader()->width() + frameWidth(),
                        contentsRect().top() + horizontalHeader()->height(),
                        viewport()->width() + verticalHeader()->width()
                        - box->rowHeight(0)*boxButtonWidth,
                        box->rowHeight(0));
                    boxButton->setGeometry(
                        viewport()->width() + verticalHeader()->width()
                        - box->rowHeight(0)*boxButtonWidth,
                        contentsRect().top() + horizontalHeader()->height() - 1,
                        box->rowHeight(0)*boxButtonWidth + 2,
                        box->rowHeight(0) + 2);
                }
                boxButton->show();
            } else {
                box->setGeometry(verticalHeader()->width() + frameWidth(),
                    horizontalHeader()->height() + frameWidth(),
                    viewport()->width() + verticalHeader()->width(), rowHeight(0));
                boxButton->hide();
                
            }
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