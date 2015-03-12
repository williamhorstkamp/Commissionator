#include <QFont>
#include <QLabel>
#include <QGuiApplication>
#include "SearchProxyModel.h"

namespace Commissionator {

    SearchProxyModel::SearchProxyModel(QObject *parent) : QIdentityProxyModel(parent) {
        searchStrings = QList<QString>();
    }

    void SearchProxyModel::setSourceModel(QAbstractItemModel *newSourceModel) {
        QIdentityProxyModel::setSourceModel(newSourceModel);
        for (int i = 0; i < columnCount(); i++)
            searchStrings.insert(i, "Search");
    }

    int SearchProxyModel::rowCount(const QModelIndex &parent) const {
        if (!sourceModel())
            return 0;
        return QIdentityProxyModel::rowCount(parent) + 1;
    }
    /**
    int LeftProxyModel::columnCount(const QModelIndex &parent) const {
        if (!sourceModel())
            return 0;
        return sourceModel()->columnCount(parent);
    }
    */
    QModelIndex SearchProxyModel::index(int row, int column, const QModelIndex &parent) const {
        if (sourceModel())
            if (row == rowCount() - 1)
                return createIndex(rowCount() - 1, column);
        return QIdentityProxyModel::index(row, column, parent);
    }
    QVariant SearchProxyModel::data(const QModelIndex &index, int role) const {
        if (index.isValid()){
            if (role == Qt::DisplayRole) {
                if (index.row() == 0) {
                    return QVariant(searchStrings.at(index.column()));
                }
                return QIdentityProxyModel::data(this->index(index.row() - 1, index.column(), index.parent()), role);
            }
            if (role == Qt::FontRole) {
                if (index.row() == 0) {
                    QFont font(QGuiApplication::font());
                    font.setItalic(true);
                    return font;
                }
            }
        }
        return QVariant();
    }
    
    bool SearchProxyModel::setData(const QModelIndex &index, const QVariant &value, int role) {
        if (index.row() == 0) {
            searchStrings.replace(index.column(), value.toString());
            emit QIdentityProxyModel::dataChanged(index, index);
            return true;
        }
        return QIdentityProxyModel::setData(this->index(index.row() -1, index.column(), index.parent()), value, role);
    }

    Qt::ItemFlags SearchProxyModel::flags(const QModelIndex &index) const {
        Qt::ItemFlags flags = QIdentityProxyModel::flags(index);
        if (index.row() != 0)
            flags &= ~Qt::ItemIsEditable;
        return flags;
    }

    void SearchProxyModel::search() {
        //needs to actually search
        for (int i = 0; i < columnCount(); i++)
            searchStrings.replace(i, "Search");
    }
}