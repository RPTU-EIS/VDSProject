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

// Test that the True and False nodes exist and have correct properties
TEST_F(managerTest, TrueAndFalseNodes) {
    // Obtain the IDs of the True and False nodes
    ClassProject::BDD_ID trueNode = manager.True();
    ClassProject::BDD_ID falseNode = manager.False();

    // Test that the True node has the expected properties
    ASSERT_EQ(manager.topVar(trueNode), trueNode) << "Top variable of True node should be itself";
    ASSERT_EQ(manager.getLabel( manager.True()), "True") << "Label of True node should be 'True'";

    // Test that the False node has the expected properties
    ASSERT_EQ(manager.topVar(falseNode), falseNode) << "Top variable of False node should be itself";
    ASSERT_EQ(manager.getLabel(manager.False()), "False") << "Label of False node should be 'False'";

    // Test that the True and False nodes are different
    ASSERT_NE(trueNode, falseNode) << "True and False node IDs should be different";
}

TEST_F(managerTest, CreateVarTest) {


    ClassProject::BDD_ID ID_a = manager.createVar("a");
    ClassProject::BDD_ID ID_b = manager.createVar("b");
    ClassProject::BDD_ID ID_c = manager.createVar("c");

    EXPECT_EQ(ID_a, 2);
    EXPECT_EQ(ID_b, 3);
    EXPECT_EQ(ID_c, 4);
}
//TEST_F(managerTest, )

/*TEST_F(managerTest, CreateNodeTest) {


    ClassProject::BDD_ID ID_a = manager.createNode(0, 1, 2, "a");

    EXPECT_EQ(manager.uniqueTableSize(), 3);
    EXPECT_EQ(manager.uniqueTableMap.size(), 3);
    EXPECT_EQ(ID_a, 2);

}



TEST_F(managerTest, keyGenTest) {


    size_t d = manager.keyGen(1,1,1);

    EXPECT_EQ(d, 2);
    //EXPECT_EQ(ID_b, 3);

}*/


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
