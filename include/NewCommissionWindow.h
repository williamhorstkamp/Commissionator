#ifndef NEWCOMMISSIONWINDOW_H
#define NEWCOMMISSIONWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QDateEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include "ComboEditorDelegate.h"
#include "FixedRowTable.h"

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
         *  @param productsModel - model containing the product names
         *  First column should be the product id, second should be name
         *  @param parent - pointer to parent widget
         */
        NewCommissionWindow(QAbstractItemModel *namesModel,
            QAbstractItemModel *productsModel, QWidget *parent = nullptr);

        /**
         *  Destructor cleans up the NewCommissionWindow
         */
        ~NewCommissionWindow();

    protected:
        /**
         *  Overrides default function and makes it so the combobox is enabled.
         *
         *  @param e - QCloseEvent to handle by the overridden function
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
         *  Slot deletes the piece at the given index.
         *
         *  @param index - index of the piece to delete
         */
        void deletePieceSlot(const QModelIndex &index);

        /**
         *  Slot intercepts the QPushButton::clicked signal from the insert
         *  commission button and emits the newCommission signal.
         */
        void newCommissionSlot();

        /**
         *  Slot adds a new piece to the newPieceView based on given parameters
         *
         *  @param query - QList of Qvariants containing the query variables
         *  Data order:
         *  Product Id, Product Name, Piece Name, Piece Notes
         */
        void newPieceSlot(const QList<QVariant> query);

    private:
        /**
         *  Function resets the window to default settings.
         */
        void clear();

        /**
         *  Private function initializes the window with the given names model
         *
         *  @param namesModel - model containing the commissioner names
         *  First column should be the commissioner id, second should be name
         *  @param productsModel - model containing the product names
         *  First column should be the product id, second should be name
         */
        void init(QAbstractItemModel *namesModel,
            QAbstractItemModel *productsModel);

        QVBoxLayout *mainLayout; 
        QGridLayout *comLayout;
        QFont *titleFont;
        QFont *font;
        QLabel *newComLabel;
        QLabel *comLabel;
        QLabel *dueLabel;
        QLabel *notesLabel;
        QLabel *pieceLabel;
        QComboBox *comBox;
        QDateEdit *calendarEdit;
        QLineEdit *notesEdit;
        QPushButton *submitButton;
        QAbstractItemModel *pieceProductsModel;
        QStandardItemModel *newPieceModel;
        ComboEditorDelegate *pieceTypeDelegate;
        FixedRowTable *newPieceView;
    };

}

#endif