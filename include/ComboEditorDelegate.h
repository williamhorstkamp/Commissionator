#ifndef COMBOTEDITORDELEGATE_H
#define COMBOTEDITORDELEGATE_H

#include "CustomEditorDelegate.h"

namespace Commissionator {

    class ComboEditorDelegate : public CustomEditorDelegate {
        
        Q_OBJECT

    public:

        /**
         *  Default constructor initializes customEditor as combobox
         */
        ComboEditorDelegate(QObject *parent = nullptr);

        /**
         *  Function sets the data for the current editor
         *
         *  @param editor - editor that is being manipulated
         *  @param index - the index containing the data to set to
         */
        void setEditorData(QWidget *editor,
            const QModelIndex &index) const;

        /**
         *  Function allows the user to set the custom editor's model.
         *
         *  @param model - model to set the custom editor to use
         */
        void setEditorModel(QAbstractItemModel *model);

        /**
         *  Function sets the data for the current model
         *
         *  @param editor - the editor that contains the data
         *  @param model - pointer to the model that the data is being saved to
         *  @param index - pointer to the index that the data is being saved to
         */
        void setModelData(QWidget *editor, QAbstractItemModel *model,
            const QModelIndex &index) const;
    };
}

#endif