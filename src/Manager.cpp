#include <iostream>
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
    BDD_node new_var(uniqueTableSize(),1,0,uniqueTableSize(), (std::string&)label);
    unique_table.push_back(new_var);
    return new_var.id;
}

void Manager::addNode(BDD_ID p_id, BDD_ID p_high, BDD_ID p_low, BDD_ID p_topvar, std::string &p_label){
    BDD_node new_var(p_id,p_high,p_low,p_topvar, (std::string&)p_label);
    unique_table.push_back(new_var);
}

BDD_ID Manager::uniqueTableSize(){
    size_t number_nodes;
    number_nodes = unique_table.size();
    return number_nodes;
}

const BDD_ID &Manager::True() {
    return unique_table[1].id;
}

const BDD_ID &Manager::False(){
    return unique_table[0].id;
}

bool Manager::isVariable(BDD_ID x){
    if (unique_table[x].high==1 and unique_table[x].low==0){
        return true;
    }
    return false;
}

std::string Manager::getTopVarName(const BDD_ID &root) {

    BDD_ID id=unique_table[root].topvar;
    return unique_table[id].label;
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root) {

    if(nodes_of_root.find(root)==nodes_of_root.end()){

        nodes_of_root.insert(root);
    }

    if (root !=1 and root !=0){

        findNodes(unique_table[root].high,nodes_of_root);
        findNodes(unique_table[root].low,nodes_of_root);
    }

}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){
    std::set<BDD_ID> a={};
    findNodes(root,a);
    for ( std::set<BDD_ID>::iterator itr = a.begin(); itr != a.end(); itr++) {
        if(*itr !=0 and *itr!=1){     //we can replace this by Is_constant function
            vars_of_root.insert(unique_table[*itr].topvar);
        }
    }
}

bool Manager::isConstant(BDD_ID f) {
    bool is_leaf;

    if (unique_table[f].id == 0 or unique_table[f].id == 1){
        is_leaf = true;
    }
    else{
        is_leaf = false;
    }

    return is_leaf;
}

BDD_ID Manager::topVar(BDD_ID f){
    return unique_table[f].topvar;
}

void Manager::printUniqueTable( void ){
    std::cout << "ID\t" << "Label\t" << "High\t" << "Low\t" << "TopVar\t\n";
    for( int i = 0; i < uniqueTableSize(); i++){
        std::cout << unique_table[i].id << "\t" << unique_table[i].label << "\t" << unique_table[i].high << "\t" <<
        unique_table[i].low << "\t" << unique_table[i].topvar << "\t\n";
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    BDD_ID T, F;
    //The topVar is the variable with smaller ID in an expression
    //If topVar(f) > x, then x won't compose f, hence it makes no
    //difference for f if x is 1, hence it's a terminal case.
    if( isConstant(f) || isConstant(x) || topVar(f) > x )
        return f;
    if( topVar(f) == x )
        return unique_table[f].high;
    else{ //if topVar(f) < x, then f may depend on x, hence the need of recursion
        T = coFactorTrue( unique_table[f].high, x );
        F = coFactorTrue( unique_table[f].low, x );
        return ite( topVar(f), T, F );
    }
}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x) {
    BDD_ID T, F;
    //The topVar is the variable with smaller ID in an expression
    //If topVar(f) > x, then x won't compose f, hence it makes no
    //difference for f if x is 0, hence it's a terminal case.
    if( isConstant(f) || isConstant(x) || topVar(f) > x )
        return f;
    if( topVar(f) == x )
        return unique_table[f].low;
    else{ //if topVar(f) < x, then f may depend on x, hence the need of recursion
        T = coFactorFalse( unique_table[f].high, x );
        F = coFactorFalse( unique_table[f].low, x );
        return ite( topVar(f), T, F );
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f){
    return unique_table[f].high;
}

BDD_ID Manager::coFactorFalse(BDD_ID f){
    return unique_table[f].low;
}

BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){

    BDD_ID  highSuccessor=iteAssist(coFactorTrue(i), coFactorTrue(t,unique_table[i].topvar),
                                    coFactorTrue(e,unique_table[i].topvar));

    BDD_ID lowSuccessor=iteAssist(coFactorFalse(i), coFactorFalse(t,unique_table[i].topvar),
                                  coFactorFalse(e,unique_table[i].topvar));

    if(highSuccessor==lowSuccessor){
        return highSuccessor ;
    }

    BDD_ID exist=checkExistance(highSuccessor,lowSuccessor,unique_table[i].topvar);
    if(exist==0){ //check if there is another node with the same top_var high Low
        std::string x ="newNode";
        addNode(uniqueTableSize(), highSuccessor, lowSuccessor, unique_table[i].topvar, (std::string &) x);
        return uniqueTableSize()-1;
    }
    else
        return exist;
}

BDD_ID Manager::iteAssist(BDD_ID i, BDD_ID t, BDD_ID e){

    if(i==1){
        return t;         //if it is a terminal case return the id
    }
    else{
        if(i==0){
            return e;     //if it is a terminal case return the id
        }
        else{
            if(t==0 and e==0)
                return 0;

            else{
                if(t==1 and e==1)
                    return 1;
                else
                    return ite(i,t,e);  //if it is not a terminal case start our recursion method
            }
        }
    }
}


BDD_ID Manager::checkExistance(BDD_ID highSuccessor,BDD_ID lowSuccessor,BDD_ID topVariable_i) {

    for (BDD_ID i = 0; i < uniqueTableSize(); i++) {
        if(unique_table[i].high==highSuccessor and unique_table[i].low==lowSuccessor
           and unique_table[i].topvar==topVariable_i){
            return i;
        }
        if(highSuccessor==1 and lowSuccessor==1){
            return 1;
        }
    }
    return 0 ;
}
