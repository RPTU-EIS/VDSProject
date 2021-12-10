#include "Tests.h"

using namespace ClassProject;

TEST_F(UniqueTableTests, constructor_sizeok){

    BDD_ID table_size = managerTest.unique_table.size();
    EXPECT_EQ(2,table_size);
}

TEST_F(UniqueTableTests, uniqueTableSize_sizeok){
    BDD_ID table_size = managerTest.uniqueTableSize();
    EXPECT_EQ(2,table_size);
}

TEST_F(UniqueTableTests, createVar_sizeok){

    BDD_ID table_size = managerTest.uniqueTableSize();
    EXPECT_EQ(5,table_size);
}

TEST_F(UniqueTableTests, createVar_itemsok){
    for (int i = 0; i < 6; i++)
        EXPECT_EQ(i,managerTest.unique_table[i].id);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
