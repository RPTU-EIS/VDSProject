#include "Tests.h"

using namespace ClassProject;

/// Manager Constructor TESTS:
TEST_F(constructorTest, constructor_sizeok){

    BDD_ID table_size = managerTest.unique_table.size();
    EXPECT_EQ(2,table_size);
}

/// UniqueTableSize Function TESTS:
TEST_F(TableSizeTest, uniqueTableSize_sizeok){
    BDD_ID table_size = managerTest.uniqueTableSize();
    EXPECT_EQ(2,table_size);
}

/// CreateVar Function TESTS:
TEST_F(UniqueTableTests, createVar_sizeok){

    BDD_ID table_size = managerTest.uniqueTableSize();
    EXPECT_EQ(6,table_size);
}
/// CreateVar Function TESTS:
TEST_F(UniqueTableTests, createVar_itemsok){
    for (int i = 0; i < 6; i++)
        EXPECT_EQ(i,managerTest.unique_table[i].id);
}

/// False Node Function TESTS:
TEST_F(UniqueTableTests, false_node_found){
    ASSERT_EQ(0,managerTest.False());
}
/// True Node Function TESTS:
TEST_F(UniqueTableTests, true_node_found){

    ASSERT_EQ(1,managerTest.True());
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
