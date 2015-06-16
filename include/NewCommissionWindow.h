#ifndef NEWCOMMISSIONWINDOW_H
#define NEWCOMMISSIONWINDOW_H

#include <QDateTime>
#include "BaseNewWindow.h"
#include "FixedRowTableDelegate.h"
#include "NewPieceWindow.h"

class QStandardItemModel;
class QVBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QDateEdit;
class QComboBox;
class QCheckBox;
class QDoubleSpinBox;
class QDateTime;
class QTableView;

namespace Commissionator {

    class NewCommissionWindow : public BaseNewWindow {

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
         *  Destructor.
         */
        ~NewCommissionWindow();

    signals:
        /**
         *  Signal contains the commissioner id, the due date, and the notes
         *  for a new commission
         *
         *  @param commissionerId - commissioner id
         *  @param dueDate - the due date of the commission
         *  @param notes - notes for the commission
         *  @param pieces - list of tuples representing each piece in the commission
         *  Tuple Order:
         *  Product Id, Piece Name, Piece Notes, Override Price (default -1)
         */
        void newCommission(const int commissionerId,
            const QDateTime dueDate, const QString notes, 
            QList<std::tuple<const int, const QString, const QString, const double>> pieces);

    public slots:
        /**
         *  Sets the commissioner to the commissioner with the id given.
         *  Also disables the commissioner combobox
         *
         *  @param commissioner - commissioner to set the combo box to
         */
        void setCommissioner(const QVariant &commissioner);

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
         *  Slot deletes the piece at the given index.
         *
         *  @param index - index of the piece to delete
         */
        void deletePieceSlot(const QModelIndex &index);

        /**
         *  Slot adds a new piece to the newPieceView based on given parameters
         *
         *  @param query - QList of Qvariants containing the query variables
         *  Data order:
         *  Product Id, Product Name, Piece Name, Piece Notes
         */
        void newPieceSlot(const QString pieceName, const QString pieceNotes,
            const int productId, const QString productName, const double price);

    private:
        /**
         *  Function resets the window to default settings.
         */
        void clear();

        QVBoxLayout *mainLayout; 
        QGridLayout *comLayout;
        QLabel *newComLabel;
        QLabel *comLabel;
        QLabel *dueLabel;
        QLabel *notesLabel;
        QLabel *pieceLabel;
        QComboBox *comBox;
        QDateEdit *calendarEdit;
        QLineEdit *notesEdit;
        QStandardItemModel *newPieceModel;
        FixedRowTableDelegate *delegate;
        QTableView *newPieceView;
        QPushButton *newPieceButton;
        QPushButton *submitButton;
        NewPieceWindow *piecePopup;
    };

}

#endif