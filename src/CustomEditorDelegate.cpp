#include "CustomEditorDelegate.h"

namespace Commissionator {
    CustomEditorDelegate::CustomEditorDelegate(QObject *parent) :
        QStyledItemDelegate(parent) {
        editorColumn = 0;
    }

    CustomEditorDelegate::~CustomEditorDelegate() {
        delete customEditor;
    }

    QWidget* CustomEditorDelegate::createEditor(QWidget *parent, 
        const QStyleOptionViewItem &option, const QModelIndex &index) const {
        if (index.column() == editorColumn)
            return customEditor;
        return QStyledItemDelegate::createEditor(parent, option, index);        
    }

    void CustomEditorDelegate::destroyEditor(QWidget *editor,
        const QModelIndex &index) const {
        if (index.column() != editorColumn)
            QStyledItemDelegate::destroyEditor(editor, index);
    }

    void CustomEditorDelegate::setColumn(const int column) {
        editorColumn = column;
    }
}