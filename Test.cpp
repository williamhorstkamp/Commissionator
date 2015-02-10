#include "ComModel.h"
#include <iostream>

using namespace Commissionator;

void main(const int argc, const char *argv[]) {
    ComModel *com = new ComModel();
    com->insertContactType("duf");
    com->insertContactType("asd");
    com->setContactTypeName(1, "wud");

    com->insertCommissioner("duder");
    com->setCommissionerName(1, "rudeboy");
    com->insertCommissioner("fugbro");
    com->insertCommissioner("whatsit");

    com->insertContact(1, 1, "entry thing");

    com->insertProduct("art", 5.0);
    com->insertProduct("not art", 2.0);
    com->setProductName(2, "still not art");
    com->setProductPrice(2, 1.0);

    com->insertCommission("01/01/2001", "05/05/2005");
    com->setCommissionDueDate(1, "06/06/2006");
    com->setCommissionPaidDate(1, "05/05/2005");

    com->insertPiece(1, 1);
    com->setPieceDescription(1, "a thing");
    com->insertPiece(1, 2, "another thing");

    auto comList = com->getCommissioners();
    for (auto it = comList.begin(); it != comList.end(); it++) {
        std::cout << std::get<0>(*it) << "\t" << std::get<1>(*it) << std::endl;
    }
    comList.clear();
    std::vector<const std::tuple<const int, const std::string>>().swap(comList);
    std::cout << std::endl;

    std::cout << com->getCommissioner(1) << std::endl;
    std::cout << std::endl;

    auto conTypeList = com->getContactTypes();
    for (auto it = conTypeList.begin(); it != conTypeList.end(); it++) {
        std::cout << std::get<0>(*it) << "\t" << std::get<1>(*it) << std::endl;
    }
    conTypeList.clear();
    std::vector<const std::tuple<const int, const std::string>>().swap(conTypeList);
    std::cout << std::endl;

    std::cout << com->getContactType(1) << std::endl;
    std::cout << std::endl;

    com->setContactType(1, 2);
    com->setContactEntry(1, "howsitwhatsitfinder");

    auto conList = com->getContacts(1);
    for (auto it = conList.begin(); it != conList.end(); it++) {
        std::cout << std::get<0>(*it) << "   " << std::get<1>(*it) << "   " << std::get<2>(*it) << std::endl;
    }
    conList.clear();
    std::vector<const std::tuple<const int, const  int, const std::string>>().swap(conList);
    std::cout << std::endl;

    std::tuple<int, int, std::string> contact = com->getContact(1);
    std::cout << std::get<0>(contact) << std::get<1>(contact) << std::get<2>(contact) << std::endl;
    
    auto proList = com->getProducts();
    for (auto it = proList.begin(); it != proList.end(); it++) {
        std::cout << std::get<0>(*it) << "\t" << std::get<1>(*it) << std::get<2>(*it) << std::endl;
    }
    proList.clear();
    std::vector<const std::tuple<const int, const std::string>>().swap(comList);
    std::cout << std::endl;
   
    std::tuple<std::string, double> product = com->getProduct(0);
    std::cout << std::get<0>(product) << std::get<1>(product) << std::endl;

    auto pieList = com->searchPieces("thing");
    for (auto it = pieList.begin(); it != pieList.end(); it++) {
        std::cout << std::get<0>(*it) << "\t" << std::get<1>(*it) << "\t" << std::get<2>(*it) << "\t" << std::get<3>(*it) << std::endl;
    }
    comList.clear();
    std::vector<const std::tuple<const int, const std::string>>().swap(comList);
    std::cout << std::endl;

    com->save("wut.db3");


    std::cin.get();
    com->close();
    delete com;
}