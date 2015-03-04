#ifndef LEFTPROXYMODEL_H
#define LEFTPROXYMODEL_H

#include <QAbstractProxyModel>

namespace Commissionator {

    class LeftProxyModel : public QAbstractProxyModel {

        Q_OBJECT

    public:
        LeftProxyModel(QObject *parent = 0) : QAbstractProxyModel(parent) {};

        //void setSourceModel(QAbstractItemModel *newSourceModel);
        QModelIndex mapFromSource(const QModelIndex &index) const;
        QModelIndex	mapToSource(const QModelIndex &index) const;
        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex &parent = QModelIndex()) const;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
        QModelIndex parent(const QModelIndex &child) const;
    };

}
#endif