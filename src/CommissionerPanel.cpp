#include <QLabel>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QHeaderView>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "FixedRowTable.h"
#include "ComboEditorDelegate.h"
#include "CommissionerPanel.h"

namespace Commissionator {

    CommissionerPanel::CommissionerPanel(QSqlQueryModel *commissionerModel, 
        QSqlQueryModel *contactModel, QSqlQueryModel *commissionsModel,
        QSqlQueryModel *contactTypesModel, QWidget *parent) :
        RightPanel(parent) {
        this->commissionerModel = commissionerModel;
        this->contactTypesModel = contactTypesModel;

        createLabels();
        createButtons();
        createTables(contactModel, commissionsModel, contactTypesModel);
        createPanel();
    }

    void CommissionerPanel::createButtons() {
        unlockButton = new QPushButton(this);
        unlockButton->setIcon(QIcon(":/NewFile.png"));
        unlockButton->hide();
        unlockButton->setToolTip("Unlock/Lock the editable fields");
        unlockButton->setMinimumSize(24, 24);
        unlockButton->setMaximumSize(24, 24);
        unlockButton->setIconSize(QSize(21.6, 21.6));
        connect(unlockButton, &QPushButton::clicked,
            this, &CommissionerPanel::toggleEdit);

        newCommissionButton = new QPushButton(tr("New Commission"), this);
        newCommissionButton->hide();
        newCommissionButton->setToolTip("Create a new Commission");
        connect(newCommissionButton, &QPushButton::clicked,
            this, &CommissionerPanel::newCommissionSlot);
    }

    void CommissionerPanel::createLabels() {
        commissionerName = new QLabel(this);
        commissionerName->setAlignment(Qt::AlignCenter);
        commissionerName->setFont(*titleFont); 

        commissionerNameEdit = new QLineEdit(this);
        connect(commissionerNameEdit, &QLineEdit::returnPressed,
            this, &CommissionerPanel::toggleEdit);
        commissionerNameEdit->hide();

        commissionerDate = new QLabel(this);
        commissionerDate->setAlignment(Qt::AlignCenter);
        commissionerDate->setFont(*standardFont);

        commissionerPaid = new QLabel(this);
        commissionerPaid->setAlignment(Qt::AlignCenter);
        commissionerPaid->setFont(*standardFont);

        contactInfoLabel = new QLabel(tr("Contact Info:"), this);
        contactInfoLabel->setAlignment(Qt::AlignCenter);
        contactInfoLabel->setFont(*standardFont);
        contactInfoLabel->hide();

        commissionsLabel = new QLabel(tr("Commissions:"), this);
        commissionsLabel->setAlignment(Qt::AlignCenter);
        commissionsLabel->setFont(*standardFont);
        commissionsLabel->hide();

        notesLabel = new QLabel(tr("Notes:"), this);
        notesLabel->setAlignment(Qt::AlignCenter);
        notesLabel->setFont(*standardFont);
        notesLabel->hide();

        commissionerNotes = new QLabel(this);
        commissionerNotes->setAlignment(Qt::AlignCenter);
        commissionerNotes->setFont(*standardFont);
        commissionerNotes->setWordWrap(true);

        commissionerNotesEdit = new QLineEdit(this);
        connect(commissionerNotesEdit, &QLineEdit::returnPressed,
            this, &CommissionerPanel::toggleEdit);
        commissionerNotesEdit->hide();
    }

    void CommissionerPanel::createPanel() {
        layout = new QVBoxLayout(this);
        titleLayout = new QGridLayout();

        titleLayout->addWidget(commissionerName, 0, 4);
        titleLayout->addWidget(commissionerNameEdit, 0, 4);
        titleLayout->addWidget(unlockButton, 0, 8);
        titleLayout->setColumnStretch(0, 1);
        titleLayout->setColumnStretch(1, 1);
        titleLayout->setColumnStretch(2, 1);
        titleLayout->setColumnStretch(3, 1); 
        titleLayout->setColumnStretch(4, 1);
        titleLayout->setColumnStretch(5, 1);
        titleLayout->setColumnStretch(6, 1);
        titleLayout->setColumnStretch(7, 1);
        titleLayout->setColumnStretch(8, 1);

        layout->addLayout(titleLayout);
        layout->addWidget(commissionerDate);
        layout->addWidget(commissionerPaid);
        layout->addWidget(contactInfoLabel);
        layout->addWidget(contactInfoTable);
        layout->addWidget(commissionsLabel);
        layout->addWidget(commissionsTable);
        layout->addWidget(newCommissionButton);
        layout->addWidget(notesLabel);
        layout->addWidget(commissionerNotes);
        layout->addWidget(commissionerNotesEdit);
    }

    void CommissionerPanel::createTables(QSqlQueryModel *contactModel, 
        QSqlQueryModel *commissionsModel, 
        QSqlQueryModel *contactTypesModel) {
        contactInfoTable = new FixedRowTable(contactModel, this);
        contactDelegate = new ComboEditorDelegate(this);
        contactDelegate->setEditorModel(contactTypesModel);
        contactDelegate->setDisplayColumn(1);
        contactDelegate->setColumn(1);
        contactInfoTable->setBoxDelegate(contactDelegate);
        contactInfoTable->setBoxBottom(true);
        contactInfoTable->setBoxButtonActivated(true);
        contactInfoTable->setBoxButtonWidth(1.25);
        contactInfoTable->setBoxButtonText(tr("Insert"));
        contactInfoTable->setBoxText("Enter Contact");
        contactInfoTable->setColumnCount(3);
        contactInfoTable->setTableButtonActivated(true);
        contactInfoTable->setTableButtonIcon(":/Delete.png");
        contactInfoTable->setTableButtonSize(24);
        contactInfoTable->setSelectionMode(QAbstractItemView::NoSelection);
        contactInfoTable->hide();
        connect(contactInfoTable, &FixedRowTable::boxQuery,
            this, &CommissionerPanel::insertContactSlot);
        connect(contactInfoTable, &FixedRowTable::tableButtonClicked,
            this, &CommissionerPanel::deleteContact);

        commissionsTable = new QTableView(this);
        commissionsTable->setModel(commissionsModel);
        commissionsTable->setSelectionMode(QAbstractItemView::NoSelection);
        commissionsTable->hide();
    }

    void CommissionerPanel::insertContactSlot(const QList<QVariant> query) {
        if (query.length() == 3)    //contact id, contact type, entry
            emit insertContact(commissionerModel->record(0).value(0).toInt(),
            contactTypesModel->index(query[1].toInt(), 0).data().toInt(),
            query[2].toString());
    }

    void CommissionerPanel::newCommissionSlot() {
        emit newCommission(commissionerModel->record(0).value(0));
    }

    void CommissionerPanel::updatePanel() {
        if (commissionerModel->record(0).value(0).toInt() != 0) {
            QLocale dollarConverter = QLocale();
            commissionerName->setText(
                commissionerModel->record(0).value(1).toString());
            if (commissionerModel->record(0).value(2).toString()
                == "No Commissions")
                commissionerDate->setText(
                commissionerModel->record(0).value(2).toString());
            else
                commissionerDate->setText(
                "Customer since " +
                commissionerModel->record(0).value(2).toString());
            if (commissionerModel->record(0).value(3).toDouble() <= 0) {
                commissionerPaid->setStyleSheet("QLabel { color : green; }");
                if (commissionerModel->record(0).value(3).toDouble() == 0)
                    commissionerPaid->setText("Paid Off");
                else
                    commissionerPaid->setText(
                    "Tipped " + dollarConverter.toCurrencyString(
                    -commissionerModel->record(0).value(3).toDouble()));
            } else if (commissionerModel->record(0).value(3).toString()
                == "") {
                commissionerPaid->setStyleSheet("QLabel { color : blue; }");
                commissionerPaid->setText(
                    "No Commissioned Pieces");
            } else {
                commissionerPaid->setStyleSheet("QLabel { color : red; }");
                commissionerPaid->setText(
                    dollarConverter.toCurrencyString(
                    commissionerModel->record(0).value(3).toDouble())
                    + " owed");
            }
            commissionerNotes->setText(commissionerModel->record(0).value(4).toString());

            for (int i = 0; i < contactInfoTable->model()->columnCount(); i++)
                contactInfoTable->horizontalHeader()->setSectionResizeMode(i,
                QHeaderView::Stretch);

            contactInfoTable->openBoxPersistentEditor(1);

            for (int i = 0; i < commissionsTable->model()->columnCount(); i++)
                commissionsTable->horizontalHeader()->setSectionResizeMode(i,
                QHeaderView::Stretch);

            contactInfoTable->setColumnHidden(0, true);

            unlockButton->show();
            commissionerName->show();
            commissionerNameEdit->hide();
            commissionerNameEdit->setText(commissionerName->text());
            commissionerDate->show();
            commissionerPaid->show();
            contactInfoLabel->show();
            contactInfoTable->show();
            commissionsLabel->show();
            commissionsTable->show();
            newCommissionButton->show();
            notesLabel->show();
            commissionerNotes->show();
            commissionerNotesEdit->hide();
            commissionerNotesEdit->setText(commissionerNotes->text());
        } else {
            unlockButton->hide();
            commissionerName->hide();
            commissionerNameEdit->hide();
            commissionerNameEdit->setText(commissionerName->text());
            commissionerDate->hide();
            commissionerPaid->hide();
            contactInfoLabel->hide();
            contactInfoTable->hide();
            commissionsLabel->hide();
            commissionsTable->hide();
            newCommissionButton->hide();
            notesLabel->hide();
            commissionerNotes->hide();
            commissionerNotesEdit->hide();
            commissionerNotesEdit->setText("");
        }
    }

    void CommissionerPanel::toggleEdit() {
        if (commissionerName->isHidden()) { 
            if (commissionerNameEdit->text() != commissionerName->text())
                emit editName(commissionerModel->record(0).value(0).toInt(),
                    commissionerNameEdit->text());
            if (commissionerNotesEdit->text() != commissionerNotes->text())
                emit editNotes(commissionerModel->record(0).value(0).toInt(),
                commissionerNotesEdit->text());
            updatePanel();
        } else {
            commissionerName->hide();
            commissionerNameEdit->show();
            commissionerNotes->hide();
            commissionerNotesEdit->show();
        }
    }
}