#ifndef COMMISSIONERCONTACTDELEGATE_H
#define COMMISSIONERCONTACTDELEGATE_H

#include <QComboBox>
#include "FixedRowTableDelegate.h"

namespace Commissionator {

    class CommissionerContactDelegate : public FixedRowTableDelegate {

        Q_OBJECT

    public:

        CommissionerContactDelegate(QObject *parent = 0);

        QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

        void setComboBoxModel(QAbstractItemModel *model);

        void setEditorData(QWidget *editor, const QModelIndex &index) const;

        void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    private:
        QComboBox *comboEditor;
    };

}

#endif