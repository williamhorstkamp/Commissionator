#ifndef COMBOTEDITORDELEGATE_H
#define COMBOTEDITORDELEGATE_H

#include <QStyledItemDelegate>

namespace Commissionator {

    class ComboEditorDelegate : public QStyledItemDelegate {
        
        Q_OBJECT

    public:

        /**
         *  Default constructor initializes editorColumn to 0
         */
        ComboEditorDelegate(QObject *parent = nullptr);

        /**
         *  Function overrides default createEditor function to return the
         *  custom editor for the first column.
         *
         *  @param parent - pointer to parent widget
         *  @param option - reference to the options for the editor to use
         *  @param index - reference to the index that the editor is being
         *      created for
         *
         *  @return - pointer to the newly created editor
         */
        virtual QWidget* createEditor(QWidget *parent,
            const QStyleOptionViewItem &option, const QModelIndex &index) const;

        /**
         *  Function sets the model that is displaying the custom editor.
         *
         *  @param column - int representing the column to display the editor in.
         */
        void setColumn(const int column);

        /**
         *  Functions sets the column that is displayed on the combobox.
         *  Defaults to 0
         *
         *  @param column - int representing the column of the model to 
         *      display on the combobox
         */
        void setDisplayColumn(const int column);

        /**
         *  Functions sets the column that is stored for data on the combobox.
         *  Defaults to 0
         *
         *  @param column - int representing the column of the model to
         *      use as data
         */
        void setEditColumn(const int column);

        /**
         *  Function sets the data for the current editor
         *
         *  @param editor - editor that is being manipulated
         *  @param index - the index containing the data to set to
         */
        virtual void setEditorData(QWidget *editor,
            const QModelIndex &index) const;

        /**
         *  Function allows the user to set the custom editor's model.
         *
         *  @param model - model to set the custom editor to use
         */
        virtual void setEditorModel(QAbstractItemModel *model);

        /**
         *  Function sets the data for the current model
         *
         *  @param editor - the editor that contains the data
         *  @param model - pointer to the model that the data is being saved to
         *  @param index - pointer to the index that the data is being saved to
         */
        virtual void setModelData(QWidget *editor, QAbstractItemModel *model,
            const QModelIndex &index) const;

    private:
        int comboColumn;
        int editColumn;
        int displayColumn;
        QAbstractItemModel *editorModel;
    };
}

#endif