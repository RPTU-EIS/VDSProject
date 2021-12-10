#include "Tests.h"

using namespace ClassProject;

TEST_F(UniqueTableTests, constructor_sizeok){

    BDD_ID table_size = managerTest.unique_table.size();
    EXPECT_EQ(2,table_size);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
