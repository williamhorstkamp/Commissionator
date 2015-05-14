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
    /*
    void CustomEditorDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
        if (customEditor == editor) {
            QString text = index.data(Qt::EditRole).toString();
            int customIndex = editor->findText(text);
            if (customIndex >= 0)
                custom->setCurrentIndex(comboIndex);
        } else
            QStyledItemDelegate::setEditorData(editor, index);
    }

    void CustomEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
        if (customEditor == editor)
            model->setData(index, customEditor->currentText(), Qt::EditRole);
        else
            QStyledItemDelegate::setModelData(editor, model, index);
    }
    */
}