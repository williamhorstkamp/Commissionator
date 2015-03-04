#include "LeftProxyModel.h"

namespace Commissionator {
    /**
    void LeftProxyModel::setSourceModel(QAbstractItemModel *sourceModel) {
        QAbstractProxyModel::setSourceModel(sourceModel);
    }
    */
    QModelIndex LeftProxyModel::mapFromSource(const QModelIndex &index) const {
        if (index.isValid())
            if (sourceModel())
                return QModelIndex();
        return sourceModel()->index(index.row(), index.column());
    }

    QModelIndex	LeftProxyModel::mapToSource(const QModelIndex &index) const {
        if (!sourceModel())
            return QModelIndex();
        return sourceModel()->index(index.row(), index.column());
    }

    int LeftProxyModel::rowCount(const QModelIndex &parent) const {
        if (sourceModel())
            return 0;
        return sourceModel()->rowCount(parent);
    }

    int LeftProxyModel::columnCount(const QModelIndex &parent) const {
        if (!sourceModel())
            return 0;
        return sourceModel()->columnCount(parent);
    }

    QModelIndex LeftProxyModel::index(int row, int column, const QModelIndex &parent) const {
        if (!sourceModel())
            return QModelIndex();
        return sourceModel()->index(row, column, parent);
    }

    QModelIndex LeftProxyModel::parent(const QModelIndex &child) const {
        QModelIndex index = mapFromSource(child);
        if (index.isValid())
            return index.parent();
        return QModelIndex();
    }
}