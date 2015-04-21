#include <QLabel>
#include <QSqlRecord>
#include "CommissionerPanel.h"

namespace Commissionator {

    CommissionerPanel::CommissionerPanel(QSqlQueryModel *commissionerModel, 
        QSqlQueryModel *contactModel, QSqlQueryModel *commissionsModel) {
        layout = new QVBoxLayout(this);

        commissionerName = new QLabel();
        layout->addWidget(commissionerName);

        commissionerDate = new QLabel();
        layout->addWidget(commissionerDate);

        commissionerPaid = new QLabel();
        layout->addWidget(commissionerPaid);

        contactInfoLabel = new QLabel(tr("Contact Info:"));
        layout->addWidget(contactInfoLabel);

        contactInfoTable = new FixedRowTable(contactModel); 
        contactInfoTable->setBoxBottom(true);
        contactInfoTable->setBoxButtonActivated(true);
        contactInfoTable->setBoxButtonWidth(2.5);
        contactInfoTable->setBoxButtonText(tr("Insert"));
        layout->addWidget(contactInfoTable);

        commissionsLabel = new QLabel(tr("Commissions:"));
        layout->addWidget(commissionsLabel);

        commissionsTable = new FixedRowTable(commissionsModel);
        layout->addWidget(commissionsTable);

        newCommissionButton = new QPushButton(tr("New Commission"));
        layout->addWidget(newCommissionButton);

        notesLabel = new QLabel(tr("Notes"));
        layout->addWidget(notesLabel);

        notesEdit = new QTextEdit();
        layout->addWidget(notesEdit);

        commissionerMapper = new QDataWidgetMapper(this);
        commissionerMapper->setModel(commissionerModel);
        commissionerMapper->addMapping(commissionerName, 0);
        commissionerMapper->addMapping(commissionerDate, 1);
        commissionerMapper->addMapping(commissionerPaid, 2);
        commissionerMapper->addMapping(notesEdit, 4);

        setLayout(layout);
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
        delete commissionerMapper;
    }
}