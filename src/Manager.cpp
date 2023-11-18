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

    ManagerInterface::ManagerInterface() {
        ClassProject::BDD_ID_Entry entry = {"False", 0, 0, 0, 0};
        Table.push_back(entry);

        entry = {"True", 1, 1, 1, 1};
        Table.push_back(entry);
    }

    const BDD_ID &ManagerInterface::False() {
        static const BDD_ID ret = 0;
        return ret;
    }

    const BDD_ID &ManagerInterface::True() {
        static const BDD_ID ret = 1;
        return ret;
    }

    bool ManagerInterface::isVariable( BDD_ID x) {
        if (Table[x].label.size() == 1 && std::all_of(Table[x].label.begin(), Table[x].label.end(), ::isalpha)) {
            return true;
        }
        else {
            return false;
        }
    }

}