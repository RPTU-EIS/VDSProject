//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include <gtest/gtest.h>
#include "../Manager.h"

/**
 * @brief TestManager Class
 *
 */
class TestManager : public testing::Test
{
protected:
    /**
     * @brief Set the Up object
     *
     */
    void SetUp() override
    {
        manager = new ClassProject::Manager;
    }

    /**
     * @brief Deletes manager
     *
     */
    void TearDown() override
    {
        delete manager;
    }

    ClassProject::Manager *manager;
};

/**
 * @brief InitTableEntries Test
 *
 */
TEST_F(TestManager, InitTableEntries)
{
    ClassProject::Manager::Unique_Table_Key key = {0, 0, 0};

    EXPECT_EQ(manager->Table[key].id, 0);

    key = {1, 1, 1};
    EXPECT_EQ(manager->Table[key].id, 1);
}

/**
 * @brief InitTableSize Test
 *
 */
TEST_F(TestManager, InitTableSize)
{

    EXPECT_EQ(manager->Table.size(), 2);
}

/**
 * @brief CreateVar Test
 *
 */
TEST_F(TestManager, createVar)
{

    ClassProject::BDD_ID ID = manager->createVar("a");
    EXPECT_EQ(ID, 2);
    // EXPECT_EQ(manager.Table[2].id, ID);
    // EXPECT_EQ(manager.Table[2].label, "a");
}

/**
 * @brief TrueID Test
 *
 */
TEST_F(TestManager, TrueID)
{
    ClassProject::BDD_ID id = manager->True();

    EXPECT_EQ(id, 1);
}

/**
 * @brief FalseID Test
 *
 */
TEST_F(TestManager, FalseID)
{

    ClassProject::BDD_ID id = manager->False();

    EXPECT_EQ(id, 0);
}

/**
 * @brief isConstant Test
 *
 */
TEST_F(TestManager, isConstant)
{
    EXPECT_TRUE(manager->isConstant(0));
    EXPECT_TRUE(manager->isConstant(1));
}

/**
 * @brief isVariable Test
 *
 */
TEST_F(TestManager, isVar)
{
    manager->Table[{2, 0, 1}] = {"a", 2};
    manager->Table[{3, 0, 1}] = {"ab", 3};

    EXPECT_FALSE(manager->isVariable(0));
    EXPECT_FALSE(manager->isVariable(1));
    EXPECT_TRUE(manager->isVariable(2));
    EXPECT_FALSE(manager->isVariable(3));
}

#endif
