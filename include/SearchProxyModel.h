#ifndef SEARCHPROXYMODEL_H
#define SEARCGPROXYMODEL_H

#include <QIdentityProxyModel>

namespace Commissionator {

    class SearchProxyModel : public QIdentityProxyModel {

        Q_OBJECT

    public:
        SearchProxyModel(QObject *parent);

        void setSourceModel(QAbstractItemModel *newSourceModel);
        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        //int columnCount(const QModelIndex &parent = QModelIndex()) const;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
        Qt::ItemFlags flags(const QModelIndex &index) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
        void search(const QList<QString> searchEntries = QList<QString>());

    private:
        QList<QString> searchLabels;
    };

}
#endif