#ifndef NEWEVENTWINDOW_H
#define NEWEVENTWINDOW_H

#include "BaseNewWindow.h"

class QVBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QPushButton;

namespace Commissionator {

    class NewEventWindow : public BaseNewWindow {

        Q_OBJECT

    public:
        /**
         *  Initializes NewPieceWindow.
         *
         *  @param productsModel - a model containing the list of products
         *  First column should be product id, second product name
         *  @param parent - pointer to parent model
         */
        NewEventWindow(QWidget *parent = nullptr);

        /**
         *  Destructor.
         */
        ~NewEventWindow();

    signals:
        /**
         *  Signal contains event name
         *
         *  @param eventName - the name of the newly entered event
         */
        void newEvent(const QString eventName);

    protected slots:
        /**
         *  Slot intercepts the QPushButton::clicked signal from the insert
         *  event button and emits the newCommissioner signal.
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
        QGridLayout *eventLayout;
        QLabel *newEventLabel;
        QLabel *nameLabel;
        QLineEdit *nameEdit;
        QPushButton *submitButton;
    };
}

#endif