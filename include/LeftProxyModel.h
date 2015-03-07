#ifndef LEFTPROXYMODEL_H
#define LEFTPROXYMODEL_H

#include <QIdentityProxyModel>

namespace Commissionator {

    class LeftProxyModel : public QIdentityProxyModel {

        Q_OBJECT

    public:
        LeftProxyModel::LeftProxyModel(QObject *parent) : QIdentityProxyModel(parent) {};

        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        //int columnCount(const QModelIndex &parent = QModelIndex()) const;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    };

}
#endif