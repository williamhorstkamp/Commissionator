#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QHeaderView>
#include "FixedRowTable.h"
#include "OptionsDialog.h"

namespace Commissionator {
    OptionsDialog::OptionsDialog(QAbstractItemModel *contactTypesModel,
        QAbstractItemModel *paymentTypesModel,
        QWidget *parent) : QDialog(parent) {
        mainLayout = new QVBoxLayout(this);
        optionLayout = new QGridLayout();

        titleFont = new QFont();
        titleFont->setPointSize(12);
        titleFont->setBold(true);

        font = new QFont();
        font->setPointSize(10);

        optionsLabel = new QLabel(this);
        optionsLabel->setAlignment(Qt::AlignCenter);
        optionsLabel->setFont(*titleFont);
        optionsLabel->setText("Store Options");

        contactLabel = new QLabel(this);
        contactLabel->setFont(*font);
        contactLabel->setText("Contact Types");

        contactTypeTable = new FixedRowTable(contactTypesModel);
        contactTypeTable->setTableButtonActivated(true);
        contactTypeTable->setTableButtonIcon(":/Delete.png");
        contactTypeTable->setTableButtonSize(24);
        contactTypeTable->setBoxText("Insert");
        contactTypeTable->setSelectionMode(QAbstractItemView::NoSelection);
        contactTypeTable->setColumnHidden(0, true);
        contactTypeTable->horizontalHeader()->setSectionResizeMode(0,
            QHeaderView::Stretch);
        connect(contactTypeTable, &FixedRowTable::tableButtonClicked,
            this, &OptionsDialog::deleteContactType);
        connect(contactTypeTable, &FixedRowTable::boxQuery,
            this, &OptionsDialog::insertContactTypeSlot);

        paymentLabel = new QLabel(this);
        paymentLabel->setFont(*font);
        paymentLabel->setText("Payment Types");

        paymentTypeTable = new FixedRowTable(paymentTypesModel);
        paymentTypeTable->setTableButtonActivated(true);
        paymentTypeTable->setTableButtonIcon(":/Delete.png");
        paymentTypeTable->setTableButtonSize(24);
        paymentTypeTable->setBoxText("Insert");
        paymentTypeTable->setSelectionMode(QAbstractItemView::NoSelection);
        paymentTypeTable->setColumnHidden(0, true);
        paymentTypeTable->horizontalHeader()->setSectionResizeMode(0,
            QHeaderView::Stretch);
        connect(paymentTypeTable, &FixedRowTable::tableButtonClicked,
            this, &OptionsDialog::deletePaymentType);
        connect(paymentTypeTable, &FixedRowTable::boxQuery,
            this, &OptionsDialog::insertPaymentTypeSlot);

        mainLayout->addWidget(optionsLabel);
        mainLayout->addLayout(optionLayout);

        optionLayout->addWidget(contactLabel, 0, 0);
        optionLayout->addWidget(contactTypeTable, 1, 0);
        optionLayout->addWidget(paymentLabel, 1, 0);
        optionLayout->addWidget(paymentTypeTable, 1, 1);

    }

    void OptionsDialog::insertContactTypeSlot(const QList<QVariant> query) {
        emit insertContactType(query[0].toString());
    }

    void OptionsDialog::insertPaymentTypeSlot(const QList<QVariant> query) {
        emit insertPaymentType(query[0].toString());
    }
}