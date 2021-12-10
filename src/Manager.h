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
    };

};

#endif
