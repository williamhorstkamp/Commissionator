#include <QSqlQueryModel>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTableView>
#include <QVBoxLayout>
#include <QSqlRecord>
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

        description = new QLabel(this);
        description->setAlignment(Qt::AlignCenter);
        description->setFont(*standardFont);


        descriptionEdit = new QLineEdit(this);
        connect(descriptionEdit, &QLineEdit::returnPressed,
            this, &PiecePanel::toggleEdit);
        descriptionEdit->hide();
    }

    void PiecePanel::createPanel() {
        layout = new QVBoxLayout(this);
        titleLayout = new QGridLayout();

        titleLayout->addWidget(pieceName, 0, 4);
        titleLayout->addWidget(pieceNameEdit, 0, 4);
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
        layout->addWidget(commissionerName);
        layout->addWidget(startDate);
        layout->addWidget(finishDate);
        layout->addWidget(eventsTable);
        layout->addWidget(description);
        layout->addWidget(descriptionEdit);
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
                descriptionEdit->text() != description->text())
                emit edit(pieceModel->record(0).value(0).toInt(),
                pieceNameEdit->text(), descriptionEdit->text());
            updatePanel();
        } else {
            pieceName->hide();
            pieceNameEdit->show();
            description->hide();
            descriptionEdit->show();
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
            description->setText(
                pieceModel->record(0).value(5).toString());

            unlockButton->show();
            pieceName->show();
            pieceNameEdit->hide();
            pieceNameEdit->setText(pieceName->text());
            commissionerName->show();
            startDate->show();
            finishDate->show();
            eventsTable->show();
            description->show();
            descriptionEdit->hide();
            descriptionEdit->setText(description->text());
        } else {
            unlockButton->hide();
            pieceName->hide();
            pieceNameEdit->hide();
            pieceNameEdit->setText("");
            commissionerName->hide();
            startDate->hide();
            finishDate->hide();
            eventsTable->hide();
            description->hide();
            descriptionEdit->hide();
            descriptionEdit->setText("");
        }
    }
}