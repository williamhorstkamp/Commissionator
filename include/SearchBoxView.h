#ifndef SEARCHBOXVIEW_H
#define SEARCHBOXVIEW_H

#include "SearchProxyModel.h"
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
         */
        void setModel(SearchProxyModel *model);

    protected:
        /**
         *  Overrides the default keyPressEvent function to allow enter to
         *  run the SearchProxyModel->search() function.
         *
         *  @param event - pointer to keyboard event
         */
        void keyPressEvent(QKeyEvent *event);

        /**
         *  Overrides the default mousePressEvent function to allow the user to
         *  edit the SearchBoxView fields with only a single click
         */
        void mousePressEvent(QMouseEvent *event);
    };
}

#endif