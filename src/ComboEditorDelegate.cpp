#include "QComboBox"
#include "ComboEditorDelegate.h"

namespace Commissionator {

    ComboEditorDelegate::ComboEditorDelegate(QObject *parent) : QStyledItemDelegate(parent) {
        editorColumn = 0;
    }

    QWidget* ComboEditorDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option, const QModelIndex &index) const {
        if (index.column() != editorColumn)
            return QStyledItemDelegate::createEditor(parent, option, index);
        QComboBox *combo = new QComboBox(parent);
        combo->setModel(editorModel);
        return combo;
    }

    void ComboEditorDelegate::setColumn(const int column) {
        editorColumn = column;
    }

    void ComboEditorDelegate::setEditorData(QWidget *editor, 
        const QModelIndex &index) const {
        if (auto *combo = qobject_cast<QComboBox *>(editor)) {
            QString text = index.data(Qt::EditRole).toString();
            int index = combo->findText(text);
            if (index >= 0)
                combo->setCurrentIndex(index);
        } else
            QStyledItemDelegate::setEditorData(editor, index);
    }

    void ComboEditorDelegate::setEditorModel(QAbstractItemModel *model) {
        editorModel = model;
    }

    void ComboEditorDelegate::setModelData(QWidget *editor, 
        QAbstractItemModel *model, const QModelIndex &index) const {
        if (auto *combo = qobject_cast<QComboBox *>(editor))
            model->setData(index, 
            combo->currentText(), 
            Qt::EditRole);
        else
            QStyledItemDelegate::setModelData(editor, model, index);
    }
}