#ifndef NEWCOMMISSIONERWINDOW_H
#define NEWCOMMISSIONERWINDOW_H

#include "BaseNewWindow.h"

class QLineEdit;
class QLabel;
class QVBoxLayout;
class QGridLayout;

namespace Commissionator {

    class NewCommissionerWindow : public BaseNewWindow {

        Q_OBJECT

    public:
        /**
         *  Initializes the NewCommissionerWindow.
         *
         *  @param parent - pointer to parent model
         */
        NewCommissionerWindow(QWidget *parent = nullptr);

        /**
         *  Destructor.
         */
        ~NewCommissionerWindow();

    signals:
        /**
         *  Signal contains commissioner name and notes for the new 
         *  commissioner.
         *
         *  @param name - commissioner name
         *  @param notes - commissioner notes
         */
        void newCommissioner(const QString name, const QString notes);

    protected slots:
        /** 
         *  Slot intercepts the QPushButton::clicked signal from the insert
         *  commissioner button and emits the newCommissioner signal.
         */
        virtual void newItemSlot();

    private:

        /**
         *  Function resets the window to default settings.
         */
        virtual void clear();

        QVBoxLayout *mainLayout;
        QGridLayout *comLayout;
        QLabel *newComLabel;
        QLabel *nameLabel;
        QLabel *notesLabel;
        QLineEdit *nameEdit;
        QLineEdit *notesEdit;
        QPushButton *submitButton;
    };
}

#endif