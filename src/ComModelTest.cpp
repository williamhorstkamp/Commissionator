#include "ComModel.h"
#include "ComModelTest.h"

namespace Commissionator {
    void ComModelTest::initTestCase() {
        com = new ComModel(this);
    }

    void ComModelTest::init() {
        com->newRecord();
    }

    void ComModelTest::insertCommissioner() {
        com->insertCommissioner("TestName", "");
        com->insertCommissioner("TestName2", "Test Notes");
        com->setCommissioner(com->getCommissioners()->index(0, 1));
        QAbstractItemModel *coms = com->getCommissioner()->model();
        QVERIFY(coms->index(0, 0).data().toString() == "None"); //checks for empty commissioner
        QVERIFY(coms->index(1, 0).data().toString() == "TestName");
        QVERIFY(coms->index(2, 0).data().toString() == "");
        QVERIFY(coms->index(1, 3).data().toString() == "TestName2");
        QVERIFY(coms->index(2, 3).data().toString() == "Test Notes");
    }

    void ComModelTest::insertProduct() {
        com->insertProduct("TestName", 1.0);
        com->insertProduct("TestName2", 2.0);
        QAbstractItemModel *pros = com->getProducts();
        QVERIFY(pros->index(0, 1).data().toString() == "TestName");
        QVERIFY(pros->index(0, 2).data().toDouble() == 1.0);
        QVERIFY(pros->index(1, 1).data().toString() == "TestName2");
        QVERIFY(pros->index(1, 2).data().toDouble() == 2.0);
    }

    void ComModelTest::insertCommission() {
        com->insertCommissioner("TestCommissioner", "");
        com->insertCommission(1, QDate::currentDate());
        QAbstractItemModel *coms = com->getCommissions();
        QVERIFY(coms->index(0, 1).data().toString() == "TestCommissioner");
        QVERIFY(coms->index(0, 2).data().toDate() == QDate::currentDate());
        QVERIFY(coms->index(0, 4).data().toDate() == QDate::currentDate());
    }

    void ComModelTest::insertPaymentType() {
        com->insertPaymentType("PaymentType");
        com->insertPaymentType("PaymentType2");
        QAbstractItemModel *pays = com->getPaymentTypes();
        QVERIFY(pays->index(0, 1).data().toString() == "Generic");  //checks for empty payment type
        QVERIFY(pays->index(1, 1).data().toString() == "PaymentType");
        QVERIFY(pays->index(2, 1).data().toString() == "PaymentType2");
    }

    void ComModelTest::insertPiece() {
        com->insertCommissioner("TestCommissioner", "");
        com->insertPaymentType("PaymentType");
        com->insertCommission(1, QDate::currentDate());
        com->insertProduct("TestName", 1.0);
        com->insertPiece(1, 1, "");
        QAbstractItemModel *pieces = com->getPieces()
    }

    void ComModelTest::insertPayment() {
        com->insertCommissioner("TestCommissioner", "");
        com->insertPaymentType("PaymentType");
        com->insertCommission(1, QDate::currentDate());
        com->insertPiece()
        com->insertPayment(1, 1, 1.0);
    }

    void ComModelTest::cleanup() {
    }

    void ComModelTest::cleanupTestCase(){
        delete com;
    }
}