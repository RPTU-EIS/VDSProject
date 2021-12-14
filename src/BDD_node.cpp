#include "BDD_node.h"

namespace ClassProject {

    BDD_node::BDD_node(BDD_ID p_id, BDD_ID p_high, BDD_ID p_low, BDD_ID p_topvar, std::string &p_label){

        id = p_id;
        high = p_high;
        low = p_low;
        topvar = p_topvar;
        label = p_label;

    };

};