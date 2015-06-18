#include <QVBoxLayout>
#include "RightPanel.h"

namespace Commissionator {
    RightPanel::RightPanel(QWidget *parent) : QWidget(parent) {
        createFonts();
    }

    RightPanel::~RightPanel() {
        delete titleFont;
        delete standardFont;
        delete titleLayout;
    }

    void RightPanel::createFonts() {
        titleFont = new QFont();
        titleFont->setPointSize(12);
        titleFont->setBold(true);

        standardFont = new QFont();
        standardFont->setPointSize(10);
    }
}