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


        void init_unique_tb();

        BDD_ID find_or_add_unique_tb(BDD_ID x, BDD_ID high, BDD_ID low);

        void print_unique_tb();

        static void swapID(BDD_ID *a, BDD_ID *b);

        void standard_triples(BDD_ID *i, BDD_ID *t, BDD_ID *e);

    public:
        Manager();

        ~Manager() = default;

        BDD_ID createVar(const std::string &label) override;

        const BDD_ID &True() override;

        const BDD_ID &False() override;

        bool isConstant(BDD_ID f) override;

        bool isVariable(BDD_ID x) override;

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
