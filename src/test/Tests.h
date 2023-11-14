//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include <gtest/gtest.h>
#include "../Manager.h"

TEST(ManagerInterface, InitTableEntries){

    ClassProject::ManagerInterface manager;

    EXPECT_EQ(manager.Table[0].label, "False");
    EXPECT_EQ(manager.Table[0].id, 0);
    EXPECT_EQ(manager.Table[1].label, "True");
    EXPECT_EQ(manager.Table[1].id, 1);
}

TEST(ManagerInterface, InitTableSize){

    ClassProject::ManagerInterface manager;

    EXPECT_EQ(manager.Table.size(), 2);
}

TEST(ManagerInterface, TrueID){

    ClassProject::ManagerInterface manager;
    ClassProject::BDD_ID id = manager.True();

    EXPECT_EQ(id, 1);
}

TEST(ManagerInterface, FalseID){

    ClassProject::ManagerInterface manager;
    ClassProject::BDD_ID id = manager.False();

    EXPECT_EQ(id, 0);
}

#endif
