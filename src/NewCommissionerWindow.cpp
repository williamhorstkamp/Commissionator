#include <QPushButton>
#include "NewCommissionerWindow.h"

namespace Commissionator {
    
    NewCommissionerWindow::NewCommissionerWindow(QWidget *parent) : QDialog(parent) {
        init();
    }

    NewCommissionerWindow::~NewCommissionerWindow() {
        delete titleFont;
        delete font;
    }

    void NewCommissionerWindow::init() {
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
        newComLabel->setText("Insert Commissioner");

        nameLabel = new QLabel(this);
        nameLabel->setFont(*font);
        nameLabel->setText("Name:");

        notesLabel = new QLabel(this);
        notesLabel->setFont(*font);
        notesLabel->setText("Notes:");

        nameEdit = new QLineEdit(this);

        notesEdit = new QLineEdit(this);

        submitButton = new QPushButton(this);
        submitButton->setText("Submit Commissioner");
        connect(submitButton, &QPushButton::clicked, 
            this, &NewCommissionerWindow::newCommissionerSlot);

        mainLayout->addWidget(newComLabel);
        mainLayout->addLayout(comLayout);
        mainLayout->addWidget(submitButton);

        comLayout->addWidget(nameLabel, 0, 0);
        comLayout->addWidget(notesLabel, 1, 0);
        comLayout->addWidget(nameEdit, 0, 1);
        comLayout->addWidget(notesEdit, 1, 1);
    }

    void NewCommissionerWindow::newCommissionerSlot() {
        emit newCommissioner(nameEdit->text(), notesEdit->text());
        nameEdit->clear();
        notesEdit->clear();
        emit done(0);
    }
}