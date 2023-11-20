// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <unordered_map>

        struct Unique_Table_Key {
            ClassProject::BDD_ID TopVar;
            int low;
            int high;

            bool operator==(const Unique_Table_Key& other) const {
        return TopVar == other.TopVar && low == other.low && high == other.high;
    }
        };
        
        template <>
        struct std::hash<Unique_Table_Key>
        {
        std::size_t operator()(const Unique_Table_Key & k) const
        {
            using std::size_t;
            using std::hash;
            using std::string;

            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:

            return ((hash<int>()(k.TopVar)
                    ^ (hash<int>()(k.low) << 1)) >> 1)
                    ^ (hash<int>()(k.high) << 1);
        }
        };

namespace ClassProject {

    class Manager : public ManagerInterface{
        public:
        Manager();

        std::unordered_map<Unique_Table_Key, BDD_ID> Table;
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
