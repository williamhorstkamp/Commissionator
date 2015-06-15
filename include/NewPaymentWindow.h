#ifndef NEWPAYMENTWINDOW_H
#define NEWPAYMENTWINDOW_H

#include "BaseNewWindow.h"

class QSqlQueryModel;
class QVBoxLayout;
class QGridLayout;
class QLabel;
class QComboBox;
class QDoubleSpinBox;
class QLineEdit;
class QPushButton;

namespace Commissionator {
    class NewPaymentWindow : public BaseNewWindow {

        Q_OBJECT

    public:
        /**
         *  Initializes NewPaymentWindow with the combobox displaying data from
         *  the given model
         *
         *  @param commissionModel - model containing commission data
         *  First column is Commission id, second is identifying information
         *      about the commission
         *  @param paymentModel - model containing payment type data
         *  First column is payment type id, second is payment type name
         */
        NewPaymentWindow(QSqlQueryModel *commissionModel,
            QSqlQueryModel *paymentModel, QWidget *parent = nullptr);

        /**
         *  Destructor cleans up objects.
         */
        ~NewPaymentWindow();

    signals:
        /**
         *  Signal contains commission id, payment type id, payment amount,
         *      and notes for the payment
         *
         *  @param commissionId - commission the payment is for
         *  @param paymentTypeId - type of payment that is being made
         *  @param paymentAmount - the amount the payment is made for
         *  @param paymentNotes - notes about the payment
         */
        void newPayment(const int commissionId, const int paymentTypeId,
            const double paymentAmount, const QString paymentNotes);

    public slots:

        /**
         *  Sets the commission to the commission with the id given.
         *  Also disables the commission combobox
         *
         *  @param commission - commission to set the combo box to
         */
        void setCommission(const QVariant &commission);

    protected slots:
        /**
         *  Slot intercepts the QPushButton::clicked signal from the insert
         *  commission button and emits the newCommission signal.
         */
        virtual void newItemSlot();

        /**
         *  Slot captures currentIndexChanged/currentTextChanged and confirms
         *  that all necissary fields are entered before enabling the submit button.
         */
        virtual void setSubmitEnabled();

    private:
        /**
        *  Function resets the window to default settings.
        */
        void clear();

        QVBoxLayout *mainLayout;
        QGridLayout *payLayout;
        QLabel *newPayLabel;
        QLabel *comLabel;
        QLabel *typeLabel;
        QLabel *amountLabel;
        QLabel *notesLabel;
        QComboBox *comBox;
        QComboBox *typeBox;
        QDoubleSpinBox *amountEdit;
        QLineEdit *notesEdit;
        QPushButton *submitButton;
    };
}

#endif