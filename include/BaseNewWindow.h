#ifndef BASENEWWINDOW_H
#define BASENEWWINDOW_H

#include <QDialog>

namespace Commissionator {

    class BaseNewWindow : public QDialog {

        Q_OBJECT

    public:
        /**
         *  Constructor assings parent and initilizes fonts.
         *
         *  @param parent - pointer to parent widget
         */
        BaseNewWindow(QWidget *parent = nullptr);

        /**
         *  Destructor clears deletes fonts.
         */
        ~BaseNewWindow();

    protected:
        /**
         *  Overrides default function and makes it so inherited classes
         *  clear all fields on exit.
         *
         *  @param e - QCloseEvent to handle by the overridden function
         */
        virtual void closeEvent(QCloseEvent *e);

    protected slots:
        /*
         *  Slot captures submit signal, emits the corresponding new signal,
         *  and clears the fields.
         *  Should be overriden by any subclass that expects to actually do
         *  anything sensible.
         */
        virtual void newItemSlot();

    protected:
        QFont *titleFont;
        QFont *font;

    private:
        /**
         *  Function resets the window to default settings.
         *  Must be implemented by inherited classes
         */
        virtual void clear() = 0;
    };
}

#endif