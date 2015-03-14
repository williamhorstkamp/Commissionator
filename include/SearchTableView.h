#ifndef SEARCHTABLEVIEW_H
#define SEARCHTABLEVIEW_H

#include <QTableView>
#include "SearchBoxView.h"

namespace Commissionator {

    /**
     *  Class creates a customized QTableView with a fixed search bar and a few
     *  minor useability tweaks.
     */
    class SearchTableView : public QTableView {

        Q_OBJECT

    public:
        /**
         *  Constructor accepts a model to build a Search Table for.
         *
         *  @param model - Pointer to QAbstractItemModel based model on use
         *      for the proxy model and views.
         */
        SearchTableView(QAbstractItemModel *model);

        /**
         *  Destructor cleans up internal objects.
         */
        ~SearchTableView();
        

    protected:
        /**
         *  Overrides the default resizeEvent function so that in addition to
         *  its normal use, it also calls updateSearchBoxGeometry()
         * 
         *  @param event - Pointer to QResizeEvent that describes the resize.
         */
        void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

        /**
        *  Overrides the default scrollTo function to prevent the user from
        *  scrolling to the hidden row.
        */
        void scrollTo(const QModelIndex & index, ScrollHint hint = EnsureVisible) Q_DECL_OVERRIDE;

    private:
        //Proxy model that creates the search column and manages it
        SearchProxyModel *proxy;
        //Search box inherits from QTableView and provides additional functionality
        SearchBoxView *searchBox;

        /**
         *  Initializes the object and all its sub objects.
         */
        void init();
        
        /**
         *  Updates the size of the search box based on the dimensions of the
         *  search table.
         */
        void updateSearchBoxGeometry();

    private slots:
        /**
         *  Updates the width of the a column in the search box whenever one is
         *  changed in the search table
         *
         *  @param logicalIndex - the logical index of the column that has been
         *      changed
         *  @param oldSize - int containing the old size in number of pixels
         *  @param newSize - int containing the new size in number of pixels
         */
        void updateSectionWidth(int logicalIndex, int oldSize, int newSize);

        /**
        *  Updates the height of the row the search box is in whenever the
        *  matching one is changed in the search table
        *
        *  @param logicalIndex - the logical index of the row that has been
        *      changed
        *  @param oldSize - int containing the old size in number of pixels
        *  @param newSize - int containing the new size in number of pixels
        */
        void updateSectionHeight(int logicalIndex, int oldSize, int newSize);
    };
}
#endif