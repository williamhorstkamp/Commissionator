#include <QKeyEvent>
#include "BaseNewWindow.h"

namespace Commissionator {

    BaseNewWindow::BaseNewWindow(QWidget *parent) : QDialog(parent) {
        titleFont = new QFont();
        titleFont->setPointSize(12);
        titleFont->setBold(true);

        font = new QFont();
        font->setPointSize(10);
    }

    BaseNewWindow::~BaseNewWindow() {
        delete titleFont;
        delete font;
    }

    void BaseNewWindow::closeEvent(QCloseEvent *e) {
        clear();
        QDialog::closeEvent(e);
    }

    void BaseNewWindow::keyPressEvent(QKeyEvent *e) {
        if (e->key() == Qt::Key_Escape)
            clear();
        QDialog::keyPressEvent(e);
    }

    void BaseNewWindow::newItemSlot() {
        clear();
        emit done(0);
    }
}