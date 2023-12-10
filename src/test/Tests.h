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
TEST_F(TestManager, CreateVar)
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

/**
 * @brief topVar Test
 *
 */

TEST_F(TestManager, topVar) {

    manager->Table[{2,0,1}] = {"a", 2};
    manager->Table[{3,0,1}] = {"b", 3};
    manager->Table[{4,0,1}] = {"c", 4};
    manager->Table[{5,0,1}] = {"d", 5};
    manager->Table[{2,1,3}] = {"a+b", 6};
    manager->Table[{4,0,5}] = {"c*d", 7};

    EXPECT_EQ(manager->topVar(2), 2);
    EXPECT_EQ(manager->topVar(3), 3);
    EXPECT_EQ(manager->topVar(4), 4);
    EXPECT_EQ(manager->topVar(5), 5);
    EXPECT_EQ(manager->topVar(6), 2);
    EXPECT_EQ(manager->topVar(7), 4);

}

//test ite function
TEST_F(TestManager, ite_terminal_case) {

    manager->Table[{2,0,1}] = {"a", 2};
    manager->Table[{3,0,1}] = {"b", 3};
    manager->Table[{4,0,1}] = {"c", 4};
    manager->Table[{5,0,1}] = {"d", 5};
    manager->Table[{2,1,3}] = {"a+b", 6};
    manager->Table[{4,0,5}] = {"c*d", 7};

    EXPECT_EQ(manager->ite(1, 1, 2) , 1); //Test i==True Cases - Terminal
    EXPECT_EQ(manager->ite(1, 4, 1) , 4); //Test i==True Cases - Not Terminal

    EXPECT_EQ(manager->ite(0, 2, 0) , 0); //Test i==False Case - Terminal
    EXPECT_EQ(manager->ite(0, 4, 2) , 2); //Test i==False Case - Not Terminal

    EXPECT_EQ(manager->ite(4, 1, 0) , 4); //Test Node with 1,0 subnodes

    EXPECT_EQ(manager->ite(2, 1, 3) , 6); //Test Existing node (a+b), not terminal

}

TEST_F(TestManager, ite) {

    manager->Table[{2,0,1}] = {"a", 2};
    manager->Table[{3,0,1}] = {"b", 3};
    manager->Table[{4,0,1}] = {"c", 4};
    manager->Table[{5,0,1}] = {"d", 5};

    EXPECT_EQ(manager->Table.size(),6);

    EXPECT_EQ(manager->ite(2, 3, 0) , 6);

    EXPECT_EQ(manager->ite(4, 5, 0) , 7);

    EXPECT_EQ(manager->ite(6, 1, 7) , 9);

    EXPECT_EQ(manager->Table.size(),10);

    EXPECT_EQ(manager->computed_table.size(),4);
}

/**
* @brief getTopVarName Test
*
*/

TEST_F(TestManager, getTopVarName)
{
    manager->Table[{2,0,1}] = {"a", 2};
    manager->Table[{3,0,1}] = {"b", 3};
    manager->Table[{4,0,1}] = {"c", 4};
    manager->Table[{5,0,1}] = {"d", 5};
    manager->Table[{2,1,3}] = {"a+b", 6};
    manager->Table[{4,0,5}] = {"c*d", 7};

    EXPECT_EQ(manager->getTopVarName(2), "a");
    EXPECT_EQ(manager->getTopVarName(3), "b");
    EXPECT_EQ(manager->getTopVarName(6), "a");
    EXPECT_EQ(manager->getTopVarName(7), "c");

}

TEST_F(TestManager, CoFactorTrue) {

    manager->createVar("a");
    manager->createVar("b");
    manager->createVar("c");
    manager->createVar("d");
    manager->Table[{2,1,3}] = {"a+b", 6}; //TODO: replace with or2 when possible

    EXPECT_EQ(manager->coFactorTrue(0,4), 0); //Terminal Case - f = 0
    EXPECT_EQ(manager->coFactorTrue(1,3), 1); //Terminal Case - f = 1
    EXPECT_EQ(manager->coFactorTrue(0,0), 0); //Terminal Case - x = 0
    EXPECT_EQ(manager->coFactorTrue(5,1), 5); //Terminal Case - x = 1

    EXPECT_EQ(manager->coFactorTrue(6,2), 3); //Case: f.top == x ret f.high

    //Case: if else: ret ite(f_key.TopVar, T, F);
    EXPECT_EQ(manager->coFactorTrue(6,5), manager->ite(2, manager->coFactorTrue(3, 5), manager->coFactorTrue(1,5)));

}

TEST_F(TestManager, CoFactorFalse) {

    manager->createVar("a");
    manager->createVar("b");
    manager->createVar("c");
    manager->createVar("d");
    manager->Table[{2,1,3}] = {"a+b", 6}; //TODO: replace with or2 when possible

    EXPECT_EQ(manager->coFactorFalse(0,4), 0); //Terminal Case - f = 0
    EXPECT_EQ(manager->coFactorFalse(1,3), 1); //Terminal Case - f = 1
    EXPECT_EQ(manager->coFactorFalse(0,0), 0); //Terminal Case - x = 0
    EXPECT_EQ(manager->coFactorFalse(5,1), 5); //Terminal Case - x = 1

    EXPECT_EQ(manager->coFactorFalse(6,2), 1); //Case: f.top == x ret f.low

    //Case: if else: ret ite(f_key.TopVar, T, F);
    EXPECT_EQ(manager->coFactorFalse(6,5), manager->ite(2, manager->coFactorFalse(3, 5), manager->coFactorFalse(1,5)));

}


/**
 * @brief neg Test
 *
 */

TEST_F(TestManager, neg)
{
    manager->Table[{2,0,1}] = {"a", 2};
    manager->Table[{3,0,1}] = {"b", 3};
    manager->Table[{4,0,1}] = {"c", 4};
    manager->Table[{5,0,1}] = {"d", 5};
    manager->Table[{2,1,3}] = {"a+b", 6};
    manager->Table[{4,0,5}] = {"c*d", 7};

    EXPECT_EQ(manager->neg(2), manager->ite(2, 0, 1));
    EXPECT_EQ(manager->neg(6), manager->ite(6, 0, 1));
    EXPECT_EQ(manager->neg(7), manager->ite(7, 0 ,1));
}

/**
 * @brief and2 Test
 *
 */

TEST_F(TestManager, and2)
{
    manager->Table[{2,0,1}] = {"a", 2};
    manager->Table[{3,0,1}] = {"b", 3};
    manager->Table[{4,0,1}] = {"c", 4};
    manager->Table[{5,0,1}] = {"d", 5};
    manager->Table[{2,1,3}] = {"e", 6};
    manager->Table[{4,0,5}] = {"f", 7};

    EXPECT_EQ(manager->and2(2, 3), manager->ite(2, 3, 0));
    EXPECT_EQ(manager->and2(4, 5), manager->ite(4, 5, 0));
    EXPECT_EQ(manager->and2(2, 4), manager->ite(2, 4, 0));
    EXPECT_EQ(manager->and2(6, 7), manager->ite(6, 7 ,0));
}

/**
 * @brief or2 Test
 *
 */

TEST_F(TestManager, or2)
{

    manager->Table[{2,0,1}] = {"a", 2};
    manager->Table[{3,0,1}] = {"b", 3};
    manager->Table[{4,0,1}] = {"c", 4};
    manager->Table[{5,0,1}] = {"d", 5};
    manager->Table[{2,1,3}] = {"e", 6};
    manager->Table[{4,0,5}] = {"f", 7};

    EXPECT_EQ(manager->or2(2, 3), manager->ite(2, 1, 3));
    EXPECT_EQ(manager->or2(4, 5), manager->ite(4, 1, 5));
    EXPECT_EQ(manager->or2(6, 7), manager->ite(6, 1 ,7));
    EXPECT_EQ(manager->or2(6, 7), manager->ite(6, 1 ,7));
}

/**
 * @brief xor2 Test
 *
 */

TEST_F(TestManager, xor2) //ite(a, ~b, b)
{

    manager->Table[{2,0,1}] = {"a", 2};
    manager->Table[{3,0,1}] = {"b", 3};
    manager->Table[{4,0,1}] = {"c", 4};
    manager->Table[{5,0,1}] = {"d", 5};
    manager->Table[{2,1,3}] = {"e", 6};
    manager->Table[{4,0,5}] = {"f", 7};

    EXPECT_EQ(manager->xor2(2, 3), manager->ite(2, manager->neg(3), 3));
    EXPECT_EQ(manager->xor2(4, 5), manager->ite(4, manager->neg(5), 5));
    EXPECT_EQ(manager->xor2(6, 7), manager->ite(6, manager->neg(7) ,7));
}


/**
 * @brief nor2 Test
 *
 */

TEST_F(TestManager, nor2) //ite(a, 0, ~b)
{

    manager->Table[{2,0,1}] = {"a", 2};
    manager->Table[{3,0,1}] = {"b", 3};
    manager->Table[{4,0,1}] = {"c", 4};
    manager->Table[{5,0,1}] = {"d", 5};
    manager->Table[{2,1,3}] = {"e", 6};
    manager->Table[{4,0,5}] = {"f", 7};

    EXPECT_EQ(manager->nor2(2, 3), manager->ite(2, 0, manager->neg(3)));
    EXPECT_EQ(manager->nor2(4, 5), manager->ite(4, 0, manager->neg(5)));
    EXPECT_EQ(manager->nor2(6, 7), manager->ite(6, 0, manager->neg(7)));
}


/**
 * @brief xnor2 Test
 *
 */

TEST_F(TestManager, xnor2) //ite(a, b, ~b)
{
    manager->Table[{2,0,1}] = {"a", 2};
    manager->Table[{3,0,1}] = {"b", 3};
    manager->Table[{4,0,1}] = {"c", 4};
    manager->Table[{5,0,1}] = {"d", 5};
    manager->Table[{2,1,3}] = {"e", 6};
    manager->Table[{4,0,5}] = {"f", 7};

    EXPECT_EQ(manager->xnor2(2, 3), manager->ite(2, 3, manager->neg(3)));
    EXPECT_EQ(manager->xnor2(4, 5), manager->ite(4, 5, manager->neg(5)));
    EXPECT_EQ(manager->xnor2(6, 7), manager->ite(6, 7, manager->neg(7)));
};

#endif
