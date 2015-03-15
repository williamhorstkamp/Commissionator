#ifndef LEFTPANEL_H
#define LEFTPANEL_H

#include <QVBoxLayout>
#include <QSqlRelationalTableModel>
#include <QList>
#include <QLabel>
#include "SearchTableView.h"

namespace Commissionator {
    class LeftPanel :public QWidget {
        Q_OBJECT

    private:
        QVBoxLayout *layout;
        SearchTableView *view;
        QLabel *titleLabel;
        
        /**
         *  Initializes the panels title label based on QString input
         *
         *  @param title - QString containing text to set the panel label to
         */
        void createTitle(QString title);

        /**
         *  Initializes the panels title based on the given model.
         *
         *  @param model - pointer to the model to set the table view to
         *
         *  @param hiddenColumns - QList containing column ids to hide from the
         *      view. Not Implemented during testing, but functionality is 
         *      written and tested.
         */
        void createTable(QSqlQueryModel *model, QList<int> hiddenColumns);

    public:
        /**
         *  Constructor takes panel title and model data and initializes 
         *  itself.
         *
         *  @param title - QString containing the title of the data the panel
         *      is displaying
         *  @param model - pointer to the model to set the table view to
         *  @param hiddenColumns - QList containing column ids to hide from the
         *      view. Not Implemented during testing, but functionality is
         *      written and tested.
         */
        LeftPanel(QString title, QSqlQueryModel *model, QList<int> hiddenColumns);
    signals:
        /**
         *  Signal that is sent whenever the table has been clicked on.
         *  Used to updated the various right panels based on the user's input
         *  to the left panel.
         *
         *  @param index - reference to the index that was clicked by the user
         */
        void tableClicked(const QModelIndex &index);

        /**
         *  Signal that contains the search query.
         *  Is a forwarded version of SearchProxyModel::searchSignal
         */
        void search(const QList<QVariant> searchQuery);

        /**
        *  Signal that is thrown when when one of the SearchTableDelegate
        *  icons was clicked.
        *  Is a forwarded version of SearchTableDelegate::iconClicked
        */
        void iconClicked(const QModelIndex &index);
    };
}
#endif