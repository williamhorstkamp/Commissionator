#include <QSqlQueryModel>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTableView>
#include <QVBoxLayout>
#include <QSqlRecord>
#include <QTextEdit>
#include "PiecePanel.h"

namespace Commissionator {

    PiecePanel::PiecePanel(QSqlQueryModel *pieceModel, QSqlQueryModel *eventsModel
        /*,QSqlQueryModel *referencesModel*/) {
        this->pieceModel = pieceModel;

        createLabels();
        createButtons();
        createTables(eventsModel);
        createPanel();
    }

    void PiecePanel::createButtons() {
        unlockButton = new QPushButton(this);
        unlockButton->setIcon(QIcon(":/Edit.png"));
        unlockButton->hide();
        unlockButton->setToolTip("Unlock/Lock the editable fields");
        unlockButton->setMinimumSize(24, 24);
        unlockButton->setMaximumSize(24, 24);
        unlockButton->setIconSize(QSize(21.6, 21.6));
        connect(unlockButton, &QPushButton::clicked,
            this, &PiecePanel::toggleEdit);
    }

    void PiecePanel::createLabels() {
        pieceName = new QLabel(this);
        pieceName->setAlignment(Qt::AlignCenter);
        pieceName->setFont(*titleFont);

        pieceNameEdit = new QLineEdit(this);
        connect(pieceNameEdit, &QLineEdit::returnPressed,
            this, &PiecePanel::toggleEdit);
        pieceNameEdit->hide();

        commissionerName = new QLabel(this);
        commissionerName->setAlignment(Qt::AlignCenter);
        commissionerName->setFont(*standardFont);

        startDate = new QLabel(this);
        startDate->setAlignment(Qt::AlignCenter);
        startDate->setFont(*standardFont);

        finishDate = new QLabel(this);
        finishDate->setAlignment(Qt::AlignCenter);
        finishDate->setFont(*standardFont);

        eventsLabel = new QLabel(this);
        eventsLabel->setText("Events:");
        eventsLabel->setAlignment(Qt::AlignCenter);
        eventsLabel->setFont(*standardFont);
        eventsLabel->hide();

        notesLabel = new QLabel(this);
        notesLabel->setText("notes:");
        notesLabel->setAlignment(Qt::AlignCenter);
        notesLabel->setFont(*standardFont);
        notesLabel->hide();

        notesEdit = new QTextEdit(this);
        notesEdit->setReadOnly(true);
        notesEdit->hide();
    }

    void PiecePanel::createPanel() {
        layout = new QVBoxLayout(this);
        titleLayout = new QGridLayout();

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
        layout->addWidget(pieceName);
        layout->addWidget(pieceNameEdit);
        layout->addWidget(commissionerName);
        layout->addWidget(startDate);
        layout->addWidget(finishDate);
        layout->addWidget(eventsLabel);
        layout->addWidget(eventsTable);
        layout->addWidget(notesLabel);
        layout->addWidget(notesEdit);
    }

    void PiecePanel::createTables(QSqlQueryModel *eventsModel) {
        eventsTable = new QTableView();
        eventsTable->setModel(eventsModel);
        eventsTable->setSelectionMode(QAbstractItemView::NoSelection);
        eventsTable->hide();
    }

    void PiecePanel::toggleEdit() {
        if (pieceName->isHidden()) {
            if (pieceNameEdit->text() != pieceName->text() ||
                notesEdit->toPlainText() != 
                pieceModel->record(0).value(5).toString())
                emit edit(pieceModel->record(0).value(0).toInt(),
                pieceNameEdit->text(), notesEdit->toPlainText());
            updatePanel();
        } else {
            pieceName->hide();
            pieceNameEdit->show();
            notesEdit->setReadOnly(false);
            notesEdit->setStyleSheet("QTextEdit { color : black }");
        }
    }

    void PiecePanel::updatePanel() {
        if (pieceModel->record(0).value(0).toInt() != 0) {
            QLocale dollarConverter = QLocale();
            pieceName->setText(
                pieceModel->record(0).value(1).toString());
            commissionerName->setText(
                pieceModel->record(0).value(2).toString());
            startDate->setText(
                "Started on " + pieceModel->record(0).value(3).toString());
            if (pieceModel->record(0).value(4).toString() == NULL) {
                finishDate->setText("Unfinished");
                finishDate->setStyleSheet("QLabel { color : red; }");
            } else {
                finishDate->setText(
                    "Finished on " + pieceModel->record(0).value(4).toString());
                finishDate->setStyleSheet("QLabel { color : green; }");
            }
            notesEdit->setText(
                pieceModel->record(0).value(5).toString());
            notesEdit->setReadOnly(true);
            notesEdit->setStyleSheet("QTextEdit { color : grey }");

            unlockButton->show();
            pieceName->show();
            pieceNameEdit->hide();
            pieceNameEdit->setText(pieceName->text());
            commissionerName->show();
            startDate->show();
            finishDate->show();
            eventsLabel->show();
            eventsTable->show();
            notesLabel->show();
            notesEdit->show();
        } else {
            unlockButton->hide();
            pieceName->hide();
            pieceNameEdit->hide();
            pieceNameEdit->setText("");
            commissionerName->hide();
            startDate->hide();
            finishDate->hide();
            eventsLabel->hide();
            eventsTable->hide();
            notesLabel->hide();
            notesEdit->hide();
            notesEdit->setReadOnly(true);
            notesEdit->setText("");
        }
    }
}