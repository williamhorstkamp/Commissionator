#ifndef COMMISSIONERPANEL_H
#define COMMISSIONERPANEL_H

#include <QVBoxLayout>
#include <QLabel>
#include <QTableView>
#include <QTextEdit>
#include <QPushButton>
#include <QSqlQueryModel>
#include <QDataWidgetMapper>
#include "FixedRowTable.h"

namespace Commissionator {
    class CommissionerPanel : public QWidget {

        Q_OBJECT

    public:
        
        /**
         *  Default constructor accepts QSqlQueryModels for the selected
         *  commissioner, their contacts, and their commissions. Will use these
         *  models to populate the panels various fields.
         *
         *  @param commissionerModel - QSqlQueryModel containing data about the
         *      selected commissioner
         *  @param contactModel - QSqlQueryModel containing data about the
         *      selected commissioner's contacts
         *  @param commissionsModel - QSqlQueryModel containing data about the
         *      selected commissioner's commissions
         *  @param contactTypesModel - QSqlQueryModel containing a list of
         *      contact types
         */
        CommissionerPanel(QSqlQueryModel *commissionerModel, 
            QSqlQueryModel *contactModel, QSqlQueryModel *commissionsModel,
            QSqlQueryModel *contactTypesModel);

        /**
         *  Destructor removes resources from the free store, cleaning up
         *  the panel
         */
        ~CommissionerPanel();

    signals:
        /**
         *  Signal thrown when the contactInfoTable's button is clicked.
         *  Is a modification of FixedRowTable::boxQuery and is to be forwarded to
         *  MainWindow::insertContact
         */
        void insertContact(const int commissioner, const int type, 
            const QString entry);

        /**
         *  Signal thrown when the newCommissionButton is clicked.
         *  Is to be forwarded to MainWindow::newCommission.
         */
        void newCommission();

    public slots:
        /**
         *  Slot captures FixedRowTable::boxQuery and emits the corresponding
         *  insertContact signal
         */
        void insertContactSlot(const QList<QVariant> query);

        /**
         *  Slot connects to ComModel::commissionerChanged.
         *  If the signal is of type "Commissioner", then the slot should
         *  refresh the Widgets that display the Commissioner data to match the 
         *  newly selected commissioner.
         */
        void updatePanel();

    private:
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
         *  @param contactModel - QSqlQueryModel containing data about the
         *      selected commissioner's contacts
         *  @param commissionsModel - QSqlQueryModel containing data about the
         *      selected commissioner's commissions
         *  @param contactTypesModel - QSqlQueryModel containing a list of
         *      contact types
         */
        void createTables(QSqlQueryModel *contactModel, 
            QSqlQueryModel *commissionsModel, 
            QSqlQueryModel *commissionerNamesModel);

        QVBoxLayout *layout;
        QSqlQueryModel *commissionerModel;
        QLabel *commissionerName;
        QLabel *commissionerDate;
        QLabel *commissionerPaid;
        QLabel *contactInfoLabel;
        FixedRowTable *contactInfoTable;
        QLabel *commissionsLabel;
        QTableView *commissionsTable;
        QPushButton *newCommissionButton;
        QLabel *notesLabel;
        QTextEdit *notesEdit;
        QFont *titleFont;
        QFont *standardFont;
    };
}

#endif