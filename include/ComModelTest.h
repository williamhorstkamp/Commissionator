#ifndef COMMODELTEST_H
#define COMMODELTEST_H

#include <QtTest/QtTest>
#include "ComModel.h"

namespace Commissionator {
    class ComModelTest : public QObject {

        Q_OBJECT

    private:
        ComModel *com;

    private slots:
        void initTestCase();
        void init();

        //void commissionsTest();
        //void commissionersTest();
        //void piecesTest();
        //void productsTest();
        //void salesTest();

        //void commissionTest();
        //void commissionerTest();
        //void pieceTest();
        //void productTest();
        //void saleTest();

        //void commissionPiecesTest();
        //void commissionPaymentsTest();
        //void commissionNotesTest();

        //void commissionerContactsTest();
        //void commissionerCommissionsTest();
        //void commissionerNotesTest();

        //void pieceEventsTest();
        //void pieceReferencesTest();
        //void pieceEventDatesTest();
        //void pieceDescriptionTest();

        //void productOptionsTest();
        //void productPiecesSoldTest();

        //void saleDescriptionTest();
        //void saleDealsTest();
        //void salePiecesSoldTest();

        void insertCommissioner();
        //void insertContactTest();
        //void insertPieceReferenceTest();
        void insertProduct();
        //void insertProductOption();
        //void insertSale();
        //void insertDeal();
        void insertPiece();
        void insertPayment();
        void insertCommission();
        void insertPaymentType();

        void cleanup();
        void cleanupTestCase();
    };
}

#endif