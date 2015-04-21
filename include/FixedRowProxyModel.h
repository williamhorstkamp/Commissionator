#ifndef FIXEDROWPROXYMODEL_H
#define FIXEDROWPROXYMODEL_H

#include <QIdentityProxyModel>

namespace Commissionator {

    /**
     *  Class is used as a proxy model to add and handle an insertable row
     *  at the top of the table. For use with FixedRowTable and FixedRowBox
     */
    class FixedRowProxyModel : public QIdentityProxyModel {

        Q_OBJECT

    public:
        /**
         *  Default constructor overrides QIdentityProxyModel()
         *
         *  @param parent - pointer to parent
         */
        FixedRowProxyModel(QObject *parent);

        /**
         *  Overrides the default setSourceModel. Provides default functionality
         *  plus prepares the QStrings containing the input
         *
         *  @param newSourceModel - the model that this model is going to proxy
         */
        void setSourceModel(QAbstractItemModel *newSourceModel);

        /**
         *  Overrides the default rowCount function and adds an additional row
         *  for the insertion row.
         *
         *  @param parent - reference containing the parent model
         *
         *  @return - number of rows as an integer
         */
        int rowCount(const QModelIndex &parent = QModelIndex()) const;

        /**
         *  Overrides default index function to handle the extra row.
         *
         *  @param row - int containing the row to get the index for
         *  @param colunn - int containing the colunn to get the index for
         *  @param parent - reference containing the parent model
         *
         *  @return - Model Index at the row, column combination
         */
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

        /**
         *  Overrides the default data function to handle the new row
         *  and place it where it at either the top or bottom.
         *
         *  @param index - reference to the index to retrieve the data for
         *  @param role - Qt role that the data is retrieving
         *
         *  @return - QVariant containing the data for the given index
         */
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

        /**
         *  Overrides the default flags function to handle the new row.
         *
         *  @param index - reference to the index to retrieve the data for
         *
         *  @return - List of ItemFlags for the index
         */
        Qt::ItemFlags flags(const QModelIndex &index) const;

        /**
         *  Overrides the default setData function to handle the new row
         *
         *  @param index - reference to the index to retrieve the data for
         *  @param value - reference containing the data to set the index to
         *  @param role - Qt role that the data is being set for
         *
         *  @return - boolean representing whether data was corrected set or not
         */
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

        /**
         *  Sets the text that occupies the proxied row.
         *  Overrides anything that is currently in the bar and replaces it
         *  with the new text.
         *
         *  @param newText - text to set the fields to
         */
        void setText(QString newText);

    private:
        //List of QStrings containing the value to use with the query
        QList<QVariant> queryStrings;
        QString text;
        //bool bottom;

    signals:
        /**
         *  Signal that contains the query.
         *  The data captured in this signal is forward to FixedRowTable signal
         *  named buttonClicked.
         *
         *  @param query - QList of QVariants containing the search query
         */
        void querySignal(const QList<QVariant> query);

    public slots:
        /**
         *  Search slot that performs a search based on the current values
         *  of the search strings.
         */
        void query();
    };
}
#endif