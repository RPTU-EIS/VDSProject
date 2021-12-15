#include "Manager.h"

namespace ClassProject{

/*
 *
 *
 */
    size_t uniqueTableSize(){
        return Manager::unique_table.size();
    }

    BDD_ID createVar(const std::string &label) {

        bool varExists=false;
        size_t sizeOfTable=uniqueTableSize();
        for(int i=0; i<Manager::unique_table.size(); i++) {
            if (Manager::unique_table[i].label==label) {
                varExists=true;
                return Manager::unique_table[i].node_id;
            }
        }
        if(varExists==false){
            Manager::unique_table.push_back(Manager::BDDnode {sizeOfTable,label,1,0,sizeOfTable});
            return Manager::unique_table[sizeOfTable].node_id;
        }
        else {
            return 0;
        }
    }


}