// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"

namespace ClassProject {

    class Manager : public ManagerInterface{
        public:
        Manager();

        struct BDD_ID_Entry {
            std::string label;
            BDD_ID id;
            int high;
            int low;
            BDD_ID TopVar;
        };

        std::vector<BDD_ID_Entry> Table;

        BDD_ID createVar(const std::string &label) override;
        const BDD_ID &True() override;
        const BDD_ID &False() override;
        bool isConstant(BDD_ID f) override;
        bool isVariable(BDD_ID x) override;
    };

}

#endif
