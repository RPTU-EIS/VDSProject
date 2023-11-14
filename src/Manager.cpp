#include "Manager.h"


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

}