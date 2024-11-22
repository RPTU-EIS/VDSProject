//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include <gtest/gtest.h>
#include "../Manager.h"

using namespace ClassProject;

class ManagerTest : public testing::Test {
    protected:
        Manager *m;
        BDD_ID a;
        BDD_ID b;
        BDD_ID c;
        BDD_ID d;

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
        EXPECT_EQ(m->isConstant(m->False()), TrueId);
        EXPECT_EQ(m->isConstant(m->True()), TrueId);
        EXPECT_EQ(m->isConstant(a), FalseId);
        EXPECT_EQ(m->isConstant(b), FalseId);
        EXPECT_EQ(m->isConstant(c), FalseId);
        EXPECT_EQ(m->isConstant(d), FalseId);
    }

    TEST_F(ManagerTest, variable_recognition) {
        EXPECT_EQ(m->isVariable(a), TrueId);
        EXPECT_EQ(m->isVariable(b), TrueId);
        EXPECT_EQ(m->isVariable(c), TrueId);
        EXPECT_EQ(m->isVariable(d), TrueId);

        EXPECT_EQ(m->isVariable(m->False()), FalseId);
        EXPECT_EQ(m->isVariable(m->True()), FalseId);
    }

    TEST_F(ManagerTest, and2_function) {
        // truth table
        EXPECT_EQ(m->and2(m->False(), m->False()), FalseId);
        EXPECT_EQ(m->and2(m->False(), m->True()), FalseId);
        EXPECT_EQ(m->and2(m->True(), m->False()), FalseId);
        EXPECT_EQ(m->and2(m->True(), m->True()), TrueId);
    }

    TEST_F(ManagerTest, or2_function) {
        // truth table
        EXPECT_EQ(m->or2(m->False(), m->False()), FalseId);
        EXPECT_EQ(m->or2(m->False(), m->True()), TrueId);
        EXPECT_EQ(m->or2(m->True(), m->False()), TrueId);
        EXPECT_EQ(m->or2(m->True(), m->True()), TrueId);
    }

    TEST_F(ManagerTest, xor2_function) {
        // truth table
        EXPECT_EQ(m->xor2(m->False(), m->False()), FalseId);
        EXPECT_EQ(m->xor2(m->False(), m->True()), TrueId);
        EXPECT_EQ(m->xor2(m->True(), m->False()), TrueId);
        EXPECT_EQ(m->xor2(m->True(), m->True()), FalseId);
    }

    TEST_F(ManagerTest, neg_function) {
        // returns the ID representing the negation of the given function.

        // truth table
        EXPECT_EQ(m->neg(m->True()), FalseId);
        EXPECT_EQ(m->neg(m->False()), TrueId);
    }

    TEST_F(ManagerTest, nand2_function) {
        // truth table
        EXPECT_EQ(m->nand2(m->False(), m->False()), TrueId);
        EXPECT_EQ(m->nand2(m->False(), m->True()), TrueId);
        EXPECT_EQ(m->nand2(m->True(), m->False()), TrueId);
        EXPECT_EQ(m->nand2(m->True(), m->True()), FalseId);
    }

    TEST_F(ManagerTest, nor2_function) {
        // truth table
        EXPECT_EQ(m->nor2(m->False(), m->False()), TrueId);
        EXPECT_EQ(m->nor2(m->False(), m->True()), FalseId);
        EXPECT_EQ(m->nor2(m->True(), m->False()), FalseId);
        EXPECT_EQ(m->nor2(m->True(), m->True()), FalseId);
    }

    TEST_F(ManagerTest, xnor2_function) {
        // truth table
        EXPECT_EQ(m->xnor2(m->False(), m->False()), TrueId);
        EXPECT_EQ(m->xnor2(m->False(), m->True()), FalseId);
        EXPECT_EQ(m->xnor2(m->True(), m->False()), FalseId);
        EXPECT_EQ(m->xnor2(m->True(), m->True()), TrueId);
    }
#endif
