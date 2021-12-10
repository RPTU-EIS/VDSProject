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
    int number_nodes_table;
    bool var_already_registered = false;
    number_nodes_table = uniqueTableSize();

    for (int i=0; i <= number_nodes_table; i++) {
        if (unique_table[i].label == label) {
            var_already_registered = true;
            break;
        }
    }
    if (!var_already_registered) {
        BDD_node new_var(number_nodes_table,1,number_nodes_table,number_nodes_table, (std::string&)label);
        unique_table.push_back(new_var);
        return new_var.id;
    }

    return 0;
}

BDD_ID Manager::uniqueTableSize(){
    size_t number_nodes;
    number_nodes = unique_table.size();
    return number_nodes;
}