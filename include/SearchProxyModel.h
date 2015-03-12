#ifndef SEARCHPROXYMODEL_H
#define SEARCGPROXYMODEL_H

#include <QIdentityProxyModel>

namespace Commissionator {

    class SearchProxyModel : public QIdentityProxyModel {

        Q_OBJECT

    public:
        /**
         *  Default constructor overrides QIdentityProxyModel()
         */
        SearchProxyModel(QObject *parent);

        /**
         *  Overrides the default setSourceModel. Provides default functionality
         *  plus prepares the QStrings containing the search input
         *
         *  @param newSourceModel - the model that this model is going to proxy
         */
        void setSourceModel(QAbstractItemModel *newSourceModel);

        /**
         *  Overrides the default rowCount function and adds an additional row
         *  for the search row.
         *
         *  @param parent - reference containing the parent model
         */
        int rowCount(const QModelIndex &parent = QModelIndex()) const;

        //int columnCount(const QModelIndex &parent = QModelIndex()) const;

        /**
         *  Overrides default index function to handle the extra search row.
         *
         *  @param row - int containing the row to get the index for
         *  @param colunn - int containing the colunn to get the index for
         *  @param parent - reference containing the parent model
         */
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

        /**
         *  Overrides the default data function to handle the new search row
         *  and put it at the top.
         *
         *  @param index - reference to the index to retrieve the data for
         *  @param role - Qt role that the data is retrieving
         */
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

        /**
         *  Overrides the default flags function to handle the new search row.
         *
         *  @param index - reference to the index to retrieve the data for
         */
        Qt::ItemFlags flags(const QModelIndex &index) const;

        /**
         *  Overrides the default setData function to handle the new search row
         *
         *  @param index - reference to the index to retrieve the data for
         *  @param value - reference containing the data to set the index to
         *  @param role - Qt role that the data is being set for
         */
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

        /**
         *  Search function that performs a search based on the current values
         *  of the search strings.
         */
        void search();

    private:
        //List of QStrings containing the value to search with
        QList<QString> searchStrings;
    };

}
#endif