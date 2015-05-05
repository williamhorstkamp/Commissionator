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
         *
         */
        CommissionerPanel(QSqlQueryModel *commissionerModel, 
            QSqlQueryModel *contactModel, QSqlQueryModel *commissionsModel);

        /**
         *  Destructor removes resources from the free store, cleaning up
         *  the panel
         */
        ~CommissionerPanel();

    signals:
        /**
        *  Signal thrown when the newCommissionButton is clicked.
        *  Is to be forwarded to MainWindow::newCommission.
        */
        void newCommission();

        /**
         *  Signal thrown when the contactInfoTable's button is clicked.
         *  Is forwarded from FixedRowTable::boxQuery and is to be forwarded to
         *  MainWindow::insertContact
         */
        void insertContact(const QString commissioner, const QString type, 
            const QString entry);


    public slots:
        /**
         *  Slot connects to ComModel::commissionerChanged.
         *  If the signal is of type "Commissioner", then the slot should
         *  refresh the Widgets that display the Commissioner data to match the 
         *  newly selected commissioner.
         */
        void updatePanel();

    private:
        /**
         *  Helper function creates QFonts and paid QPalette
         */
        void createFonts();

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