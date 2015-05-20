#ifndef NEWCOMMISSIONERWINDOW_H
#define NEWCOMMISSIONERWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QDateEdit>
#include <QLineEdit>
#include <QPushButton>

namespace Commissionator {

    class NewCommissionWindow : public QDialog {

    public:
        NewCommissionWindow(QAbstractItemModel *model, 
            QWidget *parent = nullptr);

        NewCommissionWindow(QAbstractItemModel *model,
            const int frozenRow, QWidget *parent = nullptr);

    private:
        void init(QAbstractItemModel *model, const int frozenRow = NULL);

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