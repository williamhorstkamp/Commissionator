#include <QLineEdit>
#include "CommissionPanel.h"

namespace Commissionator {

    CommissionPanel::CommissionPanel(QSqlQueryModel *commissionModel,
        QSqlQueryModel *piecesModel, QSqlQueryModel *paymentsModel,
        QSqlQueryModel *commissionerNamesModel, QWidget *parent) :
        QWidget(parent) {
        this->commissionModel = commissionModel;
        this->commissionerNamesModel = commissionerNamesModel;

        createFonts();
        createLabels();
        createButtons();
        createTables(piecesModel, paymentsModel);
        createPanel();
    }

    CommissionPanel::~CommissionPanel() {
        delete titleFont;
        delete standardFont;
        delete titleLayout;
    }

    void CommissionPanel::createButtons() {
        unlockButton = new QPushButton(this);
        unlockButton->setIcon(QIcon(":/NewFile.png"));
        unlockButton->hide();
        connect(unlockButton, &QPushButton::clicked,
            this, &CommissionPanel::toggleEdit);

        newPieceButton = new QPushButton(tr("New Payment"), this);
        newPieceButton->hide();
       // connect(newPieceButton, &QPushButton::clicked,
       //     this, &CommissionPanel::newPieceSlot);

        newPaymentButton = new QPushButton(tr("New Payment"), this);
        newPaymentButton->hide();
      //  connect(newPaymentButton, &QPushButton::clicked,
       //     this, &CommissionPanel::newPaymentSlot);
    }

    void CommissionPanel::createFonts() {
        titleFont = new QFont();
        titleFont->setPointSize(12);
        titleFont->setBold(true);

        standardFont = new QFont();
        standardFont->setPointSize(10);
    }

    void CommissionPanel::createLabels() {
        commissionerName = new QLabel(this);
        commissionerName->setAlignment(Qt::AlignCenter);
        commissionerName->setFont(*titleFont);

        commissionerNamesCombo = new QComboBox(this);
        commissionerNamesCombo->setModel(commissionerNamesModel);
        commissionerNamesCombo->hide();

        createDate = new QLabel(this);
        createDate->setAlignment(Qt::AlignCenter);
        createDate->setFont(*standardFont);

        paidDate = new QLabel(this);
        paidDate->setAlignment(Qt::AlignCenter);
        paidDate->setFont(*standardFont);

        dueDate = new QLabel(this);
        dueDate->setAlignment(Qt::AlignCenter);
        dueDate->setFont(*standardFont);

        dueEdit = new QLineEdit(this);
        connect(dueEdit, &QLineEdit::returnPressed,
            this, &CommissionPanel::toggleEdit);
        dueEdit->hide();

        amountOwed = new QLabel(this);
        amountOwed->setAlignment(Qt::AlignCenter);
        amountOwed->setFont(*standardFont);

        piecesLabel = new QLabel(tr("Pieces:"), this);
        piecesLabel->setAlignment(Qt::AlignCenter);
        piecesLabel->setFont(*standardFont);
        piecesLabel->hide();

        paymentsLabel = new QLabel(tr("Payments:"), this);
        paymentsLabel->setAlignment(Qt::AlignCenter);
        paymentsLabel->setFont(*standardFont);
        paymentsLabel->hide();

        notesLabel = new QLabel(tr("Notes:"), this);
        notesLabel->setAlignment(Qt::AlignCenter);
        notesLabel->setFont(*standardFont);
        notesLabel->hide();

        commissionNotes = new QLabel(this);
        commissionNotes->setAlignment(Qt::AlignCenter);
        commissionNotes->setFont(*standardFont);
        commissionNotes->setWordWrap(true);

        commissionNotesEdit = new QLineEdit(this);
        connect(commissionNotesEdit, &QLineEdit::returnPressed,
            this, &CommissionPanel::toggleEdit);
        commissionNotesEdit->hide();
    }

    void CommissionPanel::createPanel() {
        layout = new QVBoxLayout(this);
        titleLayout = new QGridLayout();

        titleLayout->addWidget(commissionerName, 0, 4);
        titleLayout->addWidget(commissionerNamesCombo, 0, 4);
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
        layout->addWidget(createDate);
        layout->addWidget(paidDate);
        layout->addWidget(dueDate);
        layout->addWidget(amountOwed);
        layout->addWidget(piecesLabel);
        layout->addWidget(piecesTable);
        layout->addWidget(newPieceButton);
        layout->addWidget(paymentsLabel);
        layout->addWidget(paymentsTable);
        layout->addWidget(newPaymentButton);
        layout->addWidget(notesLabel);
        layout->addWidget(commissionNotes);
        layout->addWidget(commissionNotesEdit);
    }

    void CommissionPanel::createTables(QSqlQueryModel *piecesModel,
        QSqlQueryModel *paymentsModel) {
        piecesTable = new QTableView(this);
        piecesTable->setModel(piecesModel);
        piecesDelegate = new FixedRowTableDelegate(this);
        piecesDelegate->setIcon(":/Delete.png");
        piecesDelegate->setIconSize(24);
        piecesTable->setItemDelegate(piecesDelegate);
        piecesTable->setSelectionMode(QAbstractItemView::NoSelection);
        piecesTable->hide();
        connect(piecesDelegate, &FixedRowTableDelegate::buttonClicked,
            this, &CommissionPanel::deletePiece);

        paymentsTable = new QTableView(this);
        paymentsTable->setModel(paymentsModel);
        paymentsTable->setSelectionMode(QAbstractItemView::NoSelection);
        paymentsTable->hide();
    }

    void CommissionPanel::updatePanel() {
    }

    void CommissionPanel::toggleEdit() {
    }
}