#include "CommissionerPanel.h"

namespace Commissionator {

    CommissionerPanel::CommissionerPanel(QSqlQueryModel *contactModel, QSqlQueryModel *commissionsModel) {
        init();

    }

    CommissionerPanel::~CommissionerPanel() {
        delete layout;
        delete commissionerName;
        delete commissionerDate;
        delete commissionerPaid;
        delete contactInfoLabel;
        //delete contactInfoTable;
        delete commissionsLabel;
        delete commissionsTable;
        delete newCommissionButton;
        delete notesLabel;
        delete notesEdit;
    }

    void CommissionerPanel::init() {
        layout = new QVBoxLayout(this);
        //commissionerName;
        //commissionerDate;
        //commissionerPaid;
        contactInfoLabel = new QLabel("Contact Info:");
        //InsertTableView contactInfoTable;
        commissionsLabel = new QLabel("Commissions:");
        //QTableView commissionsTable;
        //QPushButton newCommissionButton;
        notesLabel = new QLabel("Notes");
        //QTextEdit notesEdit;
    }

}