#ifndef COMMISSIONPANEL_H
#define COMMISSIONPANEL_H

#include "RightPanel.h"
#include "FixedRowTableDelegate.h"

class QSqlQueryModel;
class QVBoxLayout;
class QGridLayout;
class QLabel;
class QComboBox;
class QPushButton;
class QTableView;

namespace Commissionator {
    class CommissionPanel : public RightPanel {

        Q_OBJECT

    public:
        /**
         *  Constructor accepts QSqlQueryModels for the selected commission,
         *  the pieces that make it up, and the payments made to it. 
         *
         *  @param commissionModel - QSqlQueryModel containing data about
         *      selected commission
         *  @param commissionPiecesModel - QSqlQueryModel containing data about
         *      selected commission pieces
         *  @param commissionPaymentsModel - QSqlQueryModel containing data about
         *      selected commission payments
         *  @param productNamesMode - QSqlQueryModel containing the names and
         *      ids of the products
         */
        CommissionPanel(QSqlQueryModel *commissionModel,
            QSqlQueryModel *piecesModel, QSqlQueryModel *paymentsModel, 
            QSqlQueryModel *commissionerNamesModel, QWidget *parent = nullptr);

    signals:
        /**
         *  Signal emit when the pieceTable's delete button is clicked.
         *  Is a fowarded to ComModel::deletePiece
         *
         *  @param index - index of the contact to delete
         */
        void deletePiece(const QModelIndex &index);

        /**
         *  Signal emit when the commissioner's name has been edited during the
         *  edit mode of the panel
         *
         *  @param commission - id of the commission
         *  @param commissioner - id of the commission
         */
        void editCommissioner(const int commission, const int commissioner);

        /**
         *  Signal emit when the commissioner's name has been edited during the
         *  edit mode of the panel
         *
         *  @param commission - id of the commission
         *  @param notes - new notes for the commission
         */
        void editNotes(const int commission, const QString notes);

        /**
         *  Signal emit when the newCommissionButton is clicked.
         *  Is to be forwarded to MainWindow::newCommission.
         *
         *  @param commission - the id of the commission to create
         *      a payment for
         */
        void newPayment(const QVariant &commission);

        /**
         *  Signal emit when the newCommissionButton is clicked.
         *  Is to be forwarded to MainWindow::newCommission.
         *
         *  @param commission - the id of the commission to create
         *      a piece for
         */
        void newPiece(const QVariant &commission);

    public slots:
        /**
         *  Slot connects to ComModel::commissionChanged.
         *  Refreshes the Widgets that display the Commissioner data to match the
         *  newly selected commissioner.
         */
        virtual void updatePanel();

    private slots:
        /**
         *  Slot captures QPushButton::clicked from newCommissionButton and
         *  emits the corresponding newCommission signal
         */
        void newPaymentSlot();

        /**
         *  Slot captures QPushButton::clicked from newCommissionButton and
         *  emits the corresponding newCommission signal
         */
        void newPieceSlot();

        /**
         *  Slot toggles between the panel's edit and display modes.
         *  Has the unlockButton plugged into it.
         */
        virtual void toggleEdit();

    private:
        /**
         *  Helpers function creates buttons and connections
         */
        void createButtons();

        /**
         *  Helper function creates QLabels and QTextEdit
         */
        void createLabels();

        /**
         *  Helper function builds panel by placing widgets into the layout and applying it
         */
        void createPanel();

        /**
         *  Helper function creates tables
         *
         *  @param piecesModel - QSqlQueryModel containing data about the
         *      selected commission's pieces
         *  @param paymentsModel - QSqlQueryModel containing data about the
         *      selected commission's payments
          *  @param productNamesModel - QSqlQueryModel containing a list of
         *      product names
         */
        void createTables(QSqlQueryModel *piecesModel,
            QSqlQueryModel *paymentsModel);

        QSqlQueryModel *commissionModel;
        QSqlQueryModel *commissionerNamesModel;
        QPushButton *unlockButton;
        QLabel *commissionerName;
        QComboBox *commissionerNameCombo;
        QLabel *createDate;
        QLabel *paidDate;
        QLabel *dueDate;
        QLineEdit *dueEdit;
        QLabel *amountOwed;
        QLabel *piecesLabel;
        QTableView *piecesTable;
        QPushButton *newPieceButton;
        FixedRowTableDelegate *piecesDelegate;
        QLabel *paymentsLabel;
        QTableView *paymentsTable;
        QPushButton *newPaymentButton;
        QLabel *notesLabel;
        QLabel *commissionNotes;
        QLineEdit *commissionNotesEdit;
    };
}

#endif