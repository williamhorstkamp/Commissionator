#include <QLabel>
#include <QSqlRecord>
#include "CommissionerPanel.h"

namespace Commissionator {

    CommissionerPanel::CommissionerPanel(QSqlQueryModel *commissionerModel, 
        QSqlQueryModel *contactModel, QSqlQueryModel *commissionsModel) {
        this->commissionerModel = commissionerModel;
        
        createFonts();
        createLabels();
        createTables(contactModel, commissionsModel);
        createPanel();
    }

    CommissionerPanel::~CommissionerPanel() {
        delete commissionerName;
        delete commissionerDate;
        delete commissionerPaid;
        delete contactInfoLabel;
        delete contactInfoTable;
        delete commissionsLabel;
        delete commissionsTable;
        delete newCommissionButton;
        delete notesLabel;
        delete notesEdit;
        delete layout;
        delete titleFont;
        delete standardFont;
    }

    void CommissionerPanel::createFonts() {
        titleFont = new QFont();
        titleFont->setPointSize(12);
        titleFont->setBold(true);

        standardFont = new QFont();
        standardFont->setPointSize(10);
    }

    void CommissionerPanel::createLabels() {
        commissionerName = new QLabel();
        commissionerName->setAlignment(Qt::AlignCenter);
        commissionerName->setFont(*titleFont);
        

        commissionerDate = new QLabel();
        commissionerDate->setAlignment(Qt::AlignCenter);
        commissionerDate->setFont(*standardFont);
       

        commissionerPaid = new QLabel();
        commissionerPaid->setAlignment(Qt::AlignCenter);
        commissionerPaid->setFont(*standardFont);
        

        contactInfoLabel = new QLabel(tr("Contact Info:"));
        contactInfoLabel->setAlignment(Qt::AlignCenter);
        contactInfoLabel->setFont(*standardFont);

        commissionsLabel = new QLabel(tr("Commissions:"));
        commissionsLabel->setAlignment(Qt::AlignCenter);
        commissionsLabel->setFont(*standardFont);

        notesLabel = new QLabel(tr("Notes"));
        notesLabel->setAlignment(Qt::AlignCenter);
        notesLabel->setFont(*standardFont);

        notesEdit = new QTextEdit();
    }

    void CommissionerPanel::createPanel() {
        layout = new QVBoxLayout(this);

        layout->addWidget(commissionerName);
        layout->addWidget(commissionerDate);
        layout->addWidget(commissionerPaid);
        layout->addWidget(contactInfoLabel);
        layout->addWidget(contactInfoTable);
        layout->addWidget(commissionsLabel);
        layout->addWidget(commissionsTable);
        layout->addWidget(newCommissionButton);
        layout->addWidget(notesLabel);
        layout->addWidget(notesEdit);
        setLayout(layout);
    }

    void CommissionerPanel::createTables(QSqlQueryModel *contactModel, QSqlQueryModel *commissionsModel) {
        contactInfoTable = new FixedRowTable(contactModel);
        contactInfoTable->setBoxBottom(true);
        contactInfoTable->setBoxButtonActivated(true);
        contactInfoTable->setBoxButtonWidth(2.5);
        contactInfoTable->setBoxButtonText(tr("Insert"));

        commissionsTable = new QTableView(this);
        commissionsTable->setModel(commissionsModel);

        newCommissionButton = new QPushButton(tr("New Commission"));
    }

    void CommissionerPanel::updatePanel() {
        commissionerName->setText(commissionerModel->record(0).value(0).toString());
        if (commissionerModel->record(0).value(1).toString() == "No Commissions")
            commissionerDate->setText(commissionerModel->record(0).value(1).toString());
        else
            commissionerDate->setText("Customer since " + commissionerModel->record(0).value(1).toString());
        if (commissionerModel->record(0).value(2).toString() == "Paid Off")
            commissionerPaid->setStyleSheet("QLabel { color : green; }");
        else if (commissionerModel->record(0).value(2).toString() == "No Commissioned Pieces")
            commissionerPaid->setStyleSheet("QLabel { color : blue; }");
        else
            commissionerPaid->setStyleSheet("QLabel { color : red; }");
        commissionerPaid->setText(commissionerModel->record(0).value(2).toString());
        notesEdit->setText(commissionerModel->record(0).value(3).toString());
    }
}