#ifndef NEWPRODUCTWINDOW_H
#define NEWPRODUCTWINDOW_H

#include "BaseNewWindow.h"

class QVBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QDoubleSpinBox;
class QStringListModel;
class QListView;
class FixedRowTableDelegate;

namespace Commissionator {

    class NewProductWindow : public BaseNewWindow {

        Q_OBJECT

    public:
        /**
         *  Initializes NewProductWindow.
         *
         *  @param parent - pointer to parent model
         */
        NewProductWindow(QWidget *parent = nullptr);

        /**
         *  Destructor.
         */
        ~NewProductWindow();

    signals:
        /**
         *  Signal contains product name and base price.
         *
         *  @param productName - name of the product
         *  @param basePrice - price of the product on creation
         */
        void newProduct(const QString productName, const double basePrice);

    protected slots:
        /**
         *  Slot intercepts the QPushButton::clicked signal from the insert
         *  product button and emits the newCommissioner signal.
         */
        virtual void newItemSlot();

        /**
         *  Slot captures currentIndexChanged/currentTextChanged and confirms
         *  that all necissary fields are entered before enabling the submit button.
         */
        virtual void setSubmitEnabled();

    private slots:
        /**
         *  Slot deletes the piece at the given index.
         *
         *  @param index - index of the piece to delete
         */
        void deleteEventSlot(const QModelIndex &index);

        /**
         *  Slot adds a new piece to the newPieceView based on given parameters
         *
         *  @param eventName - the name of the newly created event
         */
        void newEventSlot(const QString eventName);

    private:
        /**
         *  Function resets the window to default settings.
         */
        void clear();

        QVBoxLayout *mainLayout;
        QGridLayout *proLayout;
        QLabel *newProLabel;
        QLabel *nameLabel;
        QLabel *priceLabel;
        QLineEdit *nameEdit;
        QDoubleSpinBox *priceEdit;
        QStringListModel *productEventsModel;
        FixedRowTableDelegate *delegate;
        QListView *productEventsView;
        QPushButton *newProductEventButton;
        QPushButton *submitButton;
    };
}

#endif