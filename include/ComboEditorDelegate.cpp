#include "QComboBox"
#include "ComboEditorDelegate.h"

namespace Commissionator {

    ComboEditorDelegate::ComboEditorDelegate(QObject *parent) : CustomEditorDelegate(parent) {
        customEditor = new QComboBox();
    }

    void ComboEditorDelegate::setEditorData(QWidget *editor, 
        const QModelIndex &index) const {
        if (auto *combo = qobject_cast<QComboBox *>(editor)) {
            QString text = index.data(Qt::EditRole).toString();
            int index = qobject_cast<QComboBox *>(customEditor)->findText(text);
            if (index >= 0)
                combo->setCurrentIndex(index);
        } else
            QStyledItemDelegate::setEditorData(editor, index);
    }

    void ComboEditorDelegate::setEditorModel(QAbstractItemModel *model) {
        qobject_cast<QComboBox *>(customEditor)->setModel(model);
    }

    void ComboEditorDelegate::setModelData(QWidget *editor, 
        QAbstractItemModel *model, const QModelIndex &index) const {
        if (auto *combo = qobject_cast<QComboBox *>(editor))
            model->setData(index, 
            qobject_cast<QComboBox *>(customEditor)->currentText(), 
            Qt::EditRole);
        else
            QStyledItemDelegate::setModelData(editor, model, index);
    }
}