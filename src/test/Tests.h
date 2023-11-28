//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include <gtest/gtest.h>
#include "../Manager.h"

// The fixture for testing class TestManager.
class TestManager : public testing::Test {
protected:

//    TestManager() {
//
//    }
//
//    ~TestManager() override {
//
//    }

    void SetUp() override {
        manager = new ClassProject::Manager;
    }

    void TearDown() override {
        delete manager;
    }

    ClassProject::Manager *manager;
};


TEST_F(TestManager, InitTableEntries){
    ClassProject::Manager::Unique_Table_Key key = {0,0,0};

    EXPECT_EQ(manager->Table[key].id, 0);

    key = {1,1,1};
    EXPECT_EQ(manager->Table[key].id, 1);
}

TEST_F(TestManager, InitTableSize){

    EXPECT_EQ(manager->Table.size(), 2);
}


TEST_F(TestManager, createVar){

    ClassProject::BDD_ID ID = manager->createVar("a");
    EXPECT_EQ(ID, 2);
    // EXPECT_EQ(manager.Table[2].id, ID);
    // EXPECT_EQ(manager.Table[2].label, "a");
}

TEST_F(TestManager, TrueID){
    ClassProject::BDD_ID id = manager->True();

    EXPECT_EQ(id, 1);
}

TEST_F(TestManager, FalseID){

    ClassProject::BDD_ID id = manager->False();

    EXPECT_EQ(id, 0);
}

// test isConstant
TEST_F(TestManager, isConstant){
    EXPECT_TRUE(manager->isConstant(0));
    EXPECT_TRUE(manager->isConstant(1));
}


//test isVariable function
 TEST_F(TestManager,isVar){
    manager->Table[{2,0,1}] = {"a", 2};
    manager->Table[{3,0,1}] = {"ab", 3};

   EXPECT_FALSE(manager->isVariable(0));
   EXPECT_FALSE(manager->isVariable(1));
   EXPECT_TRUE(manager->isVariable(2));
   EXPECT_FALSE(manager->isVariable(3));
}

//test topVariable function
TEST_F(TestManager, topVar) {

    manager->Table[{2,0,1}] = {"a", 2};
    manager->Table[{3,0,1}] = {"b", 3};
    manager->Table[{4,0,1}] = {"c", 4};
    manager->Table[{5,0,1}] = {"d", 5};
    manager->Table[{2,1,3}] = {"a+b", 6};
    manager->Table[{4,0,5}] = {"c*d", 7};

    EXPECT_EQ(manager->topVar(2), 2);
    EXPECT_EQ(manager->topVar(3), 3);
    EXPECT_EQ(manager->topVar(4), 4);
    EXPECT_EQ(manager->topVar(5), 5);
    EXPECT_EQ(manager->topVar(6), 2);
    EXPECT_EQ(manager->topVar(7), 4);

}
#endif
