#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>
#include "ComModelTest.h"
using namespace Commissionator;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTest::qExec(&ComModelTest(), argc, argv);
    return a.exec();
}