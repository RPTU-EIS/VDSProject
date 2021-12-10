#include "Manager.h"

using namespace ClassProject;

Manager::Manager(){
    std::string false_str = "False";
    std::string true_str = "True";
    BDD_node node1(0,0,0,0,false_str);
    BDD_node node2(1,1,1,1,true_str);
    unique_table.push_back(node1);
    unique_table.push_back(node2);
}

BDD_ID Manager::createVar(const std::string &label) {
    return 0;
}

BDD_ID Manager::uniqueTableSize(){
    size_t number_nodes;
    number_nodes = unique_table.size();
    return number_nodes;
}