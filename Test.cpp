#include "ComModel.h"
#include <iostream>

using namespace Commissionator;

void main(const int argc, const char *argv[]) {
    ComModel *com = new ComModel();
    com->create("wut.db3");
    com->insertContactType("duf");
    com->insertContactType("asd");
    com->renameContactType(1, "wud");
    com->insertCommissioner("duder");
    com->renameCommissioner(1, "rudeboy");
    com->insertCommissioner("fugbro");
    com->insertCommissioner("whatsit");
    com->insertContact(1, 1, "entry thing");
    std::vector<std::tuple<int, std::string>> comList = com->getCommissioners();
    for (auto it = comList.begin(); it != comList.end(); it++) {
        std::cout << std::get<0>(*it) << "\t" << std::get<1>(*it) << std::endl;
    }
    comList.clear();
    std::vector<std::tuple<int, std::string>>().swap(comList);
    std::cout << std::endl;
    std::cout << com->getCommissioner(1) << std::endl;
    std::cout << std::endl;

    std::vector<std::tuple<int, std::string>> conTypeList = com->getContactTypes();
    for (auto it = conTypeList.begin(); it != conTypeList.end(); it++) {
        std::cout << std::get<0>(*it) << "\t" << std::get<1>(*it) << std::endl;
    }
    conTypeList.clear();
    std::vector<std::tuple<int, std::string>>().swap(conTypeList);
    std::cout << std::endl;
    std::cout << com->getContactType(1) << std::endl;
    std::cout << std::endl;

    com->editContactType(1, 2);
    com->editContactEntry(1, "howsitwhatsitfinder");

    std::vector<std::tuple<int, int, std::string>> conList = com->getContacts(1);
    for (auto it = conList.begin(); it != conList.end(); it++) {
        std::cout << std::get<0>(*it) << "   " << std::get<1>(*it) << "   " << std::get<2>(*it) << std::endl;
    }
    conList.clear();
    std::vector<std::tuple<int, int, std::string>>().swap(conList);
    std::cout << std::endl;

    std::tuple<int, int, std::string> contact = com->getContact(1);
    std::cout << std::get<0>(contact) << std::get<1>(contact) << std::get<2>(contact) << std::endl;

    std::cin.get();
    com->close();
    delete com;
}