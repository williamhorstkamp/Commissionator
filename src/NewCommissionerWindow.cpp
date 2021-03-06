#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include "NewCommissionerWindow.h"

namespace Commissionator {
    
    NewCommissionerWindow::NewCommissionerWindow(QWidget *parent) :
        BaseNewWindow(parent) {
        mainLayout = new QVBoxLayout(this);
        comLayout = new QGridLayout();

        newComLabel = new QLabel(this);
        newComLabel->setAlignment(Qt::AlignCenter);
        newComLabel->setFont(*titleFont);
        newComLabel->setText("Insert Commissioner");

        nameLabel = new QLabel(this);
        nameLabel->setFont(*font);
        nameLabel->setText("Name:");

        notesLabel = new QLabel(this);
        notesLabel->setFont(*font);
        notesLabel->setText("Notes:");

        nameEdit = new QLineEdit(this);
        connect(nameEdit, &QLineEdit::textChanged,
            this, &NewCommissionerWindow::setSubmitEnabled);

        notesEdit = new QLineEdit(this);

        submitButton = new QPushButton(this);
        submitButton->setText("Submit Commissioner");
        submitButton->setEnabled(false);
        connect(submitButton, &QPushButton::clicked,
            this, &NewCommissionerWindow::newItemSlot);

        mainLayout->addWidget(newComLabel);
        mainLayout->addLayout(comLayout);
        mainLayout->addWidget(submitButton);

        comLayout->addWidget(nameLabel, 0, 0);
        comLayout->addWidget(notesLabel, 1, 0);
        comLayout->addWidget(nameEdit, 0, 1);
        comLayout->addWidget(notesEdit, 1, 1);
    }

    NewCommissionerWindow::~NewCommissionerWindow() {
        delete comLayout;
    }

    void NewCommissionerWindow::clear() {
        nameEdit->clear();
        notesEdit->clear();
        submitButton->setEnabled(false);
    }

    void NewCommissionerWindow::newItemSlot() {
        emit newCommissioner(nameEdit->text(), notesEdit->text());
        BaseNewWindow::newItemSlot();
    }

    void NewCommissionerWindow::setSubmitEnabled() {
        if (nameEdit->text() != "")
            submitButton->setEnabled(true);
        else
            submitButton->setEnabled(false);
    }
}