#ifndef NEWREFUNDWINDOW_H
#define NEWREFUNDWINDOW_H

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
    class NewRefundWindow : public BaseNewWindow {

        Q_OBJECT

    public:
        /**
         *  Initializes NewRefundWindow with the combobox displaying data from
         *  the given model
         *
         *  @param commissionModel - model containing commission data
         *  First column is Commission id, second is identifying information
         *      about the commission, third is amount owed, fourth is amount paid
         *  @param parent - pointer to parent widget
         */
        NewRefundWindow(QSqlQueryModel *commissionModel,
            QWidget *parent = nullptr);

        /**
         *  Destructor cleans up objects.
         */
        ~NewRefundWindow();

    signals:
        /**
         *  Signal contains commission id, payment type id, payment amount,
         *      and notes for the payment
         *
         *  @param commissionId - commission the payment is for
         *  @param paymentAmount - the amount the payment is made for
         *  @param paymentNotes - notes about the payment
         */
        void newRefund(const int commissionId, const double refundAmount, 
            const QString refundNotes);

        public slots:

        /**
         *  Sets the commission to the commission with the id given.
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

        private slots:
        /**
         *  Private slot updates the amountPaidLabel whenever a new item is
         *  selected from the commission drop-down box
         */
        void updateAmount();

    private:
        /**
         *  Function resets the window to default settings.
         */
        void clear();

        QVBoxLayout *mainLayout;
        QGridLayout *refundLayout;
        QLabel *newRefundLabel;
        QLabel *amountPaidLabel;
        QLabel *amountLabel;
        QLabel *notesLabel;
        QLabel *amountPaid;
        QDoubleSpinBox *amountEdit;
        QLineEdit *notesEdit;
        QPushButton *submitButton;

        int commissionId;
        QSqlQueryModel *commissionModel;
    };
}

#endif