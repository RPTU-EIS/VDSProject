//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include <gtest/gtest.h>
#include "../Manager.h"
#include <memory>

using namespace ClassProject;

class ManagerTest : public testing::Test {
    protected:
        std::unique_ptr<Manager> m;;
        BDD_ID a;
        BDD_ID b;
        BDD_ID c;
        BDD_ID d;

        void SetUp() override {
            m = std::make_unique<Manager>();
            a = m->createVar("a");  // ID 2
            b = m->createVar("b");  // ID 3
            c = m->createVar("c");  // ID 4
            d = m->createVar("d");  // ID 5
        }

        void TearDown() override {
            // m->~Manager();
        }
};

    TEST_F(ManagerTest, createVar) {
        EXPECT_EQ(a, 2);
        EXPECT_EQ(b, 3);
        EXPECT_EQ(c, 4);
        EXPECT_EQ(d, 5);
    }

    TEST_F(ManagerTest, True) {
        EXPECT_EQ(m->True(), TrueId);
    }


    TEST_F(ManagerTest, False) {
        EXPECT_EQ(m->False(), FalseId);
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

    TEST_F(ManagerTest, ite) {
        EXPECT_EQ(m->ite(m->True(), m->False(), m->True()), FalseId);
        EXPECT_EQ(m->ite(m->False(), m->False(), m->True()), TrueId);

        EXPECT_EQ(m->ite(m->False(), a, b), b);
        EXPECT_EQ(m->ite(m->True(), a, b), a);
        EXPECT_EQ(m->ite(a, m->True(), m->False()), a);
        EXPECT_EQ(m->ite(c, d, d), d);
        EXPECT_EQ(m->ite(a, m->False(), m->True()), FalseId);
    }

    TEST_F(ManagerTest, coFactorTrue) {
        EXPECT_EQ(m->coFactorTrue(m->True()), TrueId);
        EXPECT_EQ(m->coFactorTrue(a), TrueId);
    }

    TEST_F(ManagerTest, coFactorFalse) {
        EXPECT_EQ(m->coFactorFalse(m->False()), FalseId);
        EXPECT_EQ(m->coFactorFalse(a), FalseId);
    }

    TEST_F(ManagerTest, and2_function) {
        // truth table
        EXPECT_EQ(m->and2(m->False(), m->False()), FalseId);
        EXPECT_EQ(m->and2(m->False(), m->True()), FalseId);
        EXPECT_EQ(m->and2(m->True(), m->False()), FalseId);
        EXPECT_EQ(m->and2(m->True(), m->True()), TrueId);

        EXPECT_EQ(m->and2(a,b),m->ite(a,b,m->False()));
    }

    TEST_F(ManagerTest, or2_function) {
        // truth table
        EXPECT_EQ(m->or2(m->False(), m->False()), FalseId);
        EXPECT_EQ(m->or2(m->False(), m->True()), TrueId);
        EXPECT_EQ(m->or2(m->True(), m->False()), TrueId);
        EXPECT_EQ(m->or2(m->True(), m->True()), TrueId);

        EXPECT_EQ(m->or2(a, b), m->ite(a, m->True(), b));
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


    TEST_F(ManagerTest, getTopVarName) {
        // returns the label of the given BDD_ID
        EXPECT_EQ(m->getTopVarName(m->False()), "false");
        EXPECT_EQ(m->getTopVarName(m->True()), "true");
        EXPECT_EQ(m->getTopVarName(a), "a");
    }

    TEST_F(ManagerTest, findNodes) {
        BDD_ID a_or_b = m->or2(a, b);
        BDD_ID c_and_d = m->and2(c, d);
        BDD_ID f = m->and2(a_or_b, c_and_d);

        std::set<BDD_ID> expected = {m->and2(b, c_and_d), c_and_d, d, m->True(), m->False()};
        std::set<BDD_ID> nodes;
        m->findNodes(m->and2(b, c_and_d), nodes);

        // Assert that the nodes found match the expected nodes
        EXPECT_EQ(nodes, expected);

    }

    TEST_F(ManagerTest, findVars) {
        BDD_ID a_or_b = m->or2(a, b);
        BDD_ID c_and_d = m->and2(c, d);
        BDD_ID f = m->and2(a_or_b, c_and_d);

        std::set<BDD_ID> expected = {m->topVar(b), m->topVar(c), m->topVar(d)};
        std::set<BDD_ID> vars;
        m->findVars(m->and2(b, c_and_d), vars);

        EXPECT_EQ(vars, expected);
    }

    TEST_F(ManagerTest, uniqueTableSize) {
        BDD_ID size = m->uniqueTableSize();
        m->createVar("e");
        EXPECT_EQ(m->uniqueTableSize(), size + 1);
    }

    TEST_F(ManagerTest, Example_ROBDD){
        BDD_ID f = m->and2(m->or2(a, b), m->and2(c, d));

        m->visualizeBDD("ROBDD.txt",f);
    }

#endif
