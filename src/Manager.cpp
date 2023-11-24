#include "Manager.h"
#include <algorithm>

/**
 * @brief ClassProject.
 * 
 * Me gusta la fafa.
 * @param arg1 What the first argument to the function should be.
 * @return What you can expect to get back from the function.
 */

namespace ClassProject {

    Manager::Manager() {
    
        Table.emplace(Unique_Table_Key{0,0,0}, Unique_Table_Entry{"False", 0});

        Table.emplace(Unique_Table_Key{1,1,1}, Unique_Table_Entry{"True",1});
    }

    /**
     * @brief createVar
     * 
     * Creates a new variable with the given ID.
     * @param label String of the label of the variable.
     * @return returns the ID of the created variable.
     */
    // BDD_ID Manager::createVar(const std::string &label) {

    //     //BDD_ID ID = Table.size();
    //     BDD_ID_Entry entry_Var;
    //     entry_Var.label = label;
    //     entry_Var.id = ID;
    //     entry_Var.high = 1;
    //     entry_Var.low = 0;
    //     entry_Var.TopVar = ID;

    //     Table.insert(entry_Var)
    //     push(entry_Var);
    //     return ID;
    // };

    const BDD_ID &Manager::False() {
        static const BDD_ID ret = 0;
        return ret;
    }

    const BDD_ID &Manager::True() {
        static const BDD_ID ret = 1;
        return ret;
    }

    /**
     * @brief isConstant
     * 
     * Returns true if the node is a leaf node.
     * @param f ID of the node.
     * @return returns true if the node is a leaf node.
     */
//     bool Manager::isConstant(BDD_ID f) {
//         auto pred = [f](const BDD_ID_Entry & item) {
//             return item.id == f;
//         };

//         if ( std::find_if(std::begin(Table), std::end(Table), pred) != std::end(Table) && Table[f].low == Table[f].high) {
//             return true;
//         }
//         else {
//             return false;
//         }
//     };

   /**
     * @brief isVariable
     *
     * checks whether the item corresponding to a given ID is a variable or not.
     * @param x: ID of the node.
     * @return returns true if the ID represents a variable.
     */
    bool Manager::isVariable( BDD_ID x) {

       for (auto & it : Table) {
           if (it.second.id == x) {
               if (it.second.label.size() == 1 &&
                   std::all_of(it.second.label.begin(), it.second.label.end(), ::isalpha)) {
                   return true;
               } else {
                   return false;
               }
           }
       }
       return false;
   }

}