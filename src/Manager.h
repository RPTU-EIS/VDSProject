// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include "BDD_node.h"
#include <vector>
namespace ClassProject {

    class Manager : public ManagerInterface {

    public:
        std::vector<BDD_node> unique_table;

        /**
         *   Manager Constructor Definition.
         *   The unique table object is initialized with two default entries, False and True nodes.
        */
        Manager();

        /**
         *   Create Variable Function Definition.
         *   @param[in] label Name of the label of the new variable.
        */
        BDD_ID createVar(const std::string &label) override;

        /**
         *   UniqueTableSize Definition.
         *   Returns the number of nodes currently existing in the unique table of the Manager class.
        */
        size_t uniqueTableSize() override;

        /**
        *   IsTrue Function.
        *   Returns True if the node is True.
       */
        const BDD_ID &True() override;

        /**
        *   IsFalse Function.
        *   Returns True if the node is False.
       */
        const BDD_ID &False() override;
        /**
              *   isVariable Function.
              *   Returns True if the node represents a variable.
             */
        bool isVariable(BDD_ID x) override;
        /**
              *   getTopVarName.
              *   Returns the name of the rop variable for a given node.
             */
        std::string getTopVarName(const BDD_ID &root) override;
        /**
             *   AddNode.
             *  add a node to our table with a given id, true node, false node,topVariable, label
             *  this function is used during the tests.
            */

        void AddNode(BDD_ID a, BDD_ID b, BDD_ID c, BDD_ID d, std::string &e) override;

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) override;

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root) override;
    };

};

#endif
