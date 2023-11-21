#include "Manager.h"

namespace ClassProject {

/**
* @brief returns the id of the top variable of the given node f
* @author Kamel Fakih
* 
* @param f
* @return BDD_ID
*/
BDD_ID OBDDManager::topVar(BDD_ID f){
    return nodes[f].data.topVar;
}

/**
* @brief returns the id of the high node of the given node f
* @author Kamel Fakih
* 
* @param f
* @return BDD_ID
*/
BDD_ID OBDDManager::low(BDD_ID f){
    return nodes[f].data.low;
}

/**
* @brief returns the id of the low of the given node f
* @author Kamel Fakih
* 
* @param f ID
* @return BDD_ID
*/
BDD_ID OBDDManager::high(BDD_ID f){
    return nodes[f].data.high;
}

}