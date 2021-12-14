#ifndef VDSPROJECT_BDD_NODE_H
#define VDSPROJECT_BDD_NODE_H

#include "ManagerInterface.h"

namespace ClassProject {

    class BDD_node {

    public:

        BDD_ID id;
        BDD_ID high;
        BDD_ID low;
        BDD_ID topvar;
        std::string label;

        BDD_node(BDD_ID p_id, BDD_ID p_high, BDD_ID p_low, BDD_ID p_topvar, std::string &p_label);

    };

};


#endif //VDSPROJECT_BDD_NODE_H
