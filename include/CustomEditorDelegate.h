#ifndef COMMISSIONERCONTACTDELEGATE_H
#define COMMISSIONERCONTACTDELEGATE_H

#include "FixedRowTableDelegate.h"

namespace Commissionator {

    class CustomEditorDelegate : public FixedRowTableDelegate {

        Q_OBJECT

    public:

        /**
         *  Default constructor initializes customEditor
         *
         *  @param parent - Pointer to the objects parent.
         */
        CustomEditorDelegate(QObject *parent = nullptr);

        /**
         *  Destructor deletes customEditor
         */
        ~CustomEditorDelegate();

        /**
         *  Function overrides default createEditor function to return the
         *  customEditor for the first column.
         *
         *  @param parent - pointer to parent widget
         *  @param option - reference to the options for the editor to use
         *  @param index - reference to the index that the editor is being 
         *      created for
         *
         *  @return - pointer to the newly created editor
         */
        QWidget* createEditor(QWidget *parent, 
            const QStyleOptionViewItem &option, const QModelIndex &index) const;

        /**
         *  Function allows the user to set the custom editor's model.
         *
         *  @param model - model to set the custom editor to use
         */
        virtual void setEditorModel(QAbstractItemModel *model) = 0;

        /**
         *  Function sets the model that is displaying the custom editor.
         */
        void setColumn(const int column);

        /**
         *  Function sets the data for the current editor
         *
         *  @param editor - editor that is being manipulated
         *  @param index - the index containing the data to set to
         */
        virtual void setEditorData(QWidget *editor, 
            const QModelIndex &index) const = 0;

        /**
         *  Function sets the data for the current model
         *
         *  @param editor - the editor that contains the data
         *  @param model - pointer to the model that the data is being saved to
         *  @param index - pointer to the index that the data is being saved to
         */
        virtual void setModelData(QWidget *editor, QAbstractItemModel *model, 
            const QModelIndex &index) const = 0;
    
    private:
        int editorColumn;
        QWidget *customEditor;
    };
}
#endif