#include "CustomEditorDelegate.h"

namespace Commissionator {
    CustomEditorDelegate::CustomEditorDelegate(QObject *parent) :
        FixedRowTableDelegate(parent) {
        editorColumn = 0;
    }

    CustomEditorDelegate::~CustomEditorDelegate() {
        delete customEditor;
    }

    QWidget* CustomEditorDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        if (index.column() == 0)
            return customEditor;
        return QStyledItemDelegate::createEditor(parent, option, index);        
    }

    void CustomEditorDelegate::setColumn(const int column) {
        editorColumn = column;
    }
}