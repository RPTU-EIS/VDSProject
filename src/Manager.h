// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <unordered_map>

namespace ClassProject
{

    class Manager : public ManagerInterface
    {
    public:
        Manager();

        /**
         * @brief Unique_Table_Key
         * Defines a structure to be used as a key in the hash map
         *
         */
        struct Unique_Table_Key
        {
            BDD_ID TopVar;
            BDD_ID low;
            BDD_ID high;

            bool operator==(const Unique_Table_Key &other) const
            {
                return TopVar == other.TopVar && low == other.low && high == other.high;
            }
        };

        /**
         * @brief Unique_Table_Entry
         * Defines a structure to be used as a value in the hash map
         *
         */
        struct Unique_Table_Entry
        {
            std::string label;
            BDD_ID id;
        };

        /**
         * @brief KeyHash
         *
         * Defines a hash function for the Key structure
         *
         */
        struct KeyHash
        {
            std::size_t operator()(const Unique_Table_Key &k) const
            {
                // A hash function
                return ((std::hash<BDD_ID>()(k.TopVar) ^ (std::hash<BDD_ID>()(k.low) << 1)) >> 1) ^ (std::hash<BDD_ID>()(k.high) << 1);
            }
        };

        // struct input_CT
        // {
        //     BDD_ID i;
        //     BDD_ID t;
        //     BDD_ID e;

        //     bool operator == (const input_CT &other) const
        //     {
        //         return (i == other.i) && (t == other.t) && (e == other.e);
        //     }
        // };

        // struct KeyHash_CT
        // {
        //     //std::size_t operator()(const input_CT &input) const
        //     std::size_t operator()( const input_CT& k ) const
        //     // {
        //     //     // Compute individual hash values for first, second and third
        //     //     std::size_t res = 17;
        //     //     res = res * 31 + std::hash<BDD_ID>()(k.i);
        //     //     res = res * 31 + std::hash<BDD_ID>()(k.t);
        //     //     res = res * 31 + std::hash<BDD_ID>()(k.e);
        //     //     return res;
        //     // }
        //     {
        //         // A hash function
        //         return ((std::hash<BDD_ID>()(k.i) ^ (std::hash<BDD_ID>()(k.t) << 1)) >> 1) ^ (std::hash<BDD_ID>()(k.e) << 1);
        //     }
        // };

        std::unordered_map<Unique_Table_Key, Unique_Table_Entry, KeyHash> Table;
        std::unordered_map<Unique_Table_Key,BDD_ID,KeyHash> computed_table;

        BDD_ID createVar(const std::string &label) override;
        const BDD_ID &True() override;
        const BDD_ID &False() override;
        bool isConstant(BDD_ID f) override;
        bool isVariable(BDD_ID x) override;
        BDD_ID topVar(BDD_ID f) override;
        BDD_ID coFactorTrue(BDD_ID f, BDD_ID x) override;
        BDD_ID coFactorFalse(BDD_ID f, BDD_ID x) override;
        BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e) override;
        BDD_ID and2(std::string &a, std::string &b) override;
    };
}

#endif
