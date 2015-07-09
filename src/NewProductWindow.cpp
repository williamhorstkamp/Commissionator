#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QListView>
#include <QStringListModel>
#include "FixedRowTableDelegate.h"
#include "NewProductWindow.h"

namespace Commissionator {

    NewProductWindow::NewProductWindow(QWidget *parent) :
    BaseNewWindow(parent) {
        mainLayout = new QVBoxLayout(this);
        proLayout = new QGridLayout();

        newProLabel = new QLabel(this);
        newProLabel->setAlignment(Qt::AlignCenter);
        newProLabel->setFont(*titleFont);
        newProLabel->setText("Insert Product");

        nameLabel = new QLabel(this);
        nameLabel->setFont(*font);
        nameLabel->setText("Product Name:");

        priceLabel = new QLabel(this);
        priceLabel->setFont(*font);
        priceLabel->setText("Product Price:");

        nameEdit = new QLineEdit(this);
        connect(nameEdit, &QLineEdit::textChanged,
            this, &NewProductWindow::setSubmitEnabled);

        priceEdit = new QDoubleSpinBox(this);
        priceEdit->setDecimals(2);
        priceEdit->setMinimum(0);
        priceEdit->setMaximum(999999);

        QStringList list;
        productEventsModel = new QStringListModel(this);
        productEventsModel->setStringList(list);

        productEventsView = new QListView(this);
        productEventsView->setModel(productEventsModel);
        delegate = new FixedRowTableDelegate(this);
        delegate->setIcon(":/Delete.png");
        delegate->setIconSize(24);
        productEventsView->setItemDelegate(delegate);
        productEventsView->setSelectionMode(QAbstractItemView::NoSelection);
        connect(delegate, &FixedRowTableDelegate::buttonClicked,
            this, &NewProductWindow::deleteEventSlot);
        
        submitButton = new QPushButton(this);
        submitButton->setText("Submit Product");
        submitButton->setEnabled(false);
        connect(submitButton, &QPushButton::clicked,
            this, &NewProductWindow::newItemSlot);

        mainLayout->addWidget(newProLabel);
        mainLayout->addLayout(proLayout);
        mainLayout->addWidget(productEventsView);
        //mainLayout->addWidget(newProductEventButton);
        mainLayout->addWidget(submitButton);

        proLayout->addWidget(nameLabel, 0, 0);
        proLayout->addWidget(priceLabel, 1, 0);
        proLayout->addWidget(nameEdit, 0, 1);
        proLayout->addWidget(priceEdit, 1, 1);
    }

    NewProductWindow::~NewProductWindow() {
        delete proLayout;
    }

    void NewProductWindow::clear() {
        nameEdit->setText("");
        priceEdit->setValue(0);
        submitButton->setEnabled(false);
    }

    void NewProductWindow::deleteEventSlot(const QModelIndex &index) {
        productEventsModel->removeRow(index.row());
    }

    void NewProductWindow::newEventSlot(const QString eventName) {
        productEventsModel->stringList() << eventName;
    }

    void NewProductWindow::newItemSlot() {
        emit newProduct(nameEdit->text(), priceEdit->value());
        BaseNewWindow::newItemSlot();
    }

    void NewProductWindow::setSubmitEnabled() {
        if (nameEdit->text() != "")
            submitButton->setEnabled(true);
        else
            submitButton->setEnabled(false);
    }
}