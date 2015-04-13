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
        QDateTime convertedTime = QDateTime();
        QVERIFY(coms->index(0, 1).data().toString() == "TestCommissioner");
        convertedTime.setMSecsSinceEpoch(coms->index(0, 2).data().toString().toLongLong());
        QVERIFY(convertedTime.toString("MM/dd/yyyy")
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        convertedTime.setMSecsSinceEpoch(coms->index(0, 4).data().toString().toLongLong());
        QVERIFY(convertedTime.toString("MM/dd/yyyy")
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
    }

    void ComModelTest::insertPaymentTypeTest() {
        com->insertPaymentType("PaymentType");
        com->insertPaymentType("PaymentType2");
        QAbstractItemModel *pays = com->getPaymentTypes();
        QVERIFY(pays->index(0, 1).data().toString() == "PaymentType");
        QVERIFY(pays->index(1, 1).data().toString() == "PaymentType2");
    }
    /*
    void ComModelTest::insertPieceTest() {
        com->insertCommissioner("TestCommissioner", "");
        com->insertCommission(1, QDateTime::currentDateTime(), "");
        com->insertProduct("TestName", 1.0);
        com->insertPiece(1, 1, "TestPiece", "");
        QAbstractItemModel *piecesE = com->getPieceEditable()->model();
        QAbstractItemModel *piecesG = com->getPieceGenerated()->model();
        QVERIFY(piecesG->index(0, 0).data().toString() == "TestCommissioner");
        QVERIFY(piecesG->index(0, 1).data().toString() == "TestName");
        QVERIFY(piecesE->index(0, 1).data().toString() == "TestPiece");
        QVERIFY(piecesE->index(0, 3).data().toDateTime().toString("MM/dd/yyyy")
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(piecesE->index(0, 5).data().toString() == "");
    }
    */
    void ComModelTest::insertPaymentTest() {
        com->insertCommissioner("TestCommissioner", "");
        com->insertPaymentType("PaymentType");
        com->insertCommission(1, QDateTime::currentDateTime(), "");
        com->insertProduct("TestProduct", 1.0);
        com->insertPiece(1, 1, "TestPiece", "");
        com->insertPayment(1, 1, 1.0, "PaymentDescription");
        com->setCommission(com->getCommissions()->index(0, 0));
        QAbstractItemModel *pays = com->getCommissionPayments();
        QVERIFY(pays->index(0, 0).data().toString() == "PaymentType");
        QVERIFY(pays->index(0, 1).data().toDateTime().toString("MM/dd/yyyy")
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
        for (int i = 0; i < contacts->rowCount(); i++){
            qDebug() << contacts->index(i, 0).data().toString();
            qDebug() << contacts->index(i, 1).data().toString();
        }     
        QVERIFY(contacts->index(0, 0).data().toString() == "TestContactType");
        QVERIFY(contacts->index(0, 1).data().toString() == "TestEntry");
    }
    /**
    void ComModelTest::commissionersTest() {
        QAbstractItemModel *coms = com->getCommissioners();
        com->insertCommissioner("TestCommissioner", "");
        com->insertCommissioner("TestCommissioner2", "");
        com->insertCommissioner("TestCommissioner3", "");
        com->insertProduct("TestProduct", 1.0);
        com->insertCommission(2, QDateTime::currentDateTime());
        com->insertPiece(1, 1, "TestPiece", "");
        com->insertCommission(3, QDateTime::currentDateTime());
        com->insertPiece(2, 1, "TestPiece2", "");
        com->insertPiece(2, 1, "TestPiece3", "");
        qDebug() << coms->index(0, 1).data().toString();
        com->setCommissioner(coms->index(0, 1));
        qDebug() << com->getCommissionerEditable()->model()->index(0, 1).data().toString();
        QVERIFY(coms->index(0, 1).data().toString() == "TestCommissioner");
        QVERIFY(coms->index(1, 1).data().toString() == "TestCommissioner2");
        QVERIFY(coms->index(2, 1).data().toString() == "TestCommissioner3");
        QVERIFY(coms->index(0, 2).data().toDateTime().toString("MM/dd/yyyy")
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(coms->index(1, 2).data().toDateTime().toString("MM/dd/yyyy")
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(coms->index(2, 2).data().toDateTime().toString("MM/dd/yyyy")
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(coms->index(0, 3).data().toDouble() == 0);
        QVERIFY(coms->index(1, 3).data().toDouble() == 1.0);
        QVERIFY(coms->index(2, 3).data().toDouble() == 2.0);
        com->insertPaymentType("TestPaymentType");
        com->insertPayment(2, 1, 2.0, "");
        QVERIFY(coms->index(2, 3).data().toDouble() == 0.0);
    }
    
    void ComModelTest::commissionerTest() {
        QDataWidgetMapper *comsE = com->getCommissionerEditable();
        QDataWidgetMapper *comsG = com->getCommissionerGenerated();
        com->insertCommissioner("TestCommissioner", "TestNotes");
        com->insertProduct("TestProduct", 1.0);
        com->insertCommission(2, QDateTime::currentDateTime());
        com->insertPiece(1, 1, "TestPiece", "");
        com->setCommissioner(com->getCommissioners()->index(1, 0));
        QLabel *name = new QLabel();
        QLabel *customerSince = new QLabel();
        QLabel *moneyOwed = new QLabel();
        QLabel *notes = new QLabel();
        comsE->addMapping(name, 0);
        comsG->addMapping(customerSince, 0);
        comsG->addMapping(moneyOwed, 1);
        comsE->addMapping(notes, 1);
        QVERIFY(name->text() == "TestCommissioner");
        QVERIFY(QDateTime::fromString(customerSince->text()).toString("MM/dd/yyyy")
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(moneyOwed->text().toDouble() == 1.0);
        QVERIFY(notes->text() == "TestNotes");
        notes->text() = "TestNotes2";
        name->text() = "TestCommissioner2";
        QLabel *notes2 = new QLabel();
        comsE->addMapping(notes2, 1);
        QVERIFY(notes2->text() == "TestNotes2");
        QVERIFY(name->text() == "TestCommissioner2");
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
        com->insertCommission(1, QDateTime::currentDateTime());
        com->insertCommission(1, QDateTime::currentDateTime());
        com->insertPiece(1, 1, "TestPiece", "");
        com->insertPiece(1, 1, "TestPiece2", "");
        com->insertPiece(2, 1, "TestPiece3", "");
        com->setCommissioner(com->getCommissioners()->index(0, 0));
        QVERIFY(commissions->index(0, 0).data().toDateTime().toString("MM/dd/yyyy")
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(commissions->index(0, 1).data().toString() == "Unpaid");
        QVERIFY(commissions->index(0, 2).data().toDouble() == 2.0);
        QVERIFY(commissions->index(0, 3).data().toString() == "Unfinished");
        QVERIFY(commissions->index(1, 0).data().toDateTime().toString("MM/dd/yyyy")
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(commissions->index(1, 1).data().toString() == "Unpaid");
        QVERIFY(commissions->index(1, 2).data().toDouble() == 1.0);
        QVERIFY(commissions->index(1, 3).data().toString() == "Unfinished");
        com->insertPaymentType("TestType");
        com->insertPayment(1, 1, 2.0, "");
        QVERIFY(commissions->index(0, 1).data().toDateTime().toString("MM/dd/yyyy")
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(commissions->index(1, 1).data().toString() == "Unpaid");
        com->setPiece(com->getPieces()->index(1, 0));
        QVERIFY(commissions->index(0, 3).data().toDateTime().toString("MM/dd/yyyy")
            == QDateTime::currentDateTime().toString("MM/dd/yyyy"));
        QVERIFY(commissions->index(1, 3).data().toString() == "UnFinished");
    }
    */
    void ComModelTest::cleanup() {
        com->close();
    }

    void ComModelTest::cleanupTestCase() {
        delete com;
    }
    
}