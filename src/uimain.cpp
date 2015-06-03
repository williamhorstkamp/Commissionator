#include <QApplication>
#include "mainwindow.h"

using namespace Commissionator;

int main(int argc, char *argv[]) {
    Q_INIT_RESOURCE(commissionator);
    QApplication app(argc, argv);
    app.setOrganizationName("William Horstkamp");
    app.setApplicationName("Commissionator");
    MainWindow mainWindow;
    mainWindow.show();
    
    return app.exec();
}
