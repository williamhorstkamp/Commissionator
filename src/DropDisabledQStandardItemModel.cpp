#include "DropDisabledQStandardItemModel.h"

namespace Commissionator {
    DropDisabledQStandardItemModel::
        DropDisabledQStandardItemModel(QObject *parent) : QStandardItemModel(parent) {}

    Qt::ItemFlags DropDisabledQStandardItemModel::
        flags(const QModelIndex &index) const {
        if(!index.isValid())
            return QStandardItemModel::flags(index);
        return QStandardItemModel::flags(index) &= ~Qt::ItemIsDropEnabled;
    }
}