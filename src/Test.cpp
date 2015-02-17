#include "ComModel.h"
#include <iostream>
#include "gtest/gtest.h"

using namespace Commissionator;
/**
 *  No real way to check insertion without also using accessors
 *  because of this, insertions are checked in the get test for each table
 */

TEST(V1Test, close) {
    ComModel *com = new ComModel();
    ASSERT_NO_THROW(com->close());
    ASSERT_THROW(com->insertContactType("test"), std::out_of_range);

    delete com;
}

TEST(V1Test, saveOpen) {
    ComModel *com = new ComModel();
    com->save("test.db3");
    com->close();
    ASSERT_THROW(com->save("test2.db3"), SQLiteException);  //can't save if db isnt open
    ASSERT_NO_THROW(com->open("test.db3"));
    EXPECT_NO_THROW(com->insertContactType("test"));

    delete com;
}

TEST(V1Test, getContactType) {
    ComModel *com = new ComModel();
    com->insertContactType("testType");
    com->insertContactType("testType2");

    std::vector<const std::tuple<const int, const std::string>> typeList;
    typeList.push_back(std::tuple<const int, const std::string>(1, "testType"));
    typeList.push_back(std::tuple<const int, const std::string>(2, "testType2"));
    EXPECT_EQ(typeList, com->getContactTypes());
    EXPECT_EQ("testType", com->getContactType(1));
    EXPECT_EQ("testType2", com->getContactType(2));
    typeList.clear();

    delete com;
}

TEST(V1Test, deleteContactType) {
    ComModel *com = new ComModel();
    com->insertContactType("testContactType");
    EXPECT_EQ("testContactType", com->getContactType(1));
    com->deleteContactType(1);
    std::vector<const std::tuple<const int, const std::string>> empty;
    EXPECT_EQ(empty, com->getContactTypes());

    delete com;
}

TEST(V1Test, setContactTypeName) {
    ComModel *com = new ComModel();
    com->insertContactType("testContactType");
    EXPECT_EQ("testContactType", com->getContactType(1));
    com->setContactTypeName(1, "testContactType1");
    EXPECT_EQ("testContactType1", com->getContactType(1));

    delete com;
}

TEST(V1Test, getCommissioners) {
    ComModel *com = new ComModel();
    com->insertCommissioner("testCommissioner");
    com->insertCommissioner("testCommissioner2");
    com->insertCommissioner("testCommissioner3");

    std::vector<const std::tuple<const int, const std::string>> comList;
    comList.push_back(std::tuple<int, std::string>(0, "None"));
    comList.push_back(std::tuple<int, std::string>(1, "testCommissioner"));
    comList.push_back(std::tuple<int, std::string>(2, "testCommissioner2"));
    comList.push_back(std::tuple<int, std::string>(3, "testCommissioner3"));
    EXPECT_EQ(comList, com->getCommissioners());
    EXPECT_EQ("testCommissioner", com->getCommissioner(1));
    EXPECT_EQ("testCommissioner2", com->getCommissioner(2));
    EXPECT_EQ("testCommissioner3", com->getCommissioner(3));
    comList.clear();

    delete com;
}

TEST(V1Test, deleteCommissioner) {
    ComModel *com = new ComModel();
    com->insertCommissioner("testCommissioner");
    com->insertCommission(1, "01/01/2001", "05/05/2005");
    std::vector<const std::tuple<const int, const int, const std::string, const std::string, const std::string>> commissionList;
    commissionList.push_back(std::tuple<const int, const int, const std::string, const std::string, const std::string>(1, 0, "01/01/2001", "05/05/2005", ""));
    EXPECT_EQ("testCommissioner", com->getCommissioner(1));
    com->deleteCommissioner(1);
    std::vector<const std::tuple<const int, const std::string>> comList;
    comList.push_back(std::tuple<int, std::string>(0, "None"));
    EXPECT_EQ(comList, com->getCommissioners());
    EXPECT_EQ(commissionList, com->getCommissions());

    delete com;
}

TEST(V1Test, setCommissionerName) {
    ComModel *com = new ComModel();
    com->insertCommissioner("testCommissioner");
    EXPECT_EQ("testCommissioner", com->getCommissioner(1));
    com->setCommissionerName(1, "testCommissioner1");
    EXPECT_EQ("testCommissioner1", com->getCommissioner(1));

    delete com;
}

TEST(V1Test, getContact) {
    ComModel *com = new ComModel();
    com->insertContactType("testType");
    com->insertCommissioner("testCommissioner");
    com->insertContact(1, 1, "testContact");
    std::vector<const std::tuple<const int, const  int, const std::string>> conList;
    conList.push_back(std::tuple<const int, const  int, const std::string>(1, 1, "testContact"));
    EXPECT_EQ(conList, com->getContacts(1));
    EXPECT_EQ(conList.at(0), com->getContact(1));
    conList.clear();

    delete com;
}

TEST(V1Test, deleteContact){
    ComModel *com = new ComModel();
    com->insertContactType("testType");
    com->insertCommissioner("testCommissioner");
    com->insertContact(1, 1, "testContact");
    std::vector<const std::tuple<const int, const  int, const std::string>> conList;
    conList.push_back(std::tuple<const int, const  int, const std::string>(1, 1, "testContact"));
    EXPECT_EQ(conList, com->getContacts(1));
    conList.clear();
    com->deleteContact(1);
    EXPECT_EQ(conList, com->getContacts(1));

    delete com;
}

TEST(V1Test, setContactType) {
    ComModel *com = new ComModel();
    com->insertContactType("testType");
    com->insertContactType("testType2");
    com->insertCommissioner("testCommissioner");
    com->insertContact(1, 1, "testContact");
    std::vector<const std::tuple<const int, const  int, const std::string>> conList;
    conList.push_back(std::tuple<const int, const  int, const std::string>(1, 1, "testContact"));
    conList.push_back(std::tuple<const int, const  int, const std::string>(1, 2, "testContact"));
    EXPECT_EQ(conList.at(0), com->getContact(1));
    com->setContactType(1, 2);
    EXPECT_EQ(conList.at(1), com->getContact(1));

    delete com;
}

TEST(V1Test, setContactName) {
    ComModel *com = new ComModel();
    com->insertContactType("testType");
    com->insertCommissioner("testCommissioner");
    com->insertContact(1, 1, "testContact");
    std::vector<const std::tuple<const int, const  int, const std::string>> conList;
    conList.push_back(std::tuple<const int, const  int, const std::string>(1, 1, "testContact"));
    conList.push_back(std::tuple<const int, const  int, const std::string>(1, 1, "testContact1"));
    EXPECT_EQ(conList.at(0), com->getContact(1));
    com->setContactEntry(1, "testContact1");
    EXPECT_EQ(conList.at(1), com->getContact(1));

    delete com;
}

TEST(V2Test, getProduct) {
    ComModel *com = new ComModel();
    com->insertProduct("testProduct", 1.0);
    com->insertProduct("testProduct2", 2.0);
    std::vector<const std::tuple<const int, const std::string, const double>>proList;
    proList.push_back(std::tuple<const int, const std::string, const double>(0, "Generic", 0)); //already exists in the database by default
    proList.push_back(std::tuple<const int, const std::string, const double>(1, "testProduct", 1.0));
    proList.push_back(std::tuple<const int, const std::string, const double>(2, "testProduct2", 2.0));
    EXPECT_EQ(proList, com->getProducts());
    std::tuple<const std::string, const double> testProduct("testProduct", 1.0);
    std::tuple<const std::string, const double> testProduct2("testProduct2", 2.0);
    EXPECT_EQ(testProduct, com->getProduct(1));
    EXPECT_EQ(testProduct2, com->getProduct(2));
    proList.clear();

    delete com;
}

TEST(V2Test, deleteProduct) {
    ComModel *com = new ComModel();
    com->insertCommissioner("testCommissioner");
    com->insertProduct("testProduct", 1.0);
    com->insertCommission(1, "01/01/2001", "05/05/2005");
    com->insertPiece(1, 1);
    std::vector<const std::tuple<const int, const std::string, const double>>proList;
    proList.push_back(std::tuple<const int, const std::string, const double>(0, "Generic", 0)); //already exists in the database by default
    proList.push_back(std::tuple<const int, const std::string, const double>(1, "testProduct", 1.0));
    std::vector<const std::tuple<const int, const int, const int, const std::string>> pieList;
    pieList.push_back(std::tuple<const int, const int, const int, const std::string>(1, 1, 0, ""));
    EXPECT_EQ(proList, com->getProducts());
    proList.clear();
    proList.push_back(std::tuple<const int, const std::string, const double>(0, "Generic", 0));
    com->deleteProduct(1);
    EXPECT_EQ(proList, com->getProducts());
    com->deleteProduct(0);
    EXPECT_EQ(proList, com->getProducts());
    EXPECT_EQ(pieList, com->getPieces());
    proList.clear();
    std::vector<const std::tuple<const int, const std::string, const double>>().swap(proList);

    delete com;
}

TEST(V2Test, setProductPrice) {
    ComModel *com = new ComModel();
    com->insertProduct("testProduct", 1.0);
    com->setProductPrice(1, 2.0);
    std::tuple<const std::string, const double> product("testProduct", 2.0);
    EXPECT_EQ(product, com->getProduct(1));

    delete com;
}

TEST(V2Test, setProductName) {
    ComModel *com = new ComModel();
    com->insertProduct("testProduct", 1.0);
    com->setProductName(1, "testProduct1");
    std::tuple<const std::string, const double> product("testProduct1", 1.0);
    EXPECT_EQ(product, com->getProduct(1));

    delete com;
}

TEST(V2Test, getCommission) {
    ComModel *com = new ComModel();
    com->insertCommissioner("testCommissioner");
    com->insertCommission(1, "01/01/2001", "05/05/2005");
    std::vector<const std::tuple<const int, const int, const std::string, const std::string, const std::string>> comList;
    comList.push_back(std::tuple<const int, const int, const std::string, const std::string, const std::string>(1, 1, "01/01/2001", "05/05/2005", ""));
    EXPECT_EQ(comList, com->getCommissions());
    std::tuple<const int, const std::string, const std::string, const std::string> testCommission(1, "01/01/2001", "05/05/2005", "");
    EXPECT_EQ(testCommission, com->getCommission(1));
    comList.clear();

    delete com;
}

TEST(V2Test, deleteCommission) {
    ComModel *com = new ComModel();
    com->insertCommissioner("testCommissioner");
    com->insertCommission(1, "01/01/2001", "05/05/2005");
    com->deleteCommission(1);
    std::vector<const std::tuple<const int, const int, const std::string, const std::string, const std::string>> empty;
    EXPECT_EQ(empty, com->getCommissions());
   
    delete com;
}

TEST(V2Test, setCommissionDueDate) {
    ComModel *com = new ComModel();
    com->insertCommissioner("testCommissioner");
    com->insertCommission(1, "01/01/2001", "05/05/2005");
    com->setCommissionDueDate(1, "06/06/2006");
    std::tuple<const int, const std::string, const std::string, const std::string> testCommission(1, "01/01/2001", "06/06/2006", "");
    EXPECT_EQ(testCommission, com->getCommission(1));

    delete com;
}

TEST(V2Test, setCommissionPaidDate) {
    ComModel *com = new ComModel();
    com->insertCommissioner("testCommissioner");
    com->insertCommission(1, "01/01/2001", "05/05/2005");
    com->setCommissionPaidDate(1, "05/05/2005");
    std::tuple<const int, const std::string, const std::string, const std::string> testCommission(1, "01/01/2001", "05/05/2005", "05/05/2005");
    EXPECT_EQ(testCommission, com->getCommission(1));

    delete com;
}

TEST(V2Test, getPieces) {
    ComModel *com = new ComModel();
    com->insertCommissioner("testCommissioner");
    com->insertProduct("testProduct", 1.0);
    com->insertProduct("testProduct2", 2.0);
    com->insertCommission(1, "01/01/2001", "05/05/2005");
    com->insertPiece(1, 1);
    com->insertPiece(1, 2, "testPiece2");
    std::vector<const std::tuple<const int, const int, const int, const std::string>> pieList;
    pieList.push_back(std::tuple<const int, const int, const int, const std::string>(1, 1, 1, ""));
    pieList.push_back(std::tuple<const int, const int, const int, const std::string>(2, 1, 2, "testPiece2"));
    EXPECT_EQ(pieList, com->getPieces());
    std::tuple<const int, const int, const std::string>piece(1, 1, "");
    EXPECT_EQ(piece, com->getPiece(1));
    pieList.clear();

    delete com;
}

TEST(V2Test, searchPieces) {
    ComModel *com = new ComModel();
    com->insertCommissioner("testCommissioner");
    com->insertProduct("testProduct", 1.0);
    com->insertProduct("testProduct2", 2.0);
    com->insertCommission(1, "01/01/2001", "05/05/2005");
    com->insertPiece(1, 1);
    com->insertPiece(1, 2, "testPiece2");
    std::vector<const std::tuple<const int, const int, const int, const std::string>> pieList;
    pieList.push_back(std::tuple<const int, const int, const int, const std::string>(2, 1, 2, "testPiece2"));
    EXPECT_EQ(pieList, com->searchPieces("test"));
    pieList.clear();

    delete com;
    
}

TEST(V2Test, deletePiece){
    ComModel *com = new ComModel();
    com->insertCommissioner("testCommissioner");
    com->insertProduct("testProduct", 1.0);
    com->insertCommission(1, "01/01/2001", "05/05/2005");
    com->insertPiece(1, 1);
    std::vector<const std::tuple<const int, const int, const int, const std::string>> pieList;
    pieList.push_back(std::tuple<const int, const int, const int, const std::string>(1, 1, 1, ""));
    EXPECT_EQ(pieList, com->getPieces());
    pieList.clear();
    com->deletePiece(1);
    EXPECT_EQ(pieList, com->getPieces());

    delete com;
}

TEST(V2Test, deletePieceByCommission){
    ComModel *com = new ComModel();
    com->insertCommissioner("testCommissioner");
    com->insertProduct("testProduct", 1.0);
    com->insertCommission(1, "01/01/2001", "05/05/2005");
    com->insertPiece(1, 1);
    std::vector<const std::tuple<const int, const int, const int, const std::string>> pieList;
    pieList.push_back(std::tuple<const int, const int, const int, const std::string>(1, 1, 1, ""));
    EXPECT_EQ(pieList, com->getPieces());
    pieList.clear();
    com->deletePieceByCommission(1);
    EXPECT_EQ(pieList, com->getPieces());

    delete com;
}

TEST(V2Test, setPieceDescription) {
    ComModel *com = new ComModel();
    com->insertCommissioner("testCommissioner");
    com->insertProduct("testProduct", 1.0);
    com->insertCommission(1, "01/01/2001", "05/05/2005");
    com->insertPiece(1, 1);
    std::vector<const std::tuple<const int, const int, const int, const std::string>> pieList;
    pieList.push_back(std::tuple<const int, const int, const int, const std::string>(1, 1, 1, ""));
    EXPECT_EQ(pieList, com->getPieces());
    pieList.clear();
    pieList.push_back(std::tuple<const int, const int, const int, const std::string>(1, 1, 1, "test"));
    com->setPieceDescription(1, "test");
    EXPECT_EQ(pieList, com->getPieces());
    pieList.clear();

    delete com;
}

TEST(V3Test, getPaymentMethods) {
    ComModel *com = new ComModel();
    com->insertPaymentMethod("testPaymentMethod");
    com->insertPaymentMethod("testPaymentMethod2");
    std::vector<const std::tuple<const int, const std::string>> methodList;
    methodList.push_back(std::tuple<const int, const std::string>(1, "testPaymentMethod"));
    methodList.push_back(std::tuple<const int, const std::string>(2, "testPaymentMethod2"));
    EXPECT_EQ(methodList, com->getPaymentMethods());
    EXPECT_EQ("testPaymentMethod", com->getPaymentMethod(1));
    EXPECT_EQ("testPaymentMethod2", com->getPaymentMethod(2));
    methodList.clear();

    delete com;
}

TEST(V3Test, deletePaymentMethod) {
    ComModel *com = new ComModel();
    com->insertPaymentMethod("testPaymentMethod");
    std::vector<const std::tuple<const int, const std::string>> methodList;
    methodList.push_back(std::tuple<const int, const std::string>(1, "testPaymentMethod"));
    EXPECT_EQ(methodList, com->getPaymentMethods());
    methodList.clear();
    com->deletePaymentMethod(1);
    EXPECT_EQ(methodList, com->getPaymentMethods());

    delete com;
}

TEST(V3Test, setPaymentMethodName) {
    ComModel *com = new ComModel();
    com->insertPaymentMethod("testPaymentMethod");
    std::vector<const std::tuple<const int, const std::string>> methodList;
    methodList.push_back(std::tuple<const int, const std::string>(1, "testPaymentMethod"));
    EXPECT_EQ(methodList, com->getPaymentMethods());
    methodList.clear();
    methodList.push_back(std::tuple<const int, const std::string>(1, "testPaymentMethod2"));
    com->setPaymentMethodName(1, "testPaymentMethod2");
    EXPECT_EQ(methodList, com->getPaymentMethods());
    methodList.clear();

    delete com;
}

TEST(V3Test, getPayments) {
    ComModel *com = new ComModel();
    com->insertPaymentMethod("testPaymentMethod");
    com->insertPaymentMethod("testPaymentMethod2");
    com->insertCommissioner("testCommissioner");
    com->insertCommissioner("testCommissioner2");
    com->insertPayment(1, 1, "01/01/2001", 10);
    com->insertPayment(2, 2, "02/02/2001", 15, "note stuff");
    com->insertPayment(1, 2, "02/02/2050", 500.05, "more note stuff");
    std::vector < const std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >> paymentList;
    paymentList.push_back(std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >(1, 1, 1, 
        "01/01/2001", 10, ""));
    paymentList.push_back(std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >(2, 2, 2, 
        "02/02/2001", 15, "note stuff"));
    paymentList.push_back(std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >(3, 1, 2,
        "02/02/2050", 15, "more note stuff"));
    EXPECT_EQ(paymentList, com->getPayments());
    paymentList.clear();
    std::tuple <const int, const int,
        const std::string, const double, const std::string > payment(1, 1,
        "01/01/2001", 10, "");
    EXPECT_EQ(payment, com->getPaymentById(1));

    delete com;
}

TEST(V3Test, setPaymentMethod) {
    ComModel *com = new ComModel();
    com->insertPaymentMethod("testPaymentMethod");
    com->insertPaymentMethod("testPaymentMethod2");
    com->insertCommissioner("testCommissioner");
    com->insertPayment(1, 1, "01/01/2001", 10);
    std::vector < const std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >> paymentList;
    paymentList.push_back(std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >(1, 1, 1,
        "01/01/2001", 10, ""));
    EXPECT_EQ(paymentList, com->getPayments());
    paymentList.clear();
    com->setPaymentMethod(1, 2);
    paymentList.push_back(std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >(1, 1, 2,
        "01/01/2001", 10, ""));
    EXPECT_EQ(paymentList, com->getPayments());
    paymentList.clear();

    delete com;
}

TEST(V3Test, setPaymentDate) {
    ComModel *com = new ComModel();
    com->insertPaymentMethod("testPaymentMethod");
    com->insertCommissioner("testCommissioner");
    com->insertPayment(1, 1, "01/01/2001", 10);
    std::vector < const std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >> paymentList;
    paymentList.push_back(std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >(1, 1, 1,
        "01/01/2001", 10, ""));
    EXPECT_EQ(paymentList, com->getPayments());
    paymentList.clear();
    com->setPaymentDate(1, "02/02/2002");
    paymentList.push_back(std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >(1, 1, 1,
        "02/02/2002", 10, ""));
    EXPECT_EQ(paymentList, com->getPayments());
    paymentList.clear();

    delete com;
}

TEST(V3Test, setPaymentAmount) {
    ComModel *com = new ComModel();
    com->insertPaymentMethod("testPaymentMethod");
    com->insertCommissioner("testCommissioner");
    com->insertPayment(1, 1, "01/01/2001", 10);
    std::vector < const std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >> paymentList;
    paymentList.push_back(std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >(1, 1, 1,
        "01/01/2001", 10, ""));
    EXPECT_EQ(paymentList, com->getPayments());
    paymentList.clear();
    com->setPaymentAmount(1, 20);
    paymentList.push_back(std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >(1, 1, 1,
        "01/01/2001", 20, ""));
    EXPECT_EQ(paymentList, com->getPayments());
    paymentList.clear();

    delete com;
}

TEST(V3Test, setPaymentCommissioner) {
    ComModel *com = new ComModel();
    com->insertPaymentMethod("testPaymentMethod");
    com->insertCommissioner("testCommissioner");
    com->insertCommissioner("testCommissioner2");
    com->insertPayment(1, 1, "01/01/2001", 10);
    std::vector < const std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >> paymentList;
    paymentList.push_back(std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >(1, 1, 1,
        "01/01/2001", 10, ""));
    EXPECT_EQ(paymentList, com->getPayments());
    paymentList.clear();
    com->setPaymentCommissioner(1, 2);
    paymentList.push_back(std::tuple < const int, const int, const int,
        const std::string, const double, const std::string >(1, 2, 1,
        "01/01/2001", 20, ""));
    EXPECT_EQ(paymentList, com->getPayments());
    paymentList.clear();

    delete com;
}

TEST(V3Test, getPaymentsByCommissioner) {
    ComModel *com = new ComModel();
    com->insertPaymentMethod("testPaymentMethod");
    com->insertPaymentMethod("testPaymentMethod2");
    com->insertCommissioner("testCommissioner");
    com->insertCommissioner("testCommissioner2");
    com->insertPayment(1, 1, "01/01/2001", 10);
    com->insertPayment(2, 2, "02/02/2001", 15, "note stuff");
    com->insertPayment(1, 2, "02/02/2050", 500.05, "more note stuff");
    std::vector < const std::tuple <const int, const int,
        const std::string, const double, const std::string >> paymentList;
    paymentList.push_back(std::tuple <const int, const int,
        const std::string, const double, const std::string >(1, 1,
        "01/01/2001", 10, ""));
    paymentList.push_back(std::tuple <const int, const int,
        const std::string, const double, const std::string >(3, 2,
        "02/02/2050", 15, "more note stuff"));
    EXPECT_EQ(paymentList, com->getPaymentsByCommissioner(1));
    paymentList.clear();

    delete com;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}