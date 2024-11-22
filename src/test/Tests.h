//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include <gtest/gtest.h>
#include "../Manager.h"

#endif


#include "Tests.h"

namespace ClassProject {
    class ManagerTest : public testing::Test {  /* NOLINT */
    protected:
        Manager *m;
        BDD_ID a;
        BDD_ID b;
        BDD_ID c;
        BDD_ID d;

        BDD_ID neg_a;
        BDD_ID neg_b;
        BDD_ID a_and_b;
        BDD_ID a_or_b;
        BDD_ID a_xor_b;
        BDD_ID a_nand_b;
        BDD_ID a_nor_b;
        BDD_ID a_xnor_b;
        BDD_ID c_or_d;
        // f1 = a*b+c+d
        BDD_ID f1;

        void SetUp() override {
            m = new Manager();
            a = m->createVar("a");  // ID 2
            b = m->createVar("b");  // ID 3
            c = m->createVar("c");  // ID 4
            d = m->createVar("d");  // ID 5



        }

        void TearDown() override {
            m->~Manager();
        }
    };



    TEST_F(ManagerTest, createVar) {
        EXPECT_EQ(a, 2);
        EXPECT_EQ(b, 3);
        EXPECT_EQ(c, 4);
        EXPECT_EQ(d, 5);
    }


    TEST_F(ManagerTest, True) {
        EXPECT_EQ(m->True(), 1);
    }


    TEST_F(ManagerTest, False) {
        EXPECT_EQ(m->False(), 0);
    }


    TEST_F(ManagerTest, isConstant) {
        EXPECT_EQ(m->isConstant(m->False()), true);
        EXPECT_EQ(m->isConstant(m->True()), true);
        EXPECT_EQ(m->isConstant(a), false);
        EXPECT_EQ(m->isConstant(a_or_b), false);
    }