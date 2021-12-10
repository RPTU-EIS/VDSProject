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

        BDD_node(BDD_ID a, BDD_ID b, BDD_ID c, BDD_ID d, std::string &e);

    };

};


#endif //VDSPROJECT_BDD_NODE_H
