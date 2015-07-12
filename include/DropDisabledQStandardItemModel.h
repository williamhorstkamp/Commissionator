#ifndef DROPDISABLEDQSTANDARDITEMMODEL_H
#define DROPDISABLEDQSTANDARDITEMMODEL_H

#include <QStandardItemModel>

namespace Commissionator {
    class DropDisabledQStandardItemModel : public QStandardItemModel {
    
        Q_OBJECT

    public:

        /**
         *  Constructor simply runs the QStandardItemModel constructor
         *
         *  @param parent - pointer to the parent object
         */
        DropDisabledQStandardItemModel(QObject *parent = nullptr);

        /**
         *  Reimplemented flags prevents drop overwriting of items, but still
         *  allos reorganization
         *
         *  @param index - index that whose flags are being checked
         *
         *  @return - list of flags
         */
        Qt::ItemFlags flags(const QModelIndex &index) const;
    };
}

#endif