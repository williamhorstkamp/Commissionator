#ifndef COMMISSIONERPANEL_H
#define COMMISSIONERPANEL_H

#include "ComboEditorDelegate.h"
#include "FixedRowTable.h"

class QVBoxLayout;
class QGridLayout;
class QLabel;
class QTextEdit;
class QPushButton;
class QSqlQueryModel;

namespace Commissionator {
    class CommissionerPanel : public QWidget {

        Q_OBJECT

    public:
        /**
         *  Constructor accepts QSqlQueryModels for the selected
         *  commissioner, their contacts, and their commissions. Models used to
         *  populate the panels various fields.
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
            QSqlQueryModel *contactTypesModel, QWidget *parent = nullptr);

        /**
         *  Destructor removes resources from the free store, cleaning up
         *  the panel
         */
        ~CommissionerPanel();

    signals:

        /**
         *  Signal emit when the contactInfoTable's delete button is clicked.
         *  Is a modification of FixedRowTable::tableButtonClicked and is
         *  fowarded to ComModel::deleteContact
         *
         *  @param index - index of the contact to delete
         */
        void deleteContact(const QModelIndex &index);

        /** 
         *  Signal emit when the commissioner's name has been edited during the
         *  edit mode of the panel
         *
         *  @param commissioner - id of the commissioner
         *  @param name - new name for the commissioner
         */
        void editName(const int commissioner, const QString name);

        /**
         *  Signal emit when the commissioner's notes has been edited during the
         *  edit mode of the panel
         *
         *  @param commissioner - id of the commissioner
         *  @param notes - new notes for the commissioner
         */
        void editNotes(const int commissioner, const QString notes);

        /**
         *  Signal emit when the contactInfoTable's button is clicked.
         *  Is a modification of FixedRowTable::boxQuery and is to be forwarded to
         *  ComModel::insertContact
         *
         *  @param commissioner - commissioner id
         *  @param type - type id
         *  @param entry - entry text
         */
        void insertContact(const int commissioner, const int type, 
            const QString entry);

        /**
         *  Signal emit when the newCommissionButton is clicked.
         *  Is to be forwarded to MainWindow::newCommission.
         *
         *  @param commissioner - the id of the commissioner to create
         *      a commissioner for
         */
        void newCommission(const QVariant &commissioner);

    public slots:
        /**
         *  Slot connects to ComModel::commissionerChanged.
         *  Refreshes the Widgets that display the Commissioner data to match the 
         *  newly selected commissioner.
         */
        void updatePanel();

    private slots:
        /**
         *  Slot captures FixedRowTable::boxQuery from contactInfoTable and
         *  emits the corresponding insertContact signal.
         *
         *  @param query - QList of Qvariants containing the query variables
         *  Data order:
         *  Commissioner Id, Contact Type, Entry
         */
        void insertContactSlot(const QList<QVariant> query);

        /**
         *  Slot captures QPushButton::clicked from newCommissionButton and
         *  emits the corresponding newCommission signal
         */
        void newCommissionSlot();

        /**
         *  Slot toggles between the panel's edit and display modes.
         *  Has the unlockButton plugged into it.
         */
        void toggleEdit();

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
        QGridLayout *titleLayout;
        QSqlQueryModel *commissionerModel;
        QLabel *commissionerName;
        QLineEdit *commissionerNameEdit;
        QPushButton *unlockButton;
        QLabel *commissionerDate;
        QLabel *commissionerPaid;
        QLabel *contactInfoLabel;
        FixedRowTable *contactInfoTable;
        ComboEditorDelegate *contactDelegate;
        QLabel *commissionsLabel;
        QTableView *commissionsTable;
        QPushButton *newCommissionButton;
        QLabel *notesLabel;
        QLabel *commissionerNotes;
        QLineEdit *commissionerNotesEdit;
        QFont *titleFont;
        QFont *standardFont;
    };
}

#endif