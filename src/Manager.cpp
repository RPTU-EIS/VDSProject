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
        Unique_Table_Key key = {0, 0, 0};

        Table = {
            {{0,0,0}, 0},
            {{1,1,1}, 1}
        }
    }

    /**
     * @brief createVar
     * 
     * Creates a new variable with the given ID.
     * @param label String of the label of the variable.
     * @return returns the ID of the created variable.
     */
    BDD_ID Manager::createVar(const std::string &label) {

        //BDD_ID ID = Table.size();
        BDD_ID_Entry entry_Var;
        entry_Var.label = label;
        entry_Var.id = ID;
        entry_Var.high = 1;
        entry_Var.low = 0;
        entry_Var.TopVar = ID;

        Table.insert(entry_Var)
        push(entry_Var);
        return ID;
    };

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
    bool Manager::isConstant(BDD_ID f) {
        auto pred = [f](const BDD_ID_Entry & item) {
            return item.id == f;
        };

        if ( std::find_if(std::begin(Table), std::end(Table), pred) != std::end(Table) && Table[f].low == Table[f].high) {
            return true;
        }
        else {
            return false;
        }
    };

    bool Manager::isVariable( BDD_ID x) {
        if (Table[x].label.size() == 1 && std::all_of(Table[x].label.begin(), Table[x].label.end(), ::isalpha)) {
            return true;
        }
        else {
            return false;
        }
    }

}