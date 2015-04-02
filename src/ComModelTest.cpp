#include <QLabel>
#include <QDate>
#include <QLineEdit>
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
        com->setCommissioner(com->getCommissioners()->index(0, 1));
        QAbstractItemModel *coms = com->getCommissioner()->model();
        QVERIFY(coms->index(0, 0).data().toString() == "TestName");
        QVERIFY(coms->index(1, 0).data().toString() == "");
        QVERIFY(coms->index(0, 3).data().toString() == "TestName2");
        QVERIFY(coms->index(1, 3).data().toString() == "Test Notes");
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
        com->insertCommission(1, QDate::currentDate());
        QAbstractItemModel *coms = com->getCommissions();
        QVERIFY(coms->index(0, 1).data().toString() == "TestCommissioner");
        QVERIFY(coms->index(0, 2).data().toDate() == QDate::currentDate());
        QVERIFY(coms->index(0, 4).data().toDate() == QDate::currentDate());
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
        com->insertCommission(1, QDate::currentDate());
        com->insertProduct("TestName", 1.0);
        com->insertPiece(1, 1, "TestPiece", "");
        QAbstractItemModel *pieces = com->getPiece()->model();
        QVERIFY(pieces->index(0, 0).data().toString() == "TestCommissioner");
        QVERIFY(pieces->index(0, 1).data().toString() == "TestName");
        QVERIFY(pieces->index(0, 2).data().toDate() == QDate::currentDate());
        QVERIFY(pieces->index(0, 4).data().toString() == "");
    }

    void ComModelTest::insertPaymentTest() {
        com->insertCommissioner("TestCommissioner", "");
        com->insertPaymentType("PaymentType");
        com->insertCommission(1, QDate::currentDate());
        com->insertPiece(1, 1, "TestPiece", "");
        com->insertPayment(1, 1, 1.0, "PaymentDescription");
        com->setCommission(com->getCommissions()->index(0, 0));
        QAbstractItemModel *pays = com->getCommissionPayments();
        QVERIFY(pays->index(0, 0).data().toString() == "PaymentType");
        QVERIFY(pays->index(0, 1).data().toDate() == QDate::currentDate());
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
        QAbstractItemModel *coms = com->getCommissioners();
        com->insertCommissioner("TestCommissioner", "");
        com->insertCommissioner("TestCommissioner2", "");
        com->insertCommissioner("TestCommissioner3", "");
        com->insertProduct("TestProduct", 1.0);
        com->insertCommission(2, QDate::currentDate());
        com->insertPiece(1, 1, "TestPiece", "");
        com->insertCommission(3, QDate::currentDate());
        com->insertPiece(2, 1, "TestPiece2", "");
        com->insertPiece(2, 1, "TestPiece3", "");
        QVERIFY(coms->index(0, 1).data().toString() == "TestCommissioner");
        QVERIFY(coms->index(1, 1).data().toString() == "TestCommissioner2");
        QVERIFY(coms->index(2, 1).data().toString() == "TestCommissioner3");
        QVERIFY(coms->index(0, 2).data().toDate() == QDate::currentDate());
        QVERIFY(coms->index(1, 2).data().toDate() == QDate::currentDate());
        QVERIFY(coms->index(2, 2).data().toDate() == QDate::currentDate());
        QVERIFY(coms->index(0, 3).data().toDouble() == 0);
        QVERIFY(coms->index(1, 3).data().toDouble() == 1.0);
        QVERIFY(coms->index(2, 3).data().toDouble() == 2.0);
        com->insertPaymentType("TestPaymentType");
        com->insertPayment(2, 1, 2.0, "");
        QVERIFY(coms->index(2, 3).data().toDouble() == 0.0);
    }
    
    void ComModelTest::commissionerTest() {
        QDataWidgetMapper *coms = com->getCommissioner();
        com->insertCommissioner("TestCommissioner", "TestNotes");
        com->insertProduct("TestProduct", 1.0);
        com->insertCommission(2, QDate::currentDate());
        com->insertPiece(1, 1, "TestPiece", "");
        com->setCommissioner(com->getCommissioners()->index(0, 1));
        QLabel *name = new QLabel();
        QLabel *customerSince = new QLabel();
        QLabel *moneyOwed = new QLabel();
        QLineEdit *notes = new QLineEdit();
        coms->addMapping(name, 0);
        coms->addMapping(customerSince, 1);
        coms->addMapping(moneyOwed, 2);
        coms->addMapping(notes, 3);
        QVERIFY(name->text() == "TestCommissioner");
        QVERIFY(customerSince->text() == QDate::currentDate().toString("MM/DD/yyyy"));
        QVERIFY(moneyOwed->text().toDouble() == 1.0);
        QVERIFY(notes->text() == "TestNotes");
        notes->text() = "TestNotes2";
        QLabel *notes2 = new QLabel();
        coms->addMapping(notes2, 3);
        QVERIFY(notes2->text() == "TestNotes2");
        com->insertPaymentType("TypeName");
        com->insertPayment(1, 1, 1.0, "");
        QVERIFY(moneyOwed->text().toDouble() == 0.0);
        delete name;
        delete customerSince;
        delete moneyOwed;
        delete notes;
        delete notes2;
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
        QVERIFY(contacts->index(1, 1).data().toString() == "TestEntry4");
    }

    void ComModelTest::commissionerCommissionsTest() {
        QAbstractItemModel *commissions = com->getCommissionerCommissions();
        com->insertCommissioner("TestCommissioner", "");
        com->insertCommissioner("TestCommissioner2", "");
        com->insertProduct("TestProduct", 1.0);
        com->insertCommission(1, QDate::currentDate());
        com->insertCommission(1, QDate::currentDate());
        com->insertPiece(1, 1, "TestPiece", "");
        com->insertPiece(1, 1, "TestPiece2", "");
        com->insertPiece(2, 1, "TestPiece3", "");
        com->setCommissioner(com->getCommissioners()->index(0, 0));
        QVERIFY(commissions->index(0, 0).data().toDate() == QDate::currentDate());
        QVERIFY(commissions->index(0, 1).data().toString() == "Unpaid");
        QVERIFY(commissions->index(0, 2).data().toDouble() == 2.0);
        QVERIFY(commissions->index(0, 3).data().toString() == "Unfinished");
        QVERIFY(commissions->index(1, 0).data().toDate() == QDate::currentDate());
        QVERIFY(commissions->index(1, 1).data().toString() == "Unpaid");
        QVERIFY(commissions->index(1, 2).data().toDouble() == 1.0);
        QVERIFY(commissions->index(1, 3).data().toString() == "Unfinished");
        com->insertPaymentType("TestType");
        com->insertPayment(1, 1, 2.0, "");
        QVERIFY(commissions->index(0, 1).data().toDate() == QDate::currentDate());
        QVERIFY(commissions->index(1, 1).data().toString() == "Unpaid");
        com->setPiece(com->getPieces()->index(0, 0));
        QDataWidgetMapper *mapper = com->getPiece();
        QLabel *label = new QLabel();
        mapper->addMapping(label, 3);
        label->text() == QDate::currentDate().toString("MM/DD/yyyy");
        com->setPiece(com->getPieces()->index(1, 0));
        label->text() == QDate::currentDate().toString("MM/DD/yyyy");
        QVERIFY(commissions->index(0, 3).data().toDate() == QDate::currentDate());
        QVERIFY(commissions->index(1, 3).data().toString() == "UnFinished");
    }

    void ComModelTest::cleanup() {
    }

    void ComModelTest::cleanupTestCase(){
        delete com;
    }
    
}