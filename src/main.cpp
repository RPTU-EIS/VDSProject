//
// Created by Carolina P. Nogueira 2016
//

// #include <iostream>
// #include <string>
// #include "Manager.h"
// #include <memory>

#include "test/Tests.h"

int main(int argc, char* argv[])
{
    // std::cout << "Hello world :)" << std::endl;
    // using namespace ClassProject;
    //
    // std::unique_ptr<Manager> m;
    // m = std::make_unique<Manager>();
    //
    // BDD_ID a = m->createVar("a");
    // BDD_ID b = m->createVar("b");
    // BDD_ID c = m->createVar("c");
    // BDD_ID d = m->createVar("d");
    //
    // BDD_ID e = m->or2(a, b);
    // BDD_ID f = m->and2(c, d);
    // BDD_ID g = m->and2(f,e);
    //
    // BDD_ID test = m->and2(a, b);
    // m->visualizeBDD("Test.dot", test);
    //
    // m->visualizeBDD("ROBDD.dot", g);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
