#ifndef COMMISSIONERPANEL_H
#define COMMISSIONERPANEL_H

#include <QVBoxLayout>
#include <QLabel>
#include <QTableView>
/**
#include <QTextEdit>
#include <QPushButton>
#include <QSqlQueryModel>

namespace Commissionator {
    class CommissionerPanel : public QWidget {

        Q_OBJECT

    public:
        CommissionerPanel(QSqlQueryModel *contactModel, QSqlQueryModel *commissionsModel);
        ~CommissionerPanel();

    private:
        void init();

        QVBoxLayout *layout;
        QLabel commissionerName;
        QLabel commissionerDate;
        QLabel commissionerPaid;
        QLabel contactInfoLabel;
        //InsertTableView contactInfoTable;
        QLabel commissionsLabel;
        QTableView commissionsTable;
        QPushButton newCommissionButton;
        QLabel notesLabel;
        QTextEdit notesEdit;
    };
}

#endif
*/