#include "QComboBox"
#include "ComboEditorDelegate.h"

namespace Commissionator {

    ComboEditorDelegate::ComboEditorDelegate(QObject *parent) : QStyledItemDelegate(parent) {
       comboColumn = 0;
       editColumn = 0;
       displayColumn = 0;
    }

    QWidget* ComboEditorDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem &option, const QModelIndex &index) const {
        if (index.column() !=comboColumn)
            return QStyledItemDelegate::createEditor(parent, option, index);
        QComboBox *combo = new QComboBox(parent);
        combo->setModel(editorModel);
        combo->setModelColumn(displayColumn);
        combo->setCurrentIndex(-1);
        return combo;
    }

    void ComboEditorDelegate::setColumn(const int column) {
       comboColumn = column;
    }

    void ComboEditorDelegate::setDisplayColumn(const int column) {
        displayColumn = column;
    }

    void ComboEditorDelegate::setEditColumn(const int column) {
        editColumn = column;
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
        if (auto *combo = qobject_cast<QComboBox *>(editor)) {
            model->setData(index,
                combo->currentIndex(),
                Qt::DisplayRole);
            model->setData(index,
                combo->model()->index(0, editColumn),
                Qt::EditRole);
        } else
            QStyledItemDelegate::setModelData(editor, model, index);
    }
}