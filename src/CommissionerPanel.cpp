#include <QLabel>
#include <QSqlRecord>
#include "FixedRowTable.h"
#include "QHeaderView"
#include "ComboEditorDelegate.h"
#include "CommissionerPanel.h"

namespace Commissionator {

    CommissionerPanel::CommissionerPanel(QSqlQueryModel *commissionerModel, 
        QSqlQueryModel *contactModel, QSqlQueryModel *commissionsModel,
        QSqlQueryModel *contactTypesModel) {
        this->commissionerModel = commissionerModel;
        
        createFonts();
        createLabels();
        createTables(contactModel, commissionsModel, contactTypesModel);
        createPanel();
    }

    CommissionerPanel::~CommissionerPanel() {
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
        commissionerName = new QLabel(this);
        commissionerName->setAlignment(Qt::AlignCenter);
        commissionerName->setFont(*titleFont); 

        commissionerDate = new QLabel(this);
        commissionerDate->setAlignment(Qt::AlignCenter);
        commissionerDate->setFont(*standardFont);

        commissionerPaid = new QLabel(this);
        commissionerPaid->setAlignment(Qt::AlignCenter);
        commissionerPaid->setFont(*standardFont);

        contactInfoLabel = new QLabel(tr("Contact Info:"), this);
        contactInfoLabel->setAlignment(Qt::AlignCenter);
        contactInfoLabel->setFont(*standardFont);

        commissionsLabel = new QLabel(tr("Commissions:"), this);
        commissionsLabel->setAlignment(Qt::AlignCenter);
        commissionsLabel->setFont(*standardFont);

        notesLabel = new QLabel(tr("Notes"), this);
        notesLabel->setAlignment(Qt::AlignCenter);
        notesLabel->setFont(*standardFont);

        notesEdit = new QTextEdit(this);
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

    void CommissionerPanel::createTables(QSqlQueryModel *contactModel, 
        QSqlQueryModel *commissionsModel, 
        QSqlQueryModel *contactTypesModel) {
        contactInfoTable = new FixedRowTable(contactModel, this);
        ComboEditorDelegate *contactDelegate = new ComboEditorDelegate(this);
        contactDelegate->setEditorModel(contactTypesModel);
        contactInfoTable->setBoxDelegate(contactDelegate);
        contactInfoTable->setBoxBottom(true);
        contactInfoTable->setBoxButtonActivated(true);
        contactInfoTable->setBoxButtonWidth(1.25);
        contactInfoTable->setBoxButtonText(tr("Insert"));
        contactInfoTable->setBoxText("Enter Contact");
        contactInfoTable->setColumnCount(2);

        commissionsTable = new QTableView(this);
        commissionsTable->setModel(commissionsModel);

        newCommissionButton = new QPushButton(tr("New Commission"), this);
        connect(newCommissionButton, &QPushButton::clicked, 
            this, &CommissionerPanel::newCommission);
    }

    void CommissionerPanel::updatePanel() {
        commissionerName->setText(
            commissionerModel->record(0).value(0).toString());
        if (commissionerModel->record(0).value(1).toString() 
            == "No Commissions")
            commissionerDate->setText(
                commissionerModel->record(0).value(1).toString());
        else
            commissionerDate->setText(
                "Customer since " + 
                commissionerModel->record(0).value(1).toString());
        if (commissionerModel->record(0).value(2).toString() == "Paid Off") {
            commissionerPaid->setStyleSheet("QLabel { color : green; }");
            commissionerPaid->setText(
                commissionerModel->record(0).value(2).toString());
        } else if (commissionerModel->record(0).value(2).toString() 
            == "No Commissioned Pieces") {
            commissionerPaid->setStyleSheet("QLabel { color : blue; }");
            commissionerPaid->setText(
                commissionerModel->record(0).value(2).toString());
        } else {
            commissionerPaid->setStyleSheet("QLabel { color : red; }");
            QLocale dollarConverter = QLocale();
            commissionerPaid->setText(
                dollarConverter.toCurrencyString(
                    commissionerModel->record(0).value(2).toDouble())
                + " owed");
        }
        notesEdit->setText(commissionerModel->record(0).value(3).toString());

        for (int i = 0; i < contactInfoTable->model()->columnCount(); i++)
            contactInfoTable->horizontalHeader()->setSectionResizeMode(i, 
                QHeaderView::Stretch);

        contactInfoTable->openBoxPersistentEditor(0);

        for (int i = 0; i < commissionsTable->model()->columnCount(); i++)
            commissionsTable->horizontalHeader()->setSectionResizeMode(i, 
                QHeaderView::Stretch);
    }
}