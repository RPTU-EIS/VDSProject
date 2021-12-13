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
    EXPECT_EQ(0,managerTest.False());
}

/// True Node Function TESTS:
TEST_F(UniqueTableTests, true_node_found){
    EXPECT_EQ(1,managerTest.True());
}

/// Top Variable Function TESTS:
TEST_F(UniqueTableTests, top_variable_of_variables){
    for( BDD_ID i = 2; i < managerTest.uniqueTableSize(); i++ )
        EXPECT_EQ(managerTest.topVar(i), i);
}

/// IsConstant Function TESTS:
TEST_F(UniqueTableTests, is_constant){
    BDD_ID id[5]={0,1,2,3,4};
    bool result_exp[5]={true,true,false,false,false};
    for (int i=0;i<5;i++){
        EXPECT_EQ(result_exp[i],managerTest.isConstant(id[i]));
    }
}

TEST_F(UniqueTableTests, is_variable){
    BDD_ID a[6]={0,1,2,3,4,5};
    bool result_exp[6]={false,false,true,true,true,true};
    for(int i=2;i<6;i++) {
        ASSERT_EQ(result_exp[i], managerTest.isVariable(a[i]));
    }
}

TEST_F(UniqueTableTests, getTopVarName_test){
    BDD_ID a[6]={0,1,2,3,4,5};
    std::string result_exp[6]={"False","True","a","b","c","d"};
    for(int i=0;i<6;i++) {
        ASSERT_EQ(result_exp[i], managerTest.getTopVarName(a[i]));
    }
}

TEST_F(RecursiveTest1,FindNode_test){
    std::set<BDD_ID> a={};
    BDD_ID result_exp[4]={4,1,3,0};
    managerTest.findNodes(4, (std::set<BDD_ID> &) a);
    for(int i=0;i<4;i++) {
        ASSERT_NE(a.end(),a.find(result_exp[i]));
    }

}
TEST_F(RecursiveTest1,FindVars_test){
    std::set<BDD_ID> a={};
    BDD_ID result_exp[2]={2,3};
    managerTest.findVars(4, (std::set<BDD_ID> &) a);
    for(int i=0;i<2;i++) {
        ASSERT_NE(a.end(),a.find(result_exp[i]));
    }

}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
