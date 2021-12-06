// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include<iostream>
#include <list>

namespace ClassProject 
{

    struct MyStruct
    {
        std::string label;
        BDD_ID id;
        uint16_t high;
        uint16_t low;
        uint16_t topVar;
    };

class Manager: ManagerInterface
{
public:
    Manager();
    ~Manager();

    BDD_ID createVar(const std::string &label);

    const BDD_ID &True();

    const BDD_ID &False();

    bool isConstant(BDD_ID f);

    bool isVariable(BDD_ID x);

    BDD_ID topVar(BDD_ID f);

    BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e);

    BDD_ID coFactorTrue(BDD_ID f, BDD_ID x);

    BDD_ID coFactorFalse(BDD_ID f, BDD_ID x);

    BDD_ID coFactorTrue(BDD_ID f);

    BDD_ID coFactorFalse(BDD_ID f);

    BDD_ID neg(BDD_ID a);

    BDD_ID and2(BDD_ID a, BDD_ID b);

    BDD_ID or2(BDD_ID a, BDD_ID b);

    BDD_ID xor2(BDD_ID a, BDD_ID b);

    BDD_ID nand2(BDD_ID a, BDD_ID b);

    BDD_ID nor2(BDD_ID a, BDD_ID b);

    BDD_ID xnor2(BDD_ID a, BDD_ID b);

    std::string getTopVarName(const BDD_ID &root);

    void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root);

    void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root);

    size_t uniqueTableSize();

    
private:
    std::list<MyStruct> myList;
    
};
}

#endif
