#include "BDD_node.h"

namespace ClassProject {

    BDD_node::BDD_node(BDD_ID a, BDD_ID b, BDD_ID c, BDD_ID d, std::string &e){

        id = a;
        high = b;
        low = c;
        topvar = d;
        label = e;

    };

};