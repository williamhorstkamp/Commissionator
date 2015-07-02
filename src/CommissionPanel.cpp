#include <QLineEdit>
#include <QSqlRecord>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QDateTime>
#include <QTableView>
#include <QHeaderView>
#include <QVBoxLayout>
#include "FixedRowTableDelegate.h"
#include "CommissionPanel.h"

namespace Commissionator {

    CommissionPanel::CommissionPanel(QSqlQueryModel *commissionModel,
        QSqlQueryModel *piecesModel, QSqlQueryModel *paymentsModel,
        QSqlQueryModel *commissionerNamesModel, QWidget *parent) :
        RightPanel(parent) {
        this->commissionModel = commissionModel;
        this->commissionerNamesModel = commissionerNamesModel;

        createLabels();
        createButtons();
        createTables(piecesModel, paymentsModel);
        createPanel();
    }

    void CommissionPanel::createButtons() {
        unlockButton = new QPushButton(this);
        unlockButton->setIcon(QIcon(":/NewFile.png"));
        unlockButton->hide();
        unlockButton->setToolTip("Unlock/Lock the editable fields");
        unlockButton->setMinimumSize(24, 24);
        unlockButton->setMaximumSize(24, 24);
        unlockButton->setIconSize(QSize(21.6, 21.6));
        connect(unlockButton, &QPushButton::clicked,
            this, &CommissionPanel::toggleEdit);

        newPieceButton = new QPushButton(tr("New Piece"), this);
        newPieceButton->hide();
        newPieceButton->setToolTip("Create a new piece for this commission");
        connect(newPieceButton, &QPushButton::clicked,
            this, &CommissionPanel::newPieceSlot);

        newPaymentButton = new QPushButton(tr("New Payment"), this);
        newPaymentButton->hide();
        newPaymentButton->setToolTip("Make a payment on this commission");
        connect(newPaymentButton, &QPushButton::clicked,
            this, &CommissionPanel::newPaymentSlot);

        newRefundButton = new QPushButton(tr("New Refund"), this);
        newRefundButton->hide();
        newRefundButton->setToolTip("Process a refund for this commission");
        connect(newRefundButton, &QPushButton::clicked,
            this, &CommissionPanel::newRefundSlot);
    }

    void CommissionPanel::createLabels() {
        commissionerName = new QLabel(this);
        commissionerName->setAlignment(Qt::AlignCenter);
        commissionerName->setFont(*titleFont);

        commissionerNameCombo = new QComboBox(this);
        commissionerNameCombo->setModel(commissionerNamesModel);
        commissionerNameCombo->setModelColumn(1);
        commissionerNameCombo->hide();

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
        titleLayout->addWidget(commissionerNameCombo, 0, 4);
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
        layout->addWidget(newRefundButton);
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
        piecesTable->hideColumn(0);
        piecesTable->hide();
        connect(piecesDelegate, &FixedRowTableDelegate::buttonClicked,
            this, &CommissionPanel::deletePiece);

        paymentsTable = new QTableView(this);
        paymentsTable->setModel(paymentsModel);
        paymentsTable->setSelectionMode(QAbstractItemView::NoSelection);
        paymentsTable->hide();
    }

    void CommissionPanel::newPaymentSlot() {
        emit newPayment(commissionModel->record(0).value(0));
    }

    void CommissionPanel::newPieceSlot() {
        emit newPiece(commissionModel->record(0).value(0));
    }

    void CommissionPanel::newRefundSlot() {
        emit newRefund(commissionModel->record(0).value(0));
    }

    void CommissionPanel::updatePanel() {            
        if (commissionModel->record(0).value(0).toInt() != 0) {
            commissionerName->setText(
                commissionModel->record(0).value(2).toString());

            createDate->setText(
                "Created on " + commissionModel->record(0).value(3).toString());

            if (commissionModel->record(0).value(4).toString() == NULL)
                paidDate->setText("Unpaid");
            else
                paidDate->setText(
                "Paid on " + commissionModel->record(0).value(4).toString());

            dueDate->setText(
                "Due on " + commissionModel->record(0).value(5).toString());
            if (commissionModel->record(0).value(5).
                toDateTime().toMSecsSinceEpoch() >
                QDateTime::currentMSecsSinceEpoch())
                dueDate->setStyleSheet("QLabel { color : red; }");
            else
                dueDate->setStyleSheet("QLabel { color : black; }");

            QLocale dollarConverter = QLocale();
            if (commissionModel->record(0).value(6).toDouble() <= 0) {
                amountOwed->setStyleSheet("QLabel { color : green; }");
                if (commissionModel->record(0).value(6).toDouble() == 0)
                    amountOwed->setText("Paid Off");
                else
                    amountOwed->setText(
                    "Tipped " + dollarConverter.toCurrencyString(
                    -commissionModel->record(0).value(6).toDouble()));
            } else if (commissionModel->record(0).value(6).toString()
                == "") {
                amountOwed->setStyleSheet("QLabel { color : blue; }");
                amountOwed->setText(
                    "No Commissioned Pieces");
            } else {
                amountOwed->setStyleSheet("QLabel { color : red; }");
                amountOwed->setText(
                    dollarConverter.toCurrencyString(
                    commissionModel->record(0).value(6).toDouble())
                    + " owed");
            }

            commissionNotes->setText(commissionModel->record(0).value(7).toString());

            piecesTable->hideColumn(0);

            for (int i = 0; i < piecesTable->model()->columnCount(); i++)
               piecesTable->horizontalHeader()->setSectionResizeMode(
               i, QHeaderView::Stretch);

            for (int i = 0; i < paymentsTable->model()->columnCount(); i++)
            paymentsTable->horizontalHeader()->setSectionResizeMode(
                i, QHeaderView::Stretch);

            unlockButton->show();
            commissionerName->show();
            commissionerNameCombo->hide();
            commissionerNameCombo->setModelColumn(0);
            commissionerNameCombo->setCurrentIndex(
                commissionerNameCombo->findText(
                    commissionModel->record(0).value(1).toString()));
            commissionerNameCombo->setModelColumn(1);
            createDate->show();
            paidDate->show();
            dueDate->show();
            amountOwed->show();
            piecesLabel->show();
            piecesTable->show();
            newPieceButton->show();
            paymentsLabel->show();
            paymentsTable->show();
            newPaymentButton->show();
            newRefundButton->show();
            notesLabel->show();
            commissionNotes->show();
            commissionNotesEdit->hide();
            commissionNotesEdit->setText(commissionNotes->text());
       } else {
           unlockButton->hide();
           commissionerName->hide();
           commissionerNameCombo->hide();
           commissionerNameCombo->setCurrentIndex(-1);
           createDate->hide();
           paidDate->hide();
           dueDate->hide();
           amountOwed->hide();
           piecesLabel->hide();
           piecesTable->hide();
           newPieceButton->hide();
           paymentsLabel->hide();
           paymentsTable->hide();
           newPaymentButton->hide();
           newRefundButton->hide();
           notesLabel->hide();
           commissionNotes->hide();
           commissionNotesEdit->hide();
           commissionNotesEdit->setText("");
       }
    }

    void CommissionPanel::toggleEdit() {
        if (commissionerName->isHidden()) {
            if (commissionerNameCombo->model()->index(commissionerNameCombo->currentIndex(), 0).data().toString() != commissionerName->text())
                emit editCommissioner(
                    commissionModel->record(0).value(0).toInt(),
                    commissionerNameCombo->model()->index(
                        commissionerNameCombo->currentIndex(), 0).data().toInt());
            if (commissionNotesEdit->text() != commissionNotes->text())
                emit editNotes(commissionModel->record(0).value(0).toInt(),
                commissionNotesEdit->text());
            updatePanel();
        } else {
            commissionerName->hide();
            commissionerNameCombo->show();
            commissionNotes->hide();
            commissionNotesEdit->show();
        }
    }
}