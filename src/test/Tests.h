//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include "Manager.h"
#include <vector>
#include <gtest/gtest.h>


namespace ClassProject {

    class BasicTest : public testing::Test {

        protected:

        Manager testObj;

        void SetUp() override {
            testObj = Manager();
        }
    };

    class FunctionsTest : public testing::Test {

        protected:

        Manager testObj;

        void SetUp() override {
            testObj = Manager({
                {.label = "0",   .data = {.low = 0, .high = 0, .topVar = 0}},                
                {.label = "1",   .data = {.low = 1, .high = 1, .topVar = 1}},
                {.label = "a",   .data = {.low = 0, .high = 1, .topVar = 2}},
                {.label = "b",   .data = {.low = 0, .high = 1, .topVar = 3}},
                {.label = "c",   .data = {.low = 0, .high = 1, .topVar = 4}},
                {.label = "d",   .data = {.low = 0, .high = 1, .topVar = 5}},
                {.label = "a+b", .data = {.low = 1, .high = 3, .topVar = 2}},
                {.label = "c*d", .data = {.low = 5, .high = 0, .topVar = 4}}
            });           
        }
    };

    TEST_F(BasicTest, Constructor){        
        // false node
        ASSERT_EQ(testObj.low(0),    0);
        ASSERT_EQ(testObj.high(0),   0);
        ASSERT_EQ(testObj.topVar(0), 0);

        // true node
        ASSERT_EQ(testObj.low(1),    1);
        ASSERT_EQ(testObj.high(1),   1);
        ASSERT_EQ(testObj.topVar(1), 1);
    }

    TEST_F(BasicTest, FalseReturn){
        BDD_ID id_false = testObj.False();      
        ASSERT_EQ(id_false, 0);   
    }

    TEST_F(BasicTest, TrueReturn){
        BDD_ID id_true = testObj.True();
        ASSERT_EQ(id_true, 1);        
    }

    TEST_F(BasicTest, CreateVarNew){        
        BDD_ID id_a = testObj.createVar("a");
        BDD_ID id_b = testObj.createVar("b");        

        // node a
        ASSERT_EQ(testObj.low(id_a),    0);
        ASSERT_EQ(testObj.high(id_a),   1);
        ASSERT_EQ(testObj.topVar(id_a), id_a);    

        // node b
        ASSERT_EQ(testObj.low(id_b),    0);
        ASSERT_EQ(testObj.high(id_b),   1);
        ASSERT_EQ(testObj.topVar(id_b), id_b);    
    }

    TEST_F(BasicTest, CreateVarDuplicate){                
        BDD_ID id1 = testObj.createVar("a");
        BDD_ID id2 = testObj.createVar("a");

        ASSERT_EQ(testObj.low(id1),    0);
        ASSERT_EQ(testObj.high(id1),   1);
        ASSERT_EQ(testObj.topVar(id1), id1); 
        
        ASSERT_EQ(id1, id2);                
    }

    TEST_F(FunctionsTest, Constant){
        ASSERT_EQ(testObj.isConstant(0), true);  // false node
        ASSERT_EQ(testObj.isConstant(1), true);  // true node
        ASSERT_EQ(testObj.isConstant(2), false); // variable node (a)
        ASSERT_EQ(testObj.isConstant(6), false); // function node (a+b)
    }

    TEST_F(FunctionsTest, Variable){
        ASSERT_EQ(testObj.isVariable(0), false);  // false node
        ASSERT_EQ(testObj.isVariable(1), false);  // true node
        ASSERT_EQ(testObj.isVariable(2), true);   // variable node (a)
        ASSERT_EQ(testObj.isVariable(3), true);   // variable node (b)
        ASSERT_EQ(testObj.isVariable(6), false);  // function node (a+b)
    }

    TEST_F(FunctionsTest, IteTerminalCases){
        BDD_ID id_a = 2, id_b = 3;
        ASSERT_EQ(testObj.ite(1, id_a, id_b),    id_a);
        ASSERT_EQ(testObj.ite(0, id_a, id_b),    id_b);
        ASSERT_EQ(testObj.ite(id_a, 1, 0),       id_a);
        ASSERT_EQ(testObj.ite(id_a, id_b, id_b), id_b);
    }

    TEST_F(FunctionsTest, IteVariables){
        BDD_ID id_a = 2, id_b = 3, id_c = 4;        

        BDD_ID id_n = testObj.ite(id_a, id_b, id_c);        
        ASSERT_EQ(testObj.low(id_n),    id_c);
        ASSERT_EQ(testObj.high(id_n),   id_b);
        ASSERT_EQ(testObj.topVar(id_n), id_a); 
    }
}

#endif