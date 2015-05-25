#ifndef NEWCOMMISSIONERWINDOW_H
#define NEWCOMMISSIONERWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

namespace Commissionator {

    class NewCommissionerWindow : public QDialog {

        Q_OBJECT

    public:
        /**
         *  Initializes the NewCommissionerWindow.
         *
         *  @param parent - pointer to parent model
         */
        NewCommissionerWindow(QWidget *parent = nullptr);

        /**
         *  Destructor cleans up NewCommissionerWindow
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

    private slots:
        /** 
         *  Slot intercepts the QPushButton::clicked signal from the insert
         *  commissioner button and emits the newCommissioner signal.
         */
        void newCommissionerSlot();

    private:
        /**
         *  Private function initializes the window
         *
         */
        void init();

        QVBoxLayout *mainLayout;
        QGridLayout *comLayout;
        QFont *titleFont;
        QFont *font;
        QLabel *newComLabel;
        QLabel *nameLabel;
        QLabel *notesLabel;
        QLineEdit *nameEdit;
        QLineEdit *notesEdit;
        QPushButton *submitButton;
    };
}

#endif