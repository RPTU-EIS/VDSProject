// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <unordered_map>

// Define a structure to be used as a key in the hash map
struct Unique_Table_Key {
    ClassProject::BDD_ID TopVar;
    ClassProject::BDD_ID low;
    ClassProject::BDD_ID high;

    bool operator==(const Unique_Table_Key& other) const {
        return TopVar == other.TopVar && low == other.low && high == other.high;
    }
};

// Define a hash function for the Key structure
struct KeyHash {
    std::size_t operator()(const Unique_Table_Key& k) const {
        // A simple hash function for illustration purposes
        return std::hash<int>()(k.TopVar) ^ std::hash<int>()(k.low) ^ std::hash<int>()(k.high);
    }
};

namespace ClassProject {

    class Manager : public ManagerInterface{
        public:
        Manager();

        std::unordered_map<Unique_Table_Key, BDD_ID, KeyHash> Table;
//        std::vector<BDD_ID_Entry> Table;

        BDD_ID createVar(const std::string &label) override;
        const BDD_ID &True() override;
        const BDD_ID &False() override;
        bool isConstant(BDD_ID f) override;
        bool isVariable(BDD_ID x) override;
    };
    void hash_op(){


    }

}

#endif
