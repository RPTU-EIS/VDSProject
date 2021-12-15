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

TEST_F(CoFactorsTest,CoFactorTrueSimple){
    EXPECT_EQ(managerTest.coFactorTrue( 0 ), 0);
    EXPECT_EQ(managerTest.coFactorFalse( 1 ), 1);
    for( int i = 1; i < managerTest.uniqueTableSize()-2; i++ )
        EXPECT_EQ(managerTest.coFactorTrue( i ), 1);
    EXPECT_EQ(managerTest.coFactorTrue( 6 ), 1);
    EXPECT_EQ(managerTest.coFactorTrue( 7 ), 5);
}

TEST_F(CoFactorsTest,CoFactorFalseSimple){
    EXPECT_EQ(managerTest.coFactorFalse( 0 ), 0);
    EXPECT_EQ(managerTest.coFactorFalse( 1 ), 1);
    for( int i = 2; i < managerTest.uniqueTableSize()-2; i++ )
        EXPECT_EQ(managerTest.coFactorFalse( i ), 0);
    EXPECT_EQ(managerTest.coFactorFalse( 6 ), 3);
    EXPECT_EQ(managerTest.coFactorFalse( 7 ), 0);
}


TEST_F(CoFactorsTest,CoFactorTrueTwoInputs){
    //Test when f is constant, i is a variable
    for(int i = 2; i < managerTest.uniqueTableSize()-2; i++) {
        EXPECT_EQ(managerTest.coFactorTrue(0, i), 0);
        EXPECT_EQ(managerTest.coFactorTrue(1, i), 1);
    }

    //Test when x is constant, i is a variable
    for(int i = 2; i < managerTest.uniqueTableSize()-2; i++) {
        EXPECT_EQ(managerTest.coFactorTrue(i, 0), i);
        EXPECT_EQ(managerTest.coFactorTrue(i, 1), i);
    }

    //Test when topVar(f) >= x, j is variable
    for(int i = 2; i < managerTest.uniqueTableSize(); i++){
        for( int j = 2; j < managerTest.uniqueTableSize()-2; j++ ){
            if ( managerTest.topVar(i) == j )
                EXPECT_EQ(managerTest.coFactorTrue(i, j), managerTest.unique_table[i].high);
            else if ( managerTest.topVar(i) > j )
                EXPECT_EQ(managerTest.coFactorTrue(i, j), managerTest.unique_table[i].id);
            else
                break;
        }
    }

    //test when it is not a terminal case nor the topVar of F equal to x
    EXPECT_EQ(managerTest.coFactorTrue(6, 3),1);
    EXPECT_EQ(managerTest.coFactorTrue(7, 5),4);

}


TEST_F(CoFactorsTest,CoFactorFalseTwoInputsSimple){
    //Test when f is constant, i is a variable
    for(int i = 2; i < managerTest.uniqueTableSize()-2; i++) {
        EXPECT_EQ(managerTest.coFactorFalse(0, i), 0);
        EXPECT_EQ(managerTest.coFactorFalse(1, i), 1);
    }

    //Test when x is constant, i is a variable
    for(int i = 2; i < managerTest.uniqueTableSize()-2; i++) {
        EXPECT_EQ(managerTest.coFactorFalse(i, 0), i);
        EXPECT_EQ(managerTest.coFactorFalse(i, 1), i);
    }

    //Test when topVar(f) >= x, j is variable
    for(int i = 2; i < managerTest.uniqueTableSize(); i++){
        for( int j = 2; j < managerTest.uniqueTableSize()-2; j++ ){
            if ( managerTest.topVar(i) == j )
                EXPECT_EQ(managerTest.coFactorFalse(i, j), managerTest.unique_table[i].low);
            else if ( managerTest.topVar(i) > j )
                EXPECT_EQ(managerTest.coFactorFalse(i, j), managerTest.unique_table[i].id);
            else
                break;
        }
    }
    //test when it is not a terminal case nor the topVar of F equal to x
    EXPECT_EQ(managerTest.coFactorFalse(6, 3),2);
    EXPECT_EQ(managerTest.coFactorFalse(7, 5),0);
}
TEST_F(IteTest,ITETest){

    //ite of (a+b)
    BDD_ID ite_id_result = managerTest.ite(2,1,3);

    EXPECT_EQ(6,ite_id_result);
    EXPECT_EQ(7,managerTest.uniqueTableSize());
    EXPECT_EQ(1,managerTest.unique_table[managerTest.uniqueTableSize()-1].high);
    EXPECT_EQ(3,managerTest.unique_table[managerTest.uniqueTableSize()-1].low);
    EXPECT_EQ(2,managerTest.unique_table[managerTest.uniqueTableSize()-1].topvar);

    //ite of (c*d)
    ite_id_result =managerTest.ite(4,5,0);

    EXPECT_EQ(7,ite_id_result);
    EXPECT_EQ(8,managerTest.uniqueTableSize());
    EXPECT_EQ(5,managerTest.unique_table[managerTest.uniqueTableSize()-1].high);
    EXPECT_EQ(0,managerTest.unique_table[managerTest.uniqueTableSize()-1].low);
    EXPECT_EQ(4,managerTest.unique_table[managerTest.uniqueTableSize()-1].topvar);

    //ite of ((a+b)*(c*d))
    ite_id_result =managerTest.ite(6,7,0);

    EXPECT_EQ(10,managerTest.uniqueTableSize());

    //check that the node of b*c*d was created correctly
    EXPECT_EQ(8,managerTest.unique_table[managerTest.uniqueTableSize()-2].id);
    EXPECT_EQ(7,managerTest.unique_table[managerTest.uniqueTableSize()-2].high);
    EXPECT_EQ(0,managerTest.unique_table[managerTest.uniqueTableSize()-2].low);
    EXPECT_EQ(3,managerTest.unique_table[managerTest.uniqueTableSize()-2].topvar);

    //check that the node of the Output was created correctly
    EXPECT_EQ(9,ite_id_result);
    EXPECT_EQ(7,managerTest.unique_table[managerTest.uniqueTableSize()-1].high);
    EXPECT_EQ(8,managerTest.unique_table[managerTest.uniqueTableSize()-1].low);
    EXPECT_EQ(2,managerTest.unique_table[managerTest.uniqueTableSize()-1].topvar);



}

TEST_F(IteTest,checkExistanceTest){

    EXPECT_EQ(2,managerTest.checkExistance(1,0,2));
    EXPECT_EQ(0,managerTest.checkExistance(1,3,2));
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
