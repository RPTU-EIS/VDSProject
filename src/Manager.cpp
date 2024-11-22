#include "Manager.h"



namespace ClassProject {
    Manager::Manager() {
        init_unique_tb();
    }

    void Manager::init_unique_tb() {
        uTableRow false_node = {.id=uniqueTableSize(), .high=False(), .low=False(), .topVar=False(), .label="false"};
        unique_tb.push_back(false_node);
        uTableRow true_node = {.id=uniqueTableSize(), .high=True(), .low=True(), .topVar=True(), .label="true"};
        unique_tb.push_back(true_node);
    }


      
}

