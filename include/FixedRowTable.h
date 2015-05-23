#ifndef FIXEDROWTABLE_H
#define FIXEDROWTABLE_H

#include <QTableView>
#include <QPushButton>
#include "FixedRowTableDelegate.h"
#include "FixedRowBox.h"

namespace Commissionator {

    /**
     *  Class creates a customized QTableView with a fixed search bar, 
     *  buttons on each row, and a few minor useability tweaks.
     */
    class FixedRowTable : public QTableView {

        Q_OBJECT

    public:
        /**
         *  Constructor accepts a model that a table is built for.
         *
         *  @param model - Pointer to QAbstractItemModel based model on use
         *      for the proxy model and views.
         */
        FixedRowTable(QAbstractItemModel *model, QWidget *parent = nullptr);

        /**
         *  Opens a persistent editor in the ItemView at the given column.
         *
         *  @param column - column to open the editor in
         */
        void openBoxPersistentEditor(const int column);

        /**
         *  Closes a persistent editor in the ItemView at the given column.
         *
         *  @param column - column to close the editor in
         */
        void closeBoxPersistentEditor(const int column);

        /**
         *  Sets the bottom box to the bottom of the window if set to true
         *
         *  @param newOnBottom - bool containing whether the box should be on bottom
         */
        void setBoxBottom(const bool newOnBottom);

        /**
         *  Activates or deactives the box button.
         *
         *  @param isEnabled - boolean referencing whether to activate the button
         */
        void setBoxButtonActivated(const bool isEnabled);

        /**
         *  Sets the button's icon to the file found at the location referenced
         *  in the QString. Does not display without also setting button size.
         *
         *  @param newIcon - location on disk of the file to be used as the icon
         */
        void setBoxButtonIcon(QString newIcon);

        /**
         *  Sets the button's icon to the text given.
         *
         *  @param newText - QString to set the button's text to
         */
        void setBoxButtonText(QString newText);

        /**
         *  Sets the box button's width based on the width factor given.
         *  The factor is a multiple of the button's height that the width
         *  should be.
         *  0 will make the button take up the width of the last column.
         *
         *  @param widthFactor - the width factor as a double
         */
        void setBoxButtonWidth(double widthFactor);

        /**
         *  Sets the box's delegate to allow you to display custom forms
         *  in the box
         *
         *  @param newDelegate - pointer to the delegate which manages the
         *      box
         */
        void setBoxDelegate(QAbstractItemDelegate *newDelegate);

        /**
         *  Sets the default text in the box to the text in newText.
         *  Will clear the box of any entries when this is ran.
         *
         *  @param newText - new default text to set the box to
         */
        void setBoxText(QString newText);

        /**
         *  Function sets the number of expectant columns. This is used to
         *  guarentee the correct number of strings exist before a model is
         *  initialized in cases where the source model may be linked to
         *  FixedRowTable before the model is initialized.
         *
         *  @param count - number of columns
         */
        void setColumnCount(const int count);

        /**
         *  Overrides default setColumnHidden function to call the same
         *  function with the same parameters on box as well.
         */
        void setColumnHidden(int column, bool hide);

        /**
         *  Activates or deactives the table buttons.
         *
         *  @param isEnabled - boolean referencing whether to activate the button
         */
        void setTableButtonActivated(const bool isEnabled);

        /**
         *  Sets the table button's icon to the file found at the location 
         *  referenced in the QString. Does not display without also setting 
         *  button size.
         *
         *  @param newIcon - location on disk of the file to be used as the icon
         */
        void setTableButtonIcon(QString newIcon);

        /**
         *  Sets the table button's size to the integer given
         *
         *  @param size - size in pixels of the button to be displayed
         */
        void setTableButtonSize(int size);

        /**
         *  Sets the table's delegate to a FixedRowTableDelegate based delegate
         *      to allow you to display custom forms in the box
         *
         *  @param newDelegate - pointer to the delegate which manages the
         *      box
         */
        void setTableDelegate(FixedRowTableDelegate *newDelegate);

    protected:
        /**
         *  Initializes connections.
         *  Exists to allow for easier use of derived classes.
         */
        void createConnections();

        /**
         *  Initializes delegate.
         *  Exists to allow for easier use of derived classes.
         */
        void createDelegates();

        /**
         *  Initializes proxy.
         *  Exists to allow for easier use of derived classes.
         *
         *  @param model - pointer to model to proxy
         */
        void createProxy(QAbstractItemModel *model);

        /**
         *  Initializes search box.
         *  Exists to allow for easier use of derived classes.
         */
        void createBox();

        /**
         *  Initializes table.
         *  Exists to allow for easier use of derived classes.
         */
        void createTable();

        /**
         *  Initializes the object and all its sub objects.
         *
         *  @param model - pointer to model to proxy
         */
        void init(QAbstractItemModel *model);

        /**
         *  Overrides the default moveCursor function so that the user can not
         *  use keyboard controls to navigate to the hidden top row.
         *
         *  @param cursorAction - the action that the function is analyzing
         *  @param modifiers - a list of keyboard modifiers that may be pressed
         *      (shift, ctrl, etc)
         *
         *  @return - the new QModelIndex generated by the function based on
         *      the current index and cursorAction
         */
        QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) Q_DECL_OVERRIDE;

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
         *
         *  @param index - index that the table is scrolling to
         *  @param hint - hint as to how the scroll should occur
         */
        void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) Q_DECL_OVERRIDE;

    private:

        /**
        *  Updates the size of the search box based on the dimensions of the
        *  search table.
        */
        void updateBoxGeometry();

        //Proxy model that creates the search column and manages it
        FixedRowProxyModel *proxy;
        //Search box inherits from QTableView and provides additional functionality
        FixedRowBox *box;
        QPushButton *boxButton;
        double boxButtonWidth;
        //delegate that handles the icons displayed on the table
        FixedRowTableDelegate *tableDelegate;
        bool boxButtonOn;
        bool boxOnBottom;
        QList<int> persistentEditors;

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

    signals:
        /**
         *  Signal that contains a query.
         *  Use it by connecting it to your data model's signal of choice
         *  Emitted when the box button is clicked or enter is struck while
         *  editting one of the box's columns
         *
         *  @param searchQuery - QList of QVariants that each represent a field
         *      in the query
         */
        void boxQuery(const QList<QVariant> query);

        /**
         *  Signal that is thrown when when one of the SearchTableDelegate
         *  icons was clicked.
         *  Use it by connecting it to your data model's function of choice
         *
         *   @param index - index whose button was clicked
         */
        void tableButtonClicked(const QModelIndex &index);

    private slots:
        /**
         *  Slot accepts FixedRowBox::boxQuery and emits FixedRowTable::boxQuery.
         *  Also enforces open persistent editor functionality
         */
        void boxQuerySlot(const QList<QVariant> query);

        /**
         *  Slot accepts FixedRowTableDelegate::buttonClicked and emits 
         *  FixedRowTable::tableButtonClicked.
         *  Also enforces open persistent editor functionality
         */
        void tableButtonSlot(const QModelIndex &index);
    };
}
#endif