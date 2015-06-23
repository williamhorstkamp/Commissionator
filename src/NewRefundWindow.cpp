#include "NewRefundWindow.h"

#include <QSqlQueryModel>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPushButton>

namespace Commissionator {

    NewRefundWindow::NewRefundWindow(QSqlQueryModel *commissionModel, 
        QWidget *parent) : BaseNewWindow(parent) {
        this->commissionModel = commissionModel;

        mainLayout = new QVBoxLayout(this);
        refundLayout = new QGridLayout();

        newRefundLabel = new QLabel(this);
        newRefundLabel->setAlignment(Qt::AlignCenter);
        newRefundLabel->setFont(*titleFont);
        newRefundLabel->setText("Insert Payment");

        amountPaidLabel = new QLabel(this);
        amountPaidLabel->setFont(*font);
        amountPaidLabel->setText("Amount Paid:");

        amountLabel = new QLabel(this);
        amountLabel->setFont(*font);
        amountLabel->setText("Payment Amount:");

        notesLabel = new QLabel(this);
        notesLabel->setFont(*font);
        notesLabel->setText("Payment Notes:");

        amountPaid = new QLabel(this);
        amountPaid->setFont(*font);
        amountPaid->setText("No Commission Selected");

        amountEdit = new QDoubleSpinBox(this);
        amountEdit->setDecimals(2);
        amountEdit->setMinimum(0);
        amountEdit->setMaximum(999999);
        connect(amountEdit, static_cast<void(QDoubleSpinBox::*)(double)>
            (&QDoubleSpinBox::valueChanged),
            this, &NewRefundWindow::setSubmitEnabled);

        notesEdit = new QLineEdit(this);

        submitButton = new QPushButton(this);
        submitButton->setText("Submit Payment");
        submitButton->setEnabled(false);
        connect(submitButton, &QPushButton::clicked,
            this, &NewRefundWindow::newItemSlot);

        commissionId = 0;

        mainLayout->addWidget(newRefundLabel);
        mainLayout->addLayout(refundLayout);
        mainLayout->addWidget(submitButton);

        refundLayout->addWidget(amountPaidLabel, 0, 0);
        refundLayout->addWidget(amountLabel, 1, 0);
        refundLayout->addWidget(notesLabel, 2, 0);
        refundLayout->addWidget(amountPaid, 0, 1);
        refundLayout->addWidget(amountEdit, 1, 1);
        refundLayout->addWidget(notesEdit, 2, 1);
    }

    NewRefundWindow::~NewRefundWindow() {
        delete refundLayout;
    }

    void NewRefundWindow::clear() {
        amountPaid->setText("No Commission Selected");
        amountPaid->setStyleSheet("QLabel { color : black; }");
        amountEdit->setValue(0);
        notesEdit->setText("");
        submitButton->setEnabled(false);
    }

    void NewRefundWindow::newItemSlot() {
        emit newRefund(
            commissionId,
            amountEdit->value(),
            notesEdit->text());
        BaseNewWindow::newItemSlot();
    }

    void NewRefundWindow::setCommission(const QVariant &commission) {
        commissionId = commission.toInt();
        updateAmount();
    }

    void NewRefundWindow::setSubmitEnabled() {
        if (commissionId && amountEdit->value() > 0)
            submitButton->setEnabled(true);
        else
            submitButton->setEnabled(false);
    }

    void NewRefundWindow::updateAmount() {
        QLocale dollarConverter = QLocale();
        double paid = commissionModel->index(
            commissionModel->match(commissionModel->index(0, 0),
            Qt::DisplayRole,
            commissionId).first().row(), 3).data().toDouble();
        if (paid > 0) {
            amountPaid->setStyleSheet("QLabel { color : red; }");
            amountPaid->setText(dollarConverter.toCurrencyString(paid));
        } else {
            amountPaid->setStyleSheet("QLabel { color : green; }");
            amountPaid->setText("Paid Off");
        }
        amountEdit->setMaximum(paid);
    }
}