#include "NewCommissionWindow.h"

namespace Commissionator {

    NewCommissionWindow::NewCommissionWindow(QAbstractItemModel *model,
        QWidget *parent) : QDialog(parent) {
        init(model);
    }

    NewCommissionWindow::NewCommissionWindow(QAbstractItemModel *model,
        const int frozenRow, QWidget *parent) : QDialog(parent) {
        init(model, frozenRow);
    }

    void NewCommissionWindow::init(QAbstractItemModel *model, const int frozenRow) {
        mainLayout = new QVBoxLayout(this);
        comLayout = new QGridLayout(this);

        titleFont = new QFont();
        titleFont->setPointSize(12);
        titleFont->setBold(true);

        font = new QFont();
        font->setPointSize(10);

        newComLabel = new QLabel(this);
        newComLabel->setAlignment(Qt::AlignCenter);
        newComLabel->setFont(*titleFont);
        newComLabel->setText("Insert Commission");

        comLabel = new QLabel(this);
        comLabel->setFont(*font);
        comLabel->setText("Commissioner:");

        dueLabel = new QLabel(this);
        dueLabel->setFont(*font);
        dueLabel->setText("Due Date:");

        notesLabel = new QLabel(this);
        notesLabel->setFont(*font);
        notesLabel->setText("Notes:");

        comBox = new QComboBox(this); //just for testing purposes, going to have to eventually subclass combobox to get desired functionality
        comBox->setModel(model);
        comBox->setModelColumn(1);
        //comBox->setEnabled(false);

        calendarEdit = new QDateEdit(this);
        calendarEdit->setCalendarPopup(true);

        notesEdit = new QLineEdit(this);

        submitButton = new QPushButton(this);
        submitButton->setText("Submit Commission");

        mainLayout->addWidget(newComLabel);
        mainLayout->addLayout(comLayout);
        mainLayout->addWidget(submitButton);

        comLayout->addWidget(comLabel, 0, 0);
        comLayout->addWidget(dueLabel, 1, 0);
        comLayout->addWidget(notesLabel, 2, 0);
        comLayout->addWidget(comBox, 0, 1);
        comLayout->addWidget(calendarEdit, 1, 1);
        comLayout->addWidget(notesEdit, 2, 1);

        setLayout(mainLayout);

        exec();
    }
}