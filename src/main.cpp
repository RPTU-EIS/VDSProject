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

    std::string label_a_or_b="a+b";
    managerTest2.addNode(6,1 ,3, 2,label_a_or_b);
    std::string label_c_and_d="c*d";
    managerTest2.addNode(7,5 ,0, 4,label_c_and_d);

    managerTest2.printUniqueTable();
}
