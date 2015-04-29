#include <QLabel>
#include <QDateTime>
#include "ComModelTest.h"

namespace Commissionator {
    /**
     *  Note: Because of the nature of black box testing, some features can't
     *  be tested 100% in isolation of one another.
     *  For instance, it can not be checked whether an insertion or deletion
     *  is successful without accessing the table it would be displayed on.
     *  Because of this, when a large number of related tests fail, the tester
     *  should first direct their focus towards the common functions, as some
     *  of the more basal features will hold the entire program up if they fail
     *  to function appropriately.
     */
    
    void ComModelTest::initTestCase() {
        com = new ComModel(this);
    }

    void ComModelTest::init() {
        com->newRecord();
    }
    
    void ComModelTest::insertCommissionerTest() {
        com->insertCommissioner("TestName", "");
        com->insertCommissioner("TestName2", "Test Notes");
        QVERIFY(com->getCommissioners()->index(0, 1).data().toString() == "TestName");
        //QVERIFY(com->getCommissioners()->index(0, 2).data().toString() == "");
        QVERIFY(com->getCommissioners()->index(1, 1).data().toString() == "TestName2");
        //QVERIFY(com->getCommissioners()->index(1, 2).data().toString() == "Test Notes");
    }
    
    void ComModelTest::insertProductTest() {
        com->insertProduct("TestName", 1.0);
        com->insertProduct("TestName2", 2.0);
        QAbstractItemModel *pros = com->getProducts();
        QVERIFY(pros->index(0, 1).data().toString() == "TestName");
        QVERIFY(pros->index(0, 2).data().toDouble() == 1.0);
        QVERIFY(pros->index(1, 1).data().toString() == "TestName2");
        QVERIFY(pros->index(1, 2).data().toDouble() == 2.0);
    }
    
    void ComModelTest::insertCommissionTest() {
        com->insertCommissioner("TestCommissioner", "");
        com->insertCommission(1, QDateTime::currentDateTime(), "TestNotes");
        QAbstractItemModel *coms = com->getCommissions();
        QVERIFY(coms->index(0, 1).data().toString() == "TestCommissioner");
        QVERIFY(coms->index(0, 2).data().toString()
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(coms->index(0, 4).data().toString()
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
    }

    void ComModelTest::insertPaymentTypeTest() {
        com->insertPaymentType("PaymentType");
        com->insertPaymentType("PaymentType2");
        QAbstractItemModel *pays = com->getPaymentTypes();
        QVERIFY(pays->index(0, 1).data().toString() == "PaymentType");
        QVERIFY(pays->index(1, 1).data().toString() == "PaymentType2");
    }
    
    void ComModelTest::insertPieceTest() {
        com->insertCommissioner("TestCommissioner", "");
        com->insertCommission(1, QDateTime::currentDateTime(), "");
        com->insertProduct("TestName", 1.0);
        com->insertPiece(1, 1, "TestPiece", "");
        com->setPiece(com->getPieces()->index(0, 0));
        QVERIFY(com->getPiece()->index(0, 0).data().toString() == "TestCommissioner");
        QVERIFY(com->getPiece()->index(0, 1).data().toString() == "TestPiece");
        QVERIFY(com->getPiece()->index(0, 2).data().toString()
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(com->getPiece()->index(0, 3).data().toString()
            == "Unfinished");
        QVERIFY(com->getPiece()->index(0, 4).data().toString() == "");
    }
    
    void ComModelTest::insertPaymentTest() {
        com->insertCommissioner("TestCommissioner", "");
        com->insertPaymentType("PaymentType");
        com->insertCommission(1, QDateTime::currentDateTime(), "");
        com->insertProduct("TestProduct", 1.0);
        com->insertPiece(1, 1, "TestPiece", "");
        com->insertPayment(1, 1, 1.0, "PaymentDescription");
        com->setCommission(com->getCommissions()->index(0, 1));
        QAbstractItemModel *pays = com->getCommissionPayments();
        QVERIFY(pays->index(0, 0).data().toString() == "PaymentType");
        QVERIFY(pays->index(0, 1).data().toString()
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(pays->index(0, 2).data().toDouble() == 1.0);
        QVERIFY(pays->index(0, 3).data().toString() == "PaymentDescription");
    }

    void ComModelTest::insertContactTypeTest() {
        com->insertContactType("TestContactType");
        com->insertContactType("TestContactType2");
        QAbstractItemModel *contacts = com->getContactTypes();
        QVERIFY(contacts->index(0, 1).data().toString() == "TestContactType");
        QVERIFY(contacts->index(1, 1).data().toString() == "TestContactType2");
    }

    void ComModelTest::insertContactTest() {
        com->insertCommissioner("TestCommissioner", "");
        com->insertContactType("TestContactType");
        com->insertContact(1, 1, "TestEntry");
        com->setCommissioner(com->getCommissioners()->index(0, 1));
        QAbstractItemModel *contacts = com->getCommissionerContacts();
        QVERIFY(contacts->index(0, 0).data().toString() == "TestContactType");
        QVERIFY(contacts->index(0, 1).data().toString() == "TestEntry");
    }
    
    void ComModelTest::commissionersTest() {  
        com->insertCommissioner("TestCommissioner", "");
        com->insertCommissioner("TestCommissioner2", "");
        com->insertCommissioner("TestCommissioner3", "");
        com->insertProduct("TestProduct", 1.0);
        com->insertCommission(2, QDateTime::currentDateTime(), "");
        com->insertPiece(1, 1, "TestPiece", "");
        com->insertCommission(3, QDateTime::currentDateTime(), "");
        com->insertPiece(2, 1, "TestPiece2", "");
        com->insertPiece(2, 1, "TestPiece3", "");
        com->searchCommissioners("", "", "");
        QAbstractItemModel *coms = com->getCommissioners();
        for (int i = 0; i < coms->rowCount(); ++i)
            for (int j = 0; j < coms->columnCount(); ++j)
                qDebug() << coms->index(i, j).data().toString();
        for (int i = 0; i < com->getPieces()->rowCount(); ++i)
            for (int j = 0; j < com->getPieces()->columnCount(); ++j)
                qDebug() << com->getPieces()->index(i, j).data().toString();
        QVERIFY(coms->index(0, 1).data().toString() == "TestCommissioner");
        QVERIFY(coms->index(0, 2).data().toString() == "No Commissions");
        QVERIFY(coms->index(0, 3).data().toString() == "No Commissioned Pieces");
        QVERIFY(coms->index(1, 1).data().toString() == "TestCommissioner2");
        QVERIFY(coms->index(1, 2).data().toString()
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(coms->index(1, 3).data().toDouble() == 1.0);
        QVERIFY(coms->index(2, 1).data().toString() == "TestCommissioner3");
        QVERIFY(coms->index(2, 2).data().toString()
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(coms->index(2, 3).data().toDouble() == 2.0);
        com->insertPaymentType("TestPaymentType");
        com->insertPayment(1, 1, 2.0, "");
        com->searchCommissioners("", "", "");
        qDebug() << coms->index(2, 3).data().toString();
        QVERIFY(coms->index(2, 3).data().toString() == "Paid Off");
    }
    
    void ComModelTest::commissionerTest() {
        QSqlQueryModel *coms = com->getCommissioner();
        com->insertCommissioner("TestCommissioner", "TestNotes");
        com->insertProduct("TestProduct", 1.0);
        com->insertCommission(1, QDateTime::currentDateTime(), "");
        com->insertPiece(1, 1, "TestPiece", "");
        com->setCommissioner(com->getCommissioners()->index(0, 0));
        for (int i = 0; i < coms->columnCount(); ++i)
            qDebug() << coms->index(0, i).data().toString();
        QVERIFY(coms->index(0, 0).data().toString() == "TestCommissioner");
        QVERIFY(coms->index(0, 1).data().toString()
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(coms->index(0, 2).data().toDouble() == 1.0);
        QVERIFY(coms->index(0, 3).data().toString() == "TestNotes");
        com->insertPaymentType("TypeName");
        com->insertPayment(1, 1, 1.0, "");
        com->setCommissioner(com->getCommissioners()->index(0, 0));
        qDebug() << coms->index(0, 2).data().toString();
        QVERIFY(coms->index(0, 2).data().toDouble() == 0.0);
    }
    
    void ComModelTest::commissionerContactsTest() {
        QAbstractItemModel *contacts = com->getCommissionerContacts();
        com->insertCommissioner("TestCommissioner", "");
        com->setCommissioner(com->getCommissioners()->index(0, 0));
        com->insertContactType("TestType");
        com->insertContactType("TestType2");
        com->insertContact(1, 1, "TestEntry");
        com->insertContact(1, 1, "TestEntry2");
        com->insertContact(1, 2, "TestEntry3");
        QVERIFY(contacts->index(0, 0).data().toString() == "TestType");
        QVERIFY(contacts->index(0, 1).data().toString() == "TestEntry");
        QVERIFY(contacts->index(1, 0).data().toString() == "TestType");
        QVERIFY(contacts->index(1, 1).data().toString() == "TestEntry2");
        QVERIFY(contacts->index(2, 0).data().toString() == "TestType2");
        QVERIFY(contacts->index(2, 1).data().toString() == "TestEntry3");
        com->insertCommissioner("TestCommissioner2", "");
        com->insertContact(2, 1, "TestEntry4");
        com->setCommissioner(com->getCommissioners()->index(1, 0));
        QVERIFY(contacts->index(0, 0).data().toString() == "TestType");
        QVERIFY(contacts->index(0, 1).data().toString() == "TestEntry4");
    }

    void ComModelTest::commissionerCommissionsTest() {
        com->insertCommissioner("TestCommissioner", "");
        com->insertProduct("TestProduct", 1.0);
        com->insertCommission(1, QDateTime::currentDateTime(), "");
        com->insertCommission(1, QDateTime::currentDateTime(), "");
        com->insertPiece(1, 1, "TestPiece", "");
        com->insertPiece(1, 1, "TestPiece2", "");
        com->insertPiece(2, 1, "TestPiece3", "");
        com->setCommissioner(com->getCommissioners()->index(0, 0));
        QAbstractItemModel *commissions = com->getCommissionerCommissions();
        qDebug() << "Commissioners";
        for (int i = 0; i < com->getCommissioners()->rowCount(); ++i)
            for (int j = 0; j < com->getCommissioners()->columnCount(); ++j)
                qDebug() << com->getCommissioners()->index(i, j).data().toString();
        qDebug() << "Commissions";
        for (int i = 0; i < com->getCommissions()->rowCount(); ++i)
            for (int j = 0; j < com->getCommissions()->columnCount(); ++j)
                qDebug() << com->getCommissions()->index(i, j).data().toString();
        qDebug() << "Combo";
        for (int i = 0; i < commissions->rowCount(); ++i)
            for (int j = 0; j < commissions->columnCount(); ++j)
                qDebug() << commissions->index(i, j).data().toString();
        qDebug() << "Pieces";
        for (int i = 0; i < com->getPieces()->rowCount(); ++i)
            for (int j = 0; j < com->getPieces()->columnCount(); ++j)
                qDebug() << com->getPieces()->index(i, j).data().toString();
        QVERIFY(commissions->index(0, 0).data().toString()
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(commissions->index(0, 1).data().toString() == "Unpaid");
        QVERIFY(commissions->index(0, 2).data().toDouble() == 2.0);
        QVERIFY(commissions->index(0, 3).data().toString() == "Unfinished");
        QVERIFY(commissions->index(1, 0).data().toString()
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(commissions->index(1, 1).data().toString() == "Unpaid");
        QVERIFY(commissions->index(1, 2).data().toDouble() == 1.0);
        QVERIFY(commissions->index(1, 3).data().toString() == "Unfinished");
        com->insertPaymentType("TestType");
        com->insertPayment(1, 1, 2.0, "");
        qDebug() << commissions->index(0, 1).data().toString();
        qDebug() << commissions->index(1, 1).data().toString();
        QVERIFY(commissions->index(0, 1).data().toString()
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(commissions->index(1, 1).data().toString() == "Unpaid");
    }
    
    void ComModelTest::cleanup() {
        com->close();
    }

    void ComModelTest::cleanupTestCase() {
        delete com;
    }
    
}