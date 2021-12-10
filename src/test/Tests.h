//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include "gtest/gtest.h"
#include "../Manager.h"
#include "BDD_node.h"

using namespace ClassProject;

class constructorTest : public testing::Test {
public:

    Manager managerTest;

};

class TableSizeTest : public testing::Test {
public:

    Manager managerTest;

};

class UniqueTableTests : public testing::Test {
public:

    Manager managerTest;

    void SetUp() override{
        managerTest.createVar("a");
        managerTest.createVar("b");
        managerTest.createVar("c");
        managerTest.createVar("d");
        managerTest.createVar("a");
        managerTest.createVar("b");
    }
};

#endif
