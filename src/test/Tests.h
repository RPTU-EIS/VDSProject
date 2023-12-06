//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include "Manager.h"
#include <vector>
#include <gtest/gtest.h>


namespace ClassProject {
    // class Managertest : public testing::Test {
    // protected:

    //     ClassProject::Manager lectureExample;

    //     void SetUp() override {
    //         lectureExample.nodes = {
    //             ClassProject::Manager::FALSE_NODE,
    //             ClassProject::Manager::TRUE_NODE
    //         };
    //     }

    // };

    // TEST_F(Managertest, VisualizeBDDTest) {
    //     lectureExample.visualizeBDD("", (const BDD_ID) lectureExample.nodes.size()-1);
    // }

    class BasicTest : public testing::Test {

        protected:

        Manager testObj;

        void SetUp() override {
            testObj = Manager();
            // testObj.nodes = {
            //     {.label = "0", .data = {.low = 0, .high = 0, .topVar = 0}}                
            //     {.label = "0", .data = {.low = 0, .high = 0, .topVar = 0}}
            // };
        }
    };

    TEST_F(BasicTest, Constructor){
        Node exp_true =  {.label = "1", .data = {.low = 1, .high = 1, .topVar = 1}};
        Node exp_false = {.label = "0", .data = {.low = 0, .high = 0, .topVar = 0}};
        ASSERT_EQ(testObj.nodes[0], exp_false);
        ASSERT_EQ(testObj.nodes[1], exp_true);
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

        Node exp_a = {.label = "a", .data = {.low = 0, .high = 1, .topVar = 2}};
        Node exp_b = {.label = "b", .data = {.low = 0, .high = 1, .topVar = 3}};
        Node exp_c = {.label = "c", .data = {.low = 0, .high = 1, .topVar = 4}};

        BDD_ID id_a = testObj.createVar("a");
        BDD_ID id_b = testObj.createVar("b");
        BDD_ID id_c = testObj.createVar("c");

        ASSERT_EQ(id_a, 2);
        ASSERT_EQ(id_b, 3);
        ASSERT_EQ(id_c, 4);

        ASSERT_EQ(testObj.nodes[id_a], exp_a);
        ASSERT_EQ(testObj.nodes[id_b], exp_b);
        ASSERT_EQ(testObj.nodes[id_c], exp_c);        
    }

    TEST_F(BasicTest, CreateVarDuplicate){        
        Node exp_a = {.label = "a", .data = {.low = 0, .high = 1, .topVar = 2}};
        BDD_ID id1 = testObj.createVar("a");
        BDD_ID id2 = testObj.createVar("a");
        ASSERT_EQ(id1, id2);        
        ASSERT_EQ(testObj.nodes[id1], exp_a);
    }
}

#endif