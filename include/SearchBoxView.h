#ifndef SEARCHBOXVIEW_H
#define SEARCHBOXVIEW_H

#include "FixedRowProxyModel.h"
#include <QTableView>

namespace Commissionator {
    class SearchBoxView : public QTableView {

        Q_OBJECT
         
    public:
        /**
         *  Default constructor
         *
         *  @param parent - pointer to parent widget
         */
        SearchBoxView(QWidget *parent = nullptr);

        /**
         *  New setModel function works for SearchProxyModel specifically.
         *  Initializes the SearchBoxView so that it works correctly with
         *  SearchTableView and calls QTableView::setModel();
         *
         *  @param model - model display in the view
         */
        void setModel(FixedRowProxyModel *model);

    protected:
        /**
         *  Overrides the default mousePressEvent function to allow the user to
         *  edit the SearchBoxView fields with only a single click
         *
         *  @param event - pointer to the mouse event
         */
        void mousePressEvent(QMouseEvent *event);

        /**
         *  Overrides the default scrollTo function and does nothing.
         *  Exists so that any call to scrollTo will fail to move the searchbox
         *  away from the correct row. Is mainly needed for when records are
         *  added or deleted to the underlying model.
         *
         *  @param index - pointer to the index, is used only for telling which
         *      column to use
         *  @param hint - the hint to use to know in which manner the scroll
         *      should occur
         */
        void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) Q_DECL_OVERRIDE;

        /**
         *  Overrides the default wheelEvent function and does nothing.
         *  Exists so the user can't scroll the SearchBoxView, as the row
         *  should be fixed, and the SearchBox should be pinned to the top of
         *  the SearchTableView
         *
         *  @param event - pointer to the QWheel event that is to be ignored
         */
        void wheelEvent(QWheelEvent *event);

    protected slots:
        /**
         *  Overrides the default closeEditor function to allow enter to be
         *  used as a submission key for the search function.
         *
         *  @param editor - pointer to the editor that is being closed
         *  @param hint - the EndEditHint that desribes how this edit is to be
         *      closed
         */
        void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);

    signals:
        /**
         *  Signal thrown when the search box is submitted.
         */
        void searchSignal();
    };
}

#endif