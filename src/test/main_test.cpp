//
// Created by ludwig on 22.11.16.
//
#include <gtest/gtest.h>
#include "Manager.h"  // Include the header file for your Manager class


class managerTest : public ::testing::Test
{
protected:
    ClassProject::Manager manager;
    ClassProject::BDD_ID a,b,c;
    // This function will be called before each test
    void SetUp() override {
        // Initialize any test-specific resources
        //SetUp initializes the BDD manager and creates three variables a, b, and c.
        a = manager.createVar("a");
        b = manager.createVar("b");
        c = manager.createVar("c");
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

TEST_F(managerTest, CreateVarandUniqueTable) {

/*
    ClassProject::BDD_ID ID_a = manager.createVar("a");
    ClassProject::BDD_ID ID_b = manager.createVar("b");
    ClassProject::BDD_ID ID_c = manager.createVar("c");
*/
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 3);
    EXPECT_EQ(c, 4);
}
//We make sure that the size of the unique table in the BDD manager increases when a new variable is created.
TEST_F(managerTest, UniqueTableSizeIncreasesAfterCreatingVar) {
    ClassProject::BDD_ID testVar1 = manager.createVar("testVar1");
    size_t sizeAfterFirstVar = manager.uniqueTableSize();
    manager.createVar("testVar2");
    //the ASSERT_GT macro is used for comparison testing to assert that the first argument is greater than the second argument
    ASSERT_GT(manager.uniqueTableSize(), sizeAfterFirstVar) << "Unique table size should increase after creating a new variable";
}
/*
TEST_F(managerTest, CreateNodeTest) {


    ClassProject::BDD_ID ID_a = manager.createNode(0, 1, 2, "a");

    EXPECT_EQ(manager.uniqueTableSize(), 3);
    EXPECT_EQ(manager.uniqueTableMap.size(), 3);
    EXPECT_EQ(ID_a, 2);

}*/

//Returns true if the given ID represents a leaf node
TEST_F(managerTest, isconstantTest)
{
    // Create a set of known constant IDs
    //size_t tableSize = manager.uniqueTableSize();
    for (ClassProject::BDD_ID i = 0; i < manager.uniqueTableSize(); ++i)
    {
        // a boolean variable out is declared and set to true if the current i is equal to the ID of the False node or the True node in the manager's unique table.
        bool out = (i == manager.False() || i == manager.True());
        //If the assertion fails, it outputs the message "Node with ID [i] should be constant".
        ASSERT_EQ(manager.isConstant(i), out) << "Node with ID " << i << " should be constant";
    }
}

TEST_F(managerTest, isvariableTest)
{
    for (ClassProject::BDD_ID i = 0; i < manager.uniqueTableSize(); ++i)
    {
        // a boolean variable out is declared and set to true if the current i is equal to the ID of the variables we declared up there.
        bool out = (i == a || i == b || i == c);
        //If the assertion fails, it outputs the message "Node with ID [i] should be a variable".
        ASSERT_EQ(manager.isVariable(i), out) << "Node with ID " << i << " should be a variable";
    }

}


/*


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
