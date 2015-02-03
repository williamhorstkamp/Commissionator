#include "ComModel.h"
using namespace Commissionator;

void main(const int argc, const char *argv[]) {
    ComModel *com = new ComModel();
    com->create("wut.db3");
    com->insertContactType("duf");
    com->insertCommissioner("duder");
    com->insertContact("duder", "duf", "entry thing");
    com->close();
    delete com;
}