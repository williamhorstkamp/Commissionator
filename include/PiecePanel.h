#ifndef PIECEPANEL_H
#define PIECEPANEL_H

#include <QVariant>
#include "RightPanel.h"

class QSqlQueryModel;
class QPushButton;
class QLineEdit;
class QLabel;
class QTableView;

namespace Commissionator {
    class PiecePanel : public RightPanel {

        Q_OBJECT

    public:
        /**
         *  Constructor accepts QSqlQueryModels for the selected piece, the
         *  events that must be performed to construct it, and any references
         *  it may have.
         *
         *  @param pieceModel - QSqlQueryModel containing data about the
         *      selected piece
         *  @param eventsModel - QSqlQueryModel containing data about the selected
         *      piece's product's events
         *  @param referencesModel - QSqlQueryModel containing data about the
         *      locations of the selected piece's references
         */
        PiecePanel(QSqlQueryModel *pieceModel, QSqlQueryModel *eventsModel
            /*,QSqlQueryModel *referencesModel*/);

    signals:
        /**
         *  Signal emit when the piece's name or notes have been edited during
         *  the edit mode of the panel.
         *
         *  @param piece - id of the piece
         *  @param pieceName - name of the piece
         *  @param - notes - notes for the piece
         */
        void edit(const int piece, const QString pieceName,
            const QString notes);

    public slots:
        /**
         *  Slot connects to ComModel::pieceChanged.
         *  Refreshes the Widgets that display the piece data to match the newly
         *  selected piece
         */
        void updatePanel();

    private slots:
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
         *  @param eventsModel - QSqlQueryModel containing data about the selected
         *      piece's product's events
         *  @param referencesModel - QSqlQueryModel containing data about the
         *      locations of the selected piece's references
         */
        void createTables(QSqlQueryModel *eventsModel
            /*, QSqlQueryModel *referencesModel*/);

        QSqlQueryModel *pieceModel;
        QPushButton *unlockButton;
        QLabel *pieceName;
        QLineEdit *pieceNameEdit;
        QLabel *commissionerName;
        QLabel *startDate;
        QLabel *finishDate;
        QTableView *eventsTable;
        QLabel *description;
        QLineEdit *descriptionEdit;
    };
}

#endif