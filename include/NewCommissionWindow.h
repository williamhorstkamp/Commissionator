#ifndef NEWCOMMISSIONWINDOW_H
#define NEWCOMMISSIONWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QDateEdit>
#include <QLineEdit>
#include <QPushButton>

namespace Commissionator {

    class NewCommissionWindow : public QDialog {

        Q_OBJECT

    public:
        /**
         *  Initializes NewCommissionWindow with the combobox displaying data
         *  from the given model
         *
         *  @param namesModel - model containing the commissioner names
         *  First column should be the commissioner id, second should be name
         */
        NewCommissionWindow(QAbstractItemModel *namesModel, 
            QWidget *parent = nullptr);

        /**
         *  Destructor cleans up the NewCommissionWindow
         */
        ~NewCommissionWindow();

    protected:
        /**
         *  Overrides default function and makes it so the combobox is enabled.
         *
         *  @param e - QCloseEvent to handle by the overriden function
         */
        virtual void closeEvent(QCloseEvent *e);

    signals:
        /**
         *  Signal contains the commissioner id, the due date, and the notes
         *  for a new commission
         *
         *  @param commissionerId - commissioner id
         *  @param dueDate - the due date of the commission
         *  @param notes - notes for the commission
         */
        void newCommission(const int commissionerId,
            const QDateTime dueDate, const QString notes);

    public slots:
        /**
         *  Sets the commissioner to the commissioner with the id given.
         *  Also disables comBox
         *
         *  @param commissioner - commissioner to set the combo box to
         */
        void setCommissioner(const QVariant &commissioner);

    private slots:
        /**
         *  Function intercepts the QPushButton::clicked signal from the insert
         *  commissin button and emits the newCommission signal.
         */
        void newCommissionSlot();

    private:
        /**
         *  Private function initializes the window with the given names model
         *
         *  @param namesModel - model containing the commissioner names
         *  First column should be the commissioner id, second should be name
         */
        void init(QAbstractItemModel *namesModel);

        QVBoxLayout *mainLayout;
        QGridLayout *comLayout;
        QFont *titleFont;
        QFont *font;
        QLabel *newComLabel;
        QLabel *comLabel;
        QLabel *dueLabel;
        QLabel *notesLabel;
        QComboBox *comBox;
        QDateEdit *calendarEdit;
        QLineEdit *notesEdit;
        QPushButton *submitButton;
    };

}

#endif