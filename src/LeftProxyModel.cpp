#include <QFont>
#include <QGuiApplication>
#include "LeftProxyModel.h"

namespace Commissionator {

    int LeftProxyModel::rowCount(const QModelIndex &parent) const {
        if (!sourceModel())
            return 0;
        return QIdentityProxyModel::rowCount(parent) + 1;
        //return 1;
    }
    /**
    int LeftProxyModel::columnCount(const QModelIndex &parent) const {
        if (!sourceModel())
            return 0;
        return sourceModel()->columnCount(parent);
    }
    */
    QModelIndex LeftProxyModel::index(int row, int column, const QModelIndex &parent) const {
        if (sourceModel())
            if (row == rowCount() - 1)
                return createIndex(row, column);
        return QIdentityProxyModel::index(row, column, parent);
        //return QModelIndex();
    }
    QVariant LeftProxyModel::data(const QModelIndex &index, int role) const {
        if (index.isValid()){
            if (role == Qt::DisplayRole) {
                if (index.row() == rowCount() - 1) {
                    return QVariant("Search");
                }
                return QIdentityProxyModel::data(index, role);
            }
            if (role == Qt::FontRole) {
                if (index.row() == rowCount() - 1) {
                    QFont font(QGuiApplication::font());
                    font.setItalic(true);
                    return font;
                }
            }
        }
        return QVariant();
    }
    
    bool LeftProxyModel::setData(const QModelIndex &index, const QVariant &value, int role) {
        if (index.row() == rowCount() - 1) {
            return false;   //this is where the signal will be emitted
        }
        return QIdentityProxyModel::setData(index, value, role);
    }

    Qt::ItemFlags LeftProxyModel::flags(const QModelIndex &index) const {
        Qt::ItemFlags flags = QIdentityProxyModel::flags(index);
        if (index.row() != rowCount() - 1)
            flags &= ~Qt::ItemIsEditable;
        return flags;
    }
}