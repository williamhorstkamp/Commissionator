#include <QFont>
#include <QLabel>
#include <QGuiApplication>
#include "FixedRowProxyModel.h"

namespace Commissionator {

    FixedRowProxyModel::FixedRowProxyModel(QObject *parent) : QIdentityProxyModel(parent) {
        text = QString("");
        queryStrings = QList<QVariant>();
    }

    void FixedRowProxyModel::setSourceModel(QAbstractItemModel *newSourceModel) {
        QIdentityProxyModel::setSourceModel(newSourceModel);
        connect(sourceModel(), &QAbstractItemModel::rowsInserted, this, &FixedRowProxyModel::refreshText);
        refreshText();
    }

    int FixedRowProxyModel::rowCount(const QModelIndex &parent) const {
        if (!sourceModel())
            return 0;
        return QIdentityProxyModel::rowCount(parent) + 1;
    }

    QModelIndex FixedRowProxyModel::index(int row, int column, const QModelIndex &parent) const {
        if (sourceModel())
            if (row == rowCount() - 1)
                return createIndex(rowCount() - 1, column);
        return QIdentityProxyModel::index(row, column, parent);
    }

    QVariant FixedRowProxyModel::data(const QModelIndex &index, int role) const {
        if (index.isValid()) {
            if (role == Qt::DisplayRole) {
                if (index.row() == 0) {
                    if (index.column() < queryStrings.count())
                        return QVariant(queryStrings.at(index.column()));
                    return QVariant();
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

    bool FixedRowProxyModel::setData(const QModelIndex &index, const QVariant &value, int role) {
        if (index.row() == 0) {
            if (!value.toString().isEmpty()) {
                while (queryStrings.count() < columnCount())
                    queryStrings.append(text);
                queryStrings.replace(index.column(), value.toString());
            }
            emit QIdentityProxyModel::dataChanged(this->index(0, 0), this->index(0, columnCount() - 1));
            return true;
        }
        return QIdentityProxyModel::setData(this->index(index.row() -1, index.column(), index.parent()), value, role);
    }

    void FixedRowProxyModel::setText(QString newText) {
        text = newText;
        for (int i = 0; i < queryStrings.length(); i++)
            queryStrings.replace(i, text);
    }

    Qt::ItemFlags FixedRowProxyModel::flags(const QModelIndex &index) const {
        Qt::ItemFlags flags = QIdentityProxyModel::flags(index);
        if (index.row() != 0)
            flags &= ~Qt::ItemIsEditable;
        return flags;
    }

    void FixedRowProxyModel::query() {
        while (queryStrings.length() < columnCount())
            queryStrings.append(text);
        for (int i = 0; i < queryStrings.length(); i++)     //replace any place that the set text is stored 
            if (queryStrings[i].toString() == text)   //with an empty string
                queryStrings.replace(i, QVariant(""));   // to show that there was no entry to that field
        emit querySignal(queryStrings);
        refreshText();
    }

    void FixedRowProxyModel::refreshText() {
        while (queryStrings.length() < columnCount())
            queryStrings.append(text);
        for (int i = 0; i < queryStrings.length(); i++)
            queryStrings.replace(i, text);
        emit dataChanged(index(0, 0), index(0, columnCount()));
    }
}