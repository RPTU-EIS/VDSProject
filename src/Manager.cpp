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