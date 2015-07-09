#ifndef NEWPIECEWINDOW_H
#define NEWPIECEWINDOW_H

#include "BaseNewWindow.h"

class QAbstractItemModel;
class QVBoxLayout;
class QGridLayout;
class QLabel;
class QLineEdit;
class QComboBox;
class QCheckBox;
class QDoubleSpinBox;

namespace Commissionator {

    class NewPieceWindow : public BaseNewWindow {

        Q_OBJECT

    public:
        /**
         *  Initializes NewPieceWindow.
         *
         *  @param productsModel - a model containing the list of products
         *  First column should be product id, second product name
         *  @param parent - pointer to parent model
         */
        NewPieceWindow(QAbstractItemModel *productsModel, QWidget *parent = nullptr);

        /**
         *  Destructor.
         */
        ~NewPieceWindow();

    signals:
        /**
         *  Signal contains piece name, notes, and product type as both
         *  Product Id and Name
         *
         *  @param pieceName - piece name
         *  @param pieceNotes - piece notes
         *  @param productId - product id
         *  @param productName - product names
         *  @param price - override price (-1 by default)
         */
        void newPiece(const QString pieceName, const QString pieceNotes,
            const int productId, const QString productName, 
            const double price = -1);

    protected slots:
        /**
         *  Slot intercepts the QPushButton::clicked signal from the insert
         *  piece button and emits the newCommissioner signal.
         */
        virtual void newItemSlot();

        /**
         *  Slot captures currentIndexChanged/currentTextChanged and confirms
         *  that all necissary fields are entered before enabling the submit button.
         */
        virtual void setSubmitEnabled();

    private slots:
        /**
         *  Slot catches QCheckBox::stateChanged from the price override checkbox
         *  and toggles whether the price lineedit is displayed.
         */
        void setPriceOverride();

    private:
        /**
        *  Function resets the window to default settings.
        */
        void clear();

        QVBoxLayout *mainLayout;
        QGridLayout *pieLayout;
        QLabel *newPieLabel;
        QLabel *pieNameLabel;
        QLabel *pieNotesLabel;
        QLabel *proNameLabel;
        QLineEdit *pieNameEdit;
        QLineEdit *pieNotesEdit;
        QComboBox *proBox;
        QCheckBox *priceCheck;
        QDoubleSpinBox *priceEdit;
        QPushButton *submitButton;
    };
}

#endif