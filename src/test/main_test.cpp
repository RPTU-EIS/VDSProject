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
//We make sure that the size of the unique table in the BDD manager increases when a new variable is created.
TEST_F(managerTest, UniqueTableSizeIncreasesAfterCreatingVar) {
    ClassProject::BDD_ID testVar1 = manager.createVar("testVar1");
    size_t sizeAfterFirstVar = manager.uniqueTableSize();
    manager.createVar("testVar2");
    //the ASSERT_GT macro is used for comparison testing to assert that the first argument is greater than the second argument
    ASSERT_GT(manager.uniqueTableSize(), sizeAfterFirstVar) << "Unique table size should increase after creating a new variable";
}

//Returns true if the given ID represents a leaf node
TEST_F(managerTest, isconstantTest)
{
    // Create a set of known constant IDs
   /* std::set<ClassProject::BDD_ID> constants = {manager.True(), manager.False()};
    for (ClassProject::BDD_ID i = 0; i < manager.uniqueTableSize(); ++i) {
        if (constants.find(i) != constants.end()) {
            // If 'i' is in the set of known constants, isConstant should return true
            ASSERT_TRUE(manager.isConstant(i)) << "Node with ID " << i << " should be constant";
        } else {
            // If 'i' is not in the set of known constants, isConstant should return false
            ASSERT_FALSE(manager.isConstant(i)) << "Node with ID " << i << " should not be constant";
        }
    }*/
    for (ClassProject::BDD_ID i = 0; i < manager.uniqueTableSize(); ++i)
    {
        bool out = (i == manager.False() || i == manager.True());
        ASSERT_EQ(manager.isConstant(i), out) << "Node with ID " << i << " should be constant";
    }
}

//
TEST_F(managerTest, isvariableTest)
{
    ClassProject::BDD_ID ID_a = manager.createVar("a");
    ClassProject::BDD_ID ID_b = manager.createVar("b");
    ClassProject::BDD_ID ID_c = manager.createVar("c");
    for (ClassProject::BDD_ID i = 0; i < manager.uniqueTableSize(); ++i)
    {
        bool out = (i == ID_a || i == ID_b || i == ID_c);
        ASSERT_EQ(manager.isVariable(i), out) << "Incorrect assertion for isVariable";
    }
}

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
