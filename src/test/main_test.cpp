//
// Created by ludwig on 22.11.16.
//
#include <gtest/gtest.h>
#include "Manager.h"  // Include the header file for your Manager class


class managerTest : public ::testing::Test
{
protected:
    ClassProject::Manager manager;
    // This function will be called before each test
    void SetUp() override {
        // Initialize any test-specific resources
    }

    // This function will be called after each test
    void TearDown() override {
        // Clean up any test-specific resources
    }
};

TEST_F(ManagerTest, CreateNodeTest) {


    ClassProject::BDD_ID ID_a = manager.createNode(0, 1, 2, "a");

    EXPECT_EQ(manager.uniqueTableSize(), 3);
    EXPECT_EQ(manager.uniqueTableMap.size(), 3);
    EXPECT_EQ(ID_a, 2);

}

TEST_F(ManagerTest, CreateVarTest) {


    ClassProject::BDD_ID ID_a = manager.createVar("a");
    ClassProject::BDD_ID ID_b = manager.createVar("b");

    EXPECT_EQ(ID_a, 2);
    EXPECT_EQ(ID_b, 3);

}

TEST_F(ManagerTest, keyGenTest) {


    size_t d = manager.keyGen(1,1,1);

    EXPECT_EQ(d, 2);
    //EXPECT_EQ(ID_b, 3);

}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
