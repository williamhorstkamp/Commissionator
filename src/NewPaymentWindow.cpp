#include "NewPaymentWindow.h"

#include <QSqlQueryModel>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QPushButton>

namespace Commissionator {

    NewPaymentWindow::NewPaymentWindow(QSqlQueryModel *commissionModel,
        QSqlQueryModel *paymentModel, QWidget *parent) :
        BaseNewWindow(parent) {

        mainLayout = new QVBoxLayout(this);
        payLayout = new QGridLayout();

        newPayLabel = new QLabel(this);
        newPayLabel->setAlignment(Qt::AlignCenter);
        newPayLabel->setFont(*titleFont);
        newPayLabel->setText("Insert Payment");

        comLabel = new QLabel(this);
        comLabel->setFont(*font);
        comLabel->setText("Commission:");

        typeLabel = new QLabel(this);
        typeLabel->setFont(*font);
        typeLabel->setText("Payment Type:");

        amountOwedLabel = new QLabel(this);
        amountOwedLabel->setFont(*font);
        amountOwedLabel->setText("Amount Owed:");

        amountOwed = new QLabel(this);
        amountOwed->setFont(*font);
        amountOwed->setText("No Commission Selected");

        amountLabel = new QLabel(this);
        amountLabel->setFont(*font);
        amountLabel->setText("Payment Amount:");

        notesLabel = new QLabel(this);
        notesLabel->setFont(*font);
        notesLabel->setText("Payment Notes:");

        comBox = new QComboBox(this);
        comBox->setModel(commissionModel);
        comBox->setModelColumn(1);
        comBox->setCurrentIndex(-1);
        connect(comBox, static_cast<void(QComboBox::*)(int)>
            (&QComboBox::currentIndexChanged),
            this, &NewPaymentWindow::setSubmitEnabled);
        connect(comBox, static_cast<void(QComboBox::*)(int)>
            (&QComboBox::currentIndexChanged),
            this, &NewPaymentWindow::updateAmount);

        typeBox = new QComboBox(this);
        typeBox->setModel(paymentModel);
        typeBox->setModelColumn(1);
        typeBox->setCurrentIndex(-1);
        connect(typeBox, static_cast<void(QComboBox::*)(int)>
            (&QComboBox::currentIndexChanged),
            this, &NewPaymentWindow::setSubmitEnabled);

        amountEdit = new QDoubleSpinBox(this);
        amountEdit->setDecimals(2);
        amountEdit->setMinimum(0);
        amountEdit->setMaximum(999999);
        connect(amountEdit, static_cast<void(QDoubleSpinBox::*)(double)>
            (&QDoubleSpinBox::valueChanged),
            this, &NewPaymentWindow::setSubmitEnabled);

        notesEdit = new QLineEdit(this);

        submitButton = new QPushButton(this);
        submitButton->setText("Submit Payment");
        submitButton->setEnabled(false);
        connect(submitButton, &QPushButton::clicked,
            this, &NewPaymentWindow::newItemSlot);

        mainLayout->addWidget(newPayLabel);
        mainLayout->addLayout(payLayout);
        mainLayout->addWidget(submitButton);

        payLayout->addWidget(comLabel, 0, 0);
        payLayout->addWidget(typeLabel, 1, 0);
        payLayout->addWidget(amountOwedLabel, 2, 0);
        payLayout->addWidget(amountLabel, 3, 0);
        payLayout->addWidget(notesLabel, 4, 0);
        payLayout->addWidget(comBox, 0, 1);
        payLayout->addWidget(typeBox, 1, 1);
        payLayout->addWidget(amountOwed, 2, 1);
        payLayout->addWidget(amountEdit, 3, 1);
        payLayout->addWidget(notesEdit, 4, 1);
    }

    NewPaymentWindow::~NewPaymentWindow() {
        delete payLayout;
    }

    void NewPaymentWindow::clear() {
        comBox->setEnabled(true);
        comBox->setCurrentIndex(-1);
        typeBox->setCurrentIndex(-1);
        amountOwed->setText("No Commission Selected");
        amountOwed->setStyleSheet("QLabel { color : black; }");
        amountEdit->setValue(0);
        notesEdit->setText("");
        submitButton->setEnabled(false);
    }

    void NewPaymentWindow::newItemSlot() {
        emit newPayment(
            comBox->model()->index(comBox->currentIndex(), 0).data().toInt(),
            typeBox->model()->index(typeBox->currentIndex(), 0).data().toInt(),
            amountEdit->value(),
            notesEdit->text());
        BaseNewWindow::newItemSlot();
    }

    void NewPaymentWindow::setCommission(const QVariant &commission) {
        comBox->setModelColumn(0);
        int index = comBox->findText(commission.toString());
        if (index >= 0) {
            comBox->setCurrentIndex(index);
            comBox->setEnabled(false);
        }
        comBox->setModelColumn(1);
    }

    void NewPaymentWindow::setSubmitEnabled() {
        if (comBox->currentIndex() > -1 && typeBox->currentIndex() > -1 &&
            amountEdit->value() > 0)
            submitButton->setEnabled(true);
        else
            submitButton->setEnabled(false);
    }

    void NewPaymentWindow::updateAmount() {
        QLocale dollarConverter = QLocale();
        double dollars = comBox->model()->index(
            comBox->currentIndex(), 2).data().toDouble();
        if (dollars > 0) {
            amountOwed->setStyleSheet("QLabel { color : red; }");
            amountOwed->setText(dollarConverter.toCurrencyString(dollars));
        } else {
            amountOwed->setStyleSheet("QLabel { color : green; }");
            amountOwed->setText("Paid Off");
        }      
    }
}