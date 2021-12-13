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
    Manager managerTest;

    managerTest.createVar("a");
    managerTest.createVar("b");
    managerTest.createVar("c");
    managerTest.createVar("d");
    managerTest.createVar("a");
    managerTest.createVar("b");

    managerTest.printUniqueTable();
}
