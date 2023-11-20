//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include <gtest/gtest.h>
#include "../Manager.h"

TEST(Manager, InitTableEntries){

    ClassProject::Manager manager;

    EXPECT_EQ(manager.Table[0].label, "False");
    EXPECT_EQ(manager.Table[0].id, 0);
    EXPECT_EQ(manager.Table[1].label, "True");
    EXPECT_EQ(manager.Table[1].id, 1);
}

TEST(Manager, InitTableSize){

    ClassProject::Manager manager;

    EXPECT_EQ(manager.Table.size(), 2);
}


TEST(Manager, createVar){

    ClassProject::Manager manager;
    ClassProject::BDD_ID ID = manager.createVar("a");

    EXPECT_EQ(manager.Table[2].id, 2);
    EXPECT_EQ(manager.Table[2].id, ID);
    EXPECT_EQ(manager.Table[2].label, "a");
}

TEST(Manager, TrueID){

    ClassProject::Manager manager;
    ClassProject::BDD_ID id = manager.True();

    EXPECT_EQ(id, 1);
}

TEST(Manager, FalseID){

    ClassProject::Manager manager;
    ClassProject::BDD_ID id = manager.False();

    EXPECT_EQ(id, 0);
}

//test isConstant
TEST(Manager,isConstant){
    ClassProject::Manager manager;

    EXPECT_TRUE(manager.isConstant(0));
    EXPECT_TRUE(manager.isConstant(1));
}


//test isVariable function
TEST(Manager,isVar){
    ClassProject::Manager manager;

    EXPECT_FALSE(manager.isVariable(0));
    EXPECT_FALSE(manager.isVariable(1));
    //EXPECT_TRUE(manager.isVariable(2));
    //EXPECT_TRUE(manager.isVariable(3));

}
#endif
