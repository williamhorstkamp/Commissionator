#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QVariant>
#include <QDialog>

class QVBoxLayout;
class QGridLayout;
class QLabel;
class FixedRowTable;
class QAbstractItemModel;
class QFont;

namespace Commissionator {
    class OptionsDialog : public QDialog {

        Q_OBJECT

    public:
        /**
         *  Constructor accepts models needed to build the options menu
         *
         *  @param contactTypesModel - model containing a list of contact types
         *  @param paymentTypesModel - model containing a list of payment types
         *  @param parent - pointer to parent widget
         */
        OptionsDialog(QAbstractItemModel *contactTypesModel, 
            QAbstractItemModel *paymentTypesModel, QWidget *parent = nullptr);

    signals:
        /**
         *  Signal emitted when a contact type is to be deleted
         *
         *  @param index - index to be deleted
         */
        void deleteContactType(const QModelIndex &index);

        /**
         *  Signal emitted when a payment type is to be deleted
         *
         *  @param index - index to be deleted
         */
        void deletePaymentType(const QModelIndex &index);

        /**
         *  Signal emit when a contact type is to be added
         *
         *  @param contactType - name of the contact type
         */
        void insertContactType(const QString contactType);

        /**
         *  Signal emit when a payment type is to be added
         *
         *  @param paymentType - name of the payment type
         */
        void insertPaymentType(const QString paymentType);

    private slots:
        /**
         *  Slot captures FixedRowTable::boxQuery from contactTypeTable and
         *  emits the corresponding insertContactType signal.
         *
         *  @param query - QList of QVariants containing the query variable
         *  Data order:
         *  Contact Type
         */
        void insertContactTypeSlot(const QList<QVariant> query);

        /**
         *  Slot captures FixedRowTable::boxQuery from paymentTypeTable and
         *  emits the corresponding insertPaymentType signal.
         *
         *  @param query - QList of QVariants containing the query variable
         *  Data order:
         *  Payment Type
         */
        void insertPaymentTypeSlot(const QList<QVariant> query);

    private:
        QVBoxLayout *mainLayout;
        QGridLayout *optionLayout;
        QLabel *optionsLabel;
        QLabel *contactLabel;
        FixedRowTable *contactTypeTable;
        QLabel *paymentLabel;
        FixedRowTable *paymentTypeTable;
        QFont *titleFont;
        QFont *font;
    };
}

#endif