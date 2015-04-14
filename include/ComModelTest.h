#ifndef COMMODELTEST_H
#define COMMODELTEST_H

#include <QtTest>
#include <QWidget>
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

        void commissionerContactsTest();
        void commissionerCommissionsTest();

        //void pieceEventsTest();
        //void pieceReferencesTest();
        //void pieceEventDatesTest();

        //void productOptionsTest();
        //void productPiecesSoldTest();

        //void saleDescriptionTest();
        //void saleDealsTest();
        //void salePiecesSoldTest();

        void insertCommissionerTest();
        void insertContactTest();
        //void insertPieceReferenceTest();
        void insertProductTest();
        //void insertProductOptionTest();
        //void insertSaleTest();
        //void insertDealTest();
        void insertPieceTest();
        void insertPaymentTest();
        void insertCommissionTest();
        void insertPaymentTypeTest();
        void insertContactTypeTest();

        //void searchCommissionsTest();
        //void searchCommissionersTest();
        //void searchProductsTest();
        //void searchPiecesTest();

        void cleanup();
        void cleanupTestCase();
        
    };
}

#endif
