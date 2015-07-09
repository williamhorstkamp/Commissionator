#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "NewEventWindow.h"

namespace Commissionator {

    NewEventWindow::NewEventWindow(QWidget *parent) {
        mainLayout = new QVBoxLayout(this);
        eventLayout = new QGridLayout();

        newEventLabel = new QLabel(this);
        newEventLabel->setAlignment(Qt::AlignCenter);
        newEventLabel->setFont(*titleFont);
        newEventLabel->setText("Insert Product Event");

        nameLabel = new QLabel(this);
        nameLabel->setFont(*font);
        nameLabel->setText("Event Name:");

        nameEdit = new QLineEdit(this);
        connect(nameEdit, &QLineEdit::textChanged,
            this, &NewEventWindow::setSubmitEnabled);

        submitButton = new QPushButton(this);
        submitButton->setText("Submit Piece");
        submitButton->setEnabled(false);
        connect(submitButton, &QPushButton::clicked,
            this, &NewEventWindow::newItemSlot);
    }

    NewEventWindow::~NewEventWindow() {
        delete eventLayout;
    }

    void NewEventWindow::clear() {
        nameEdit->setText("");
        submitButton->setEnabled(false);
    }

    void NewEventWindow::newItemSlot() {
        emit newEvent(nameEdit->text());
        BaseNewWindow::newItemSlot();
    }

    void NewEventWindow::setSubmitEnabled() {
        if (nameEdit->text() != "")
            submitButton->setEnabled(true);
        else
            submitButton->setEnabled(false);
    }
}