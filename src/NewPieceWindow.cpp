#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include "NewPieceWindow.h"

namespace Commissionator {

    NewPieceWindow::NewPieceWindow(QAbstractItemModel *productsModel, 
        QWidget *parent) : BaseNewWindow(parent) {
        mainLayout = new QVBoxLayout(this);
        pieLayout = new QGridLayout();

        newPieLabel = new QLabel(this);
        newPieLabel->setAlignment(Qt::AlignCenter);
        newPieLabel->setFont(*titleFont);
        newPieLabel->setText("Insert Piece");

        pieNameLabel = new QLabel(this);
        pieNameLabel->setFont(*font);
        pieNameLabel->setText("Piece Name:");

        pieNotesLabel = new QLabel(this);
        pieNotesLabel->setFont(*font);
        pieNotesLabel->setText("Piece Notes:");

        proNameLabel = new QLabel(this);
        proNameLabel->setFont(*font);
        proNameLabel->setText("Product Name:");

        pieNameEdit = new QLineEdit(this);

        pieNotesEdit = new QLineEdit(this);

        proBox = new QComboBox(this);
        proBox->setModel(productsModel);
        proBox->setModelColumn(1);
        proBox->setCurrentIndex(-1);

        priceCheck = new QCheckBox(this);
        priceCheck->setText("Price Override");
        connect(priceCheck, &QCheckBox::stateChanged,
            this, &NewPieceWindow::setPriceOverride);
 
        priceEdit = new QDoubleSpinBox(this);
        priceEdit->setDecimals(2);
        priceEdit->setMinimum(0);
        priceEdit->setEnabled(false);
        priceEdit->setMaximum(999999);

        submitButton = new QPushButton(this);
        submitButton->setText("Submit Piece");
        connect(submitButton, &QPushButton::clicked,
            this, &NewPieceWindow::newItemSlot);

        mainLayout->addWidget(newPieLabel);
        mainLayout->addLayout(pieLayout);
        mainLayout->addWidget(submitButton);

        pieLayout->addWidget(pieNameLabel, 0, 0);
        pieLayout->addWidget(pieNotesLabel, 1, 0);
        pieLayout->addWidget(proNameLabel, 2, 0);
        pieLayout->addWidget(priceCheck, 3, 0);
        pieLayout->addWidget(pieNameEdit, 0, 1);
        pieLayout->addWidget(pieNotesEdit, 1, 1);
        pieLayout->addWidget(proBox, 2, 1);
        pieLayout->addWidget(priceEdit, 3, 1);
    }

    NewPieceWindow::~NewPieceWindow() {
        delete pieLayout;
    }

    void NewPieceWindow::clear() {
        pieNameEdit->setText("");
        pieNotesEdit->setText("");
        proBox->setCurrentIndex(-1);
        priceCheck->setChecked(false);
        priceEdit->setEnabled(false);
        priceEdit->setValue(0);
    }

    void NewPieceWindow::newItemSlot() {
        if (pieNameEdit->text() != "" && proBox->currentIndex() > -1) {
            double price = -1;
            if (priceCheck->isChecked())
                price = priceEdit->value();
            emit newPiece(pieNameEdit->text(),
                pieNotesEdit->text(),
                proBox->model()->index(proBox->currentIndex(), 0).data().toInt(),
                proBox->currentText(),
                price);
        }
        BaseNewWindow::newItemSlot();
    }

    void NewPieceWindow::setPriceOverride() {
        priceEdit->setEnabled(priceCheck->isChecked());
        priceEdit->setValue(0);
    }
}