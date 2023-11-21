#include "Manager.h"

namespace ClassProject {

/**
* @brief returns the id of the top variable of the given node f
* @author Kamel Fakih
* 
* @param f ID of node representing function f
* @return BDD_ID ID of top variable node
*/
BDD_ID OBDDManager::topVar(BDD_ID f){
    return nodes[f].data.topVar;
}

/**
* @brief returns the id of the high node of the given node f
* @author Kamel Fakih
* 
* @param f ID of node representing function f
* @return BDD_ID ID of top variable node
*/
BDD_ID OBDDManager::low(BDD_ID f){
    return nodes[f].data.low;
}

/**
* @brief returns the id of the low of the given node f
* @author Kamel Fakih
* 
* @param f ID of node representing function f
* @return BDD_ID ID of top variable node
*/
BDD_ID OBDDManager::high(BDD_ID f){
    return nodes[f].data.high;
}

/**
 * @brief positive cofactor of the function f with respect to variable x
 * @author Kamel Fakih
 * 
 * @param f ID of node representing function f
 * @param x ID of node representing variable x
 * @return BDD_ID ID of the node representing the postive cofactor
 *
 * returns the positive cofactor of the function represented by ID f with respect to
 * the variable represented by ID x. 
 */
BDD_ID OBDDManager::coFactorTrue(BDD_ID f, BDD_ID x){

    BDD_ID fTopVar = topVar(f);
    BDD_ID fHigh   = high(f);
    BDD_ID fLow    = low(f);

    if(isConstant(f) || isConstant(x) || fTopVar > x){
        return f;
    }
    if(fTopVar == x){
        return fHigh;
    }else{
        auto T = coFactorTrue(fHigh, x);
        auto F = coFactorTrue(fLow, x);
        return ite(fTopVar, T, F);
    }
}

/**
 * @brief positive cofactor of the function f with respect to its top variable
 * @author Kamel Fakih
 * 
 * @param f ID of node representing function f
 * @return BDD_ID ID of the node representing the postive cofactor
 *
 * calls coFactorTrue(BDD_ID f, BDD_ID x) with x as f's top variable
 *
 */
BDD_ID OBDDManager::coFactorTrue(BDD_ID f){
    return coFactorTrue(f, topVar(f));
}

/**
 * @brief negative cofactor of the function f with respect to variable x
 * @author Kamel Fakih
 * 
 * @param f ID of node representing function f
 * @param x ID of node representing variable x
 * @return BDD_ID ID of the node representing the negative cofactor
 *
 * returns the negative cofactor of the function represented by ID f with respect to
 * the variable represented by ID x. 
 */
BDD_ID OBDDManager::coFactorFalse(BDD_ID f, BDD_ID x){

    BDD_ID fTopVar = topVar(f);
    BDD_ID fHigh   = high(f);
    BDD_ID fLow    = low(f);

    if(isConstant(f) || isConstant(x) || fTopVar > x){
        return f;
    }
    if(fTopVar == x){
        return fLow;
    }else{
        auto T = coFactorFalse(fHigh, x);
        auto F = coFactorFalse(fLow, x);
        return ite(fTopVar, T, F);
    }
}

/**
 * @brief negative cofactor of the function f with respect to its top variable
 * @author Kamel Fakih
 * 
 * @param f ID of node representing function f
 * @return BDD_ID ID of the node representing the negative cofactor
 *
 * calls coFactorFalse(BDD_ID f, BDD_ID x) with x as f's top variable
 *
 */
BDD_ID OBDDManager::coFactorFalse(BDD_ID f){
    return coFactorFalse(f, topVar(f));
}

}