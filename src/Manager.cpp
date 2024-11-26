#include "Manager.h"

#include <algorithm>


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

    BDD_ID Manager::createVar(const std::string &label){
        BDD_ID id = uniqueTableSize();
        unique_tb.push_back((uTableRow) {.id=id, .high=True(), .low=False(), .topVar=id, .label=label});
        return id;
    }

    const BDD_ID &Manager::True(){
        return TrueId;
    }

    const BDD_ID &Manager::False(){
        return FalseId;
    }

    bool Manager::isConstant(BDD_ID f){
        return f <= 1;
    }

    bool Manager::isVariable(BDD_ID x){
        return unique_tb.at(x).topVar == x && !isConstant(x);
    }

    BDD_ID Manager::topVar(BDD_ID f){
        return unique_tb.at(f).topVar;
    }

    BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){
        if (isConstant(i)) {
           return i == TrueId ? t : e;
        }/**
        else if(t == TrueId && e == FalseId) {
            return i;
        }
        else if(alreadyexisting) {

        }
        else
        {

        }
*/  return 0;
    }

    BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
        return 0;
    }

    BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){
        return 0;
    }

    BDD_ID Manager::coFactorTrue(BDD_ID f){
        return 0;
    }

    BDD_ID Manager::coFactorFalse(BDD_ID f){
        return 0;
    }

    BDD_ID Manager::and2(BDD_ID a, BDD_ID b){
        return 0;
    }

    BDD_ID Manager::or2(BDD_ID a, BDD_ID b){
        return 0;
    }

    BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){
        return 0;
    }

    BDD_ID Manager::neg(BDD_ID a){
        return 0;
    }

    BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){
        return 0;
    }

    BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){
        return 0;
    }

    BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){
        return 0;
    }

    std::string Manager::getTopVarName(const BDD_ID &root){
        return 0;
    }

    void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){
    }

    void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){

    }

    size_t Manager::uniqueTableSize(){
        return unique_tb.size();
    }

    void Manager::visualizeBDD(std::string filepath, BDD_ID &root){

    }
    
}

