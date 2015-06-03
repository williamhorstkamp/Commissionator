#ifndef COMMISSIONPANEL_H
#define COMMISSIONPANEL_H

#include <QVBoxLayout>
#include <QSqlQueryModel>
#include <QLabel>
#include <QComboBox>
#include <QTableView>
#include <QPushButton>
#include "FixedRowTableDelegate.h"

namespace Commissionator {
    class CommissionPanel : public QWidget {

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

        /**
         *  Destructor removes resources from the free store, cleaning up
         *  the panel
         */
        ~CommissionPanel();

    signals:
        /**
         *  Signal emit when the pieceTable's delete button is clicked.
         *  Is a fowarded to ComModel::deletePiece
         *
         *  @param index - index of the contact to delete
         */
        void deletePiece(const QModelIndex &index);

    private slots:
        /**
         *  Slot connects to ComModel::commissionChanged.
         *  Refreshes the Widgets that display the Commissioner data to match the
         *  newly selected commissioner.
         */
        virtual void updatePanel();

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
         *  Helper function creates QFonts
         */
        void createFonts();

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

        QVBoxLayout *layout;
        QGridLayout *titleLayout;
        QSqlQueryModel *commissionModel;
        QSqlQueryModel *commissionerNamesModel;
        QPushButton *unlockButton;
        QLabel *commissionerName;
        QComboBox *commissionerNamesCombo;
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
        QFont *titleFont;
        QFont *standardFont;
    };
}

#endif