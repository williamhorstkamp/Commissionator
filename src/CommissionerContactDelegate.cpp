#include "CommissionerContactDelegate.h"

namespace Commissionator {
    CommissionerContactDelegate::CommissionerContactDelegate(QObject *parent) :
        FixedRowTableDelegate(parent) {
        comboEditor = new QComboBox();
        comboEditor->addItem(QString("one"));
        comboEditor->addItem(QString("two"));
        comboEditor->addItem(QString("three"));
    }

    QWidget* CommissionerContactDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
        if (index.column() == 0)
            return comboEditor;
        return QStyledItemDelegate::createEditor(parent, option, index);        
    }

    void CommissionerContactDelegate::setComboBoxModel(QAbstractItemModel *model) {
        comboEditor->setModel(model);
    }

    void CommissionerContactDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
        if (QComboBox *combo = qobject_cast<QComboBox *>(editor)) {
            QString text = index.data(Qt::EditRole).toString();
            int comboIndex = combo->findText(text);
            if (comboIndex >= 0)
                combo->setCurrentIndex(comboIndex);
        } else
            QStyledItemDelegate::setEditorData(editor, index);
    }

    void CommissionerContactDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
        if (QComboBox *combo = qobject_cast<QComboBox *>(editor))
            model->setData(index, combo->currentText(), Qt::EditRole);
        else
            QStyledItemDelegate::setModelData(editor, model, index);
    }
}