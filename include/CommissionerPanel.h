#ifndef COMMISSIONERPANEL_H
#define COMMISSIONERPANEL_H

#include <QVBoxLayout>
#include <QLabel>
#include <QTableView>
#include <QTextEdit>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QDataWidgetMapper>
#include "FixedRowTable.h"

namespace Commissionator {
    class CommissionerPanel : public QWidget {

        Q_OBJECT

    public:
        CommissionerPanel(QSqlQueryModel *commissionerModel, 
            QSqlQueryModel *contactModel, QSqlQueryModel *commissionsModel);
        ~CommissionerPanel();

    private:
        QVBoxLayout *layout;
        QDataWidgetMapper *commissionerMapper;
        QLabel *commissionerName;
        QLabel *commissionerDate;
        QLabel *commissionerPaid;
        QLabel *contactInfoLabel;
        FixedRowTable *contactInfoTable;
        QLabel *commissionsLabel;
        FixedRowTable *commissionsTable;
        QPushButton *newCommissionButton;
        QLabel *notesLabel;
        QTextEdit *notesEdit;

    signals:
        void insertContact(const QList<QVariant> query);
        void newCommission();

    };
}

#endif