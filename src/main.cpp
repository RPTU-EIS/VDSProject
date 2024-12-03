//
// Created by Carolina P. Nogueira 2016
//

#include <iostream>
#include <string>
#include "Manager.h"

int main(int argc, char* argv[])
{
    std::cout << "Hello world :)" << std::endl;
    using namespace ClassProject;
    Manager m = Manager();

    BDD_ID a = m.createVar("a");
    BDD_ID b = m.createVar("b");
    BDD_ID c = m.createVar("c");
    BDD_ID d = m.createVar("d");

    BDD_ID f = m.and2(m.or2(a, b), m.and2(c, d));

    m.visualizeBDD("ROBDD.dot", f);
}
