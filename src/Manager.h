// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_map>


namespace ClassProject {

    static const BDD_ID FalseId = 0;
    static const BDD_ID TrueId = 1;

    struct uTableRow {
        BDD_ID id;
        BDD_ID high;
        BDD_ID low;
        BDD_ID topVar;
        std::string label;
    };

  class Manager : public ManagerInterface {
    private:
        std::vector<uTableRow> unique_tb;
        std::unordered_map<size_t, BDD_ID> unique_tb_map;
        std::unordered_map<size_t, BDD_ID> computed_tb;

        BDD_ID find_or_add_unique_tb(BDD_ID x, BDD_ID high, BDD_ID low);

        static size_t hashFunction(BDD_ID f, BDD_ID g, BDD_ID h);

        void print_unique_tb();

        static void swapID(BDD_ID *a, BDD_ID *b);

        void standard_triples(BDD_ID *i, BDD_ID *t, BDD_ID *e);

        void init_unique_tb();

    public:

        Manager();

        ~Manager() = default;

        BDD_ID createVar(const std::string &label) override;

        const BDD_ID &True() override;

        const BDD_ID &False() override;

        /**
        * isConstant determines if a node is a leafnode
        * @param f ID of the Node under test
        * @return true if f is a constant 0 or 1
        */
        bool isConstant(BDD_ID f) override;

        /**
        * isVariable determines if a node is a variable
        * @param x ID of the Node under test
        * @return returns true if id of x is equal to topVar of x and x is not a leafnode
        * see /doc/VDSCP_Part_1.pdf Tab. 2 for a better understanding
        */
        bool isVariable(BDD_ID x) override;

        /**
        * topVar returns the top Variable of the node
        * @param f ID of the Node under test
        * @return topVar of f
        */
        BDD_ID topVar(BDD_ID f) override;

        BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e) override;

        BDD_ID coFactorTrue(BDD_ID f, BDD_ID x) override;

        BDD_ID coFactorFalse(BDD_ID f, BDD_ID x) override;

        BDD_ID coFactorTrue(BDD_ID f) override;

        BDD_ID coFactorFalse(BDD_ID f) override;

        BDD_ID and2(BDD_ID a, BDD_ID b) override;

        BDD_ID or2(BDD_ID a, BDD_ID b) override;

        BDD_ID xor2(BDD_ID a, BDD_ID b) override;

        BDD_ID neg(BDD_ID a) override;

        BDD_ID nand2(BDD_ID a, BDD_ID b) override;

        BDD_ID nor2(BDD_ID a, BDD_ID b) override;

        BDD_ID xnor2(BDD_ID a, BDD_ID b) override;

        std::string getTopVarName(const BDD_ID &root) override;

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;

        size_t uniqueTableSize() override;

        void visualizeBDD(std::string filepath, BDD_ID &root) override;
    };
}



#endif
