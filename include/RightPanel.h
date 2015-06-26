#ifndef RIGHTPANEL_H
#define RIGHTPANEL_H

#include <QWidget>

class QFont;
class QVBoxLayout;
class QGridLayout;

namespace Commissionator {
    class RightPanel : public QWidget {

        Q_OBJECT

    public:
        /**
         *  Default constructor accepts optional parent to pass to QWidget
         *  constructor
         *
         *  @param parent - pointer to parent
         */
        RightPanel(QWidget *parent = nullptr);

        /**
         *  Destructor removes resources from the free store, cleaning up
         *  the panel
         */
        ~RightPanel();

    public slots:
        /**
         *  Refreshes the Widgets that display the panel data to match the
         *  newly selected item.
         */
        virtual void updatePanel() = 0;

    private slots:
        /**
         *  Slot toggles between the panel's edit and display modes.
         */
        virtual void toggleEdit() = 0;

    private:
        /**
         *  Helpers function creates buttons and connections
         */
        virtual void createButtons() = 0;

        /**
         *  Helper function creates QFonts
         */
        virtual void createFonts();

        /**
         *  Helper function creates QLabels and QTextEdit
         */
        virtual void createLabels() = 0;

        /**
         *  Helper function builds panel by placing widgets into the layout and applying it
         */
        virtual void createPanel() = 0;

    protected:

        QVBoxLayout *layout;
        QGridLayout *titleLayout;
        QFont *titleFont;
        QFont *standardFont;
    };
}

#endif