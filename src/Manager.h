// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <vector>
#include <map>
#include <iostream>
#include "gtest/gtest.h"
// #include "Tests.h"

namespace ClassProject {

    struct NodeData{
        BDD_ID low, high, topVar;

        bool operator < (const NodeData & other) const{
            if(low == other.low){
                if(high == other.high){
                    return topVar < other.topVar;
                }
                return high < other.high;
            }
            return low < other.low;
        }        

        bool operator== (const NodeData & other) const {
            return (low == other.low) && (high == other.high) && (topVar == other.topVar);
        }
    };

    struct Node{
        std::string label;
        NodeData data;

        bool operator== (const Node &other) const {
            return data == other.data;
        }

        friend std::ostream& operator <<(std::ostream& stream, const Node& node);
    };

    class Manager : ManagerInterface{

        std::vector<Node> nodes;
        std::map<NodeData, BDD_ID> unique_table; //TODO use hash table
        std::map<NodeData, BDD_ID> computed_table; //TODO use hash table

        const static BDD_ID FALSE_ADDRESS;
        const static BDD_ID TRUE_ADDRESS;

        const static Node FALSE_NODE;
        const static Node TRUE_NODE;

        BDD_ID add_unique_table(NodeData data);
        void bfs(const BDD_ID root, std::vector<BDD_ID> &order, std::vector<bool> &marc);        

    public:
        
        Manager();
        Manager(std::vector<Node> nodes);

        BDD_ID createVar(const std::string &label);

        const BDD_ID &True();

        const BDD_ID &False();

        bool isConstant(BDD_ID f);

        bool isVariable(BDD_ID x);

        BDD_ID topVar(BDD_ID f);
        
        BDD_ID topVar(BDD_ID f, BDD_ID g);

        BDD_ID high(BDD_ID f);

        BDD_ID low(BDD_ID f);

        BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e);

        BDD_ID coFactorTrue(BDD_ID f, BDD_ID x);

        BDD_ID coFactorFalse(BDD_ID f, BDD_ID x);

        BDD_ID coFactorTrue(BDD_ID f);

        BDD_ID coFactorFalse(BDD_ID f);

        bool updateNodeLabel(BDD_ID id, BDD_ID a, BDD_ID b, std::string op);

        BDD_ID and2(BDD_ID a, BDD_ID b);

        BDD_ID or2(BDD_ID a, BDD_ID b);

        BDD_ID xor2(BDD_ID a, BDD_ID b);

        BDD_ID neg(BDD_ID a);

        BDD_ID nand2(BDD_ID a, BDD_ID b);

        BDD_ID nor2(BDD_ID a, BDD_ID b);

        BDD_ID xnor2(BDD_ID a, BDD_ID b);

        std::string getTopVarName(const BDD_ID &root);

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root);

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root);

        size_t uniqueTableSize();

        void visualizeBDD(std::string filepath, BDD_ID &root);
    };

}

#endif
