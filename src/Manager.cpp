#include "Manager.h"

namespace ClassProject {

    OBDDManager::OBDDManager(){
        nodes = {ZERO_NODE, ONE_NODE};
    }

    const BDD_ID &OBDDManager::True(){
        return 1;
    }

    const BDD_ID &OBDDManager::False(){
        return 0;
    }

    bool OBDDManager::isConstant(BDD_ID f){
        return (f == True() || f == False());
    }

    bool OBDDManager::isVariable(BDD_ID x){
        return !isConstant(x);//TODO
    }

    BDD_ID OBDDManager::add_unique_table(NodeData data){
        if(unique_table.find(data) != unique_table.end()){
            nodes.push_back(Node{.data=data});
            unique_table[data] = nodes.size()-1;
        }
        return unique_table[data];
    }

    BDD_ID OBDDManager::ite(BDD_ID i, BDD_ID t, BDD_ID e){
        //TODO terminal case
        //TODO grab from cache
        BDD_ID topVar; 
        BDD_ID high = ite(coFactorTrue(i,topVar), coFactorTrue(t,topVar), coFactorTrue(e,topVar));
        BDD_ID low = ite(coFactorFalse(i,topVar), coFactorFalse(t,topVar), coFactorFalse(e,topVar));

        if(high == low){
            return high;
        }

        BDD_ID result = add_unique_table({.low=low, .high=high, .topVar=topVar});
        //TODO save in cache

        return result;
    }

    bool OBDDManager::updateNodeLabel(BDD_ID id, BDD_ID a, BDD_ID b, std::string op){
        if(nodes[id].label == "")
            nodes[id].label = op + "(" + nodes[a].label + "," + nodes[b].label + ")";
    }

    BDD_ID OBDDManager::and2(BDD_ID a, BDD_ID b){
        BDD_ID id = ite(a,b, 0);
        updateNodeLabel(id, a, b, "and2");
        return id;
    }

    BDD_ID OBDDManager::or2(BDD_ID a, BDD_ID b){
        BDD_ID id = ite(a, 1, b);
        updateNodeLabel(id, a, b, "or2");
        return id;
    }

    BDD_ID OBDDManager::xor2(BDD_ID a, BDD_ID b){
        BDD_ID id = ite(a,neg(b), b);
        updateNodeLabel(id, a, b, "xor2");
        return id;
    }

    BDD_ID OBDDManager::neg(BDD_ID a){
        //TODO
        BDD_ID id;
        if(nodes[id].label == "")
            nodes[id].label = "~(" + nodes[a].label + ")";
        return id;
    }

    BDD_ID OBDDManager::nand2(BDD_ID a, BDD_ID b){
        BDD_ID id = ite(a,neg(b), 1);
        updateNodeLabel(id, a, b, "nand2");
        return id;
    }

    BDD_ID OBDDManager::nor2(BDD_ID a, BDD_ID b){
        BDD_ID id = ite(a, 0, neg(b));
        updateNodeLabel(id, a, b, "nor2");
        return id;
    }

    BDD_ID OBDDManager::xnor2(BDD_ID a, BDD_ID b){
        BDD_ID id = ite(a,b, neg(b));
        updateNodeLabel(id, a, b, "xnor2");
        return id;
    }

    void OBDDManager::visualizeBDD(std::string filepath, BDD_ID &root){
        //TODO
    }

}
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