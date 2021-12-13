//
// Created by Carolina P. Nogueira 2016
//

#include <iostream>
#include <string>
#include "Manager.h"

using namespace ClassProject;

int main(int argc, char* argv[])
{
    std::cout << "Something implemented, already" << std::endl;
    Manager managerTest2;

    managerTest2.createVar("a");
    managerTest2.createVar("b");
    managerTest2.createVar("c");
    managerTest2.createVar("d");
    managerTest2.createVar("a");
    managerTest2.createVar("b");

    managerTest2.printUniqueTable();
}
