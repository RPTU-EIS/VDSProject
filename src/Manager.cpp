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
        }
        if(t == TrueId && e == FalseId) {
            return i;
        }
        //searches a computed entry in the computed table via a HashMap
        auto comp_tb_res = computed_tb.find(hashFunction(i,t,e));
        //Checks for existing entry
        if (comp_tb_res != computed_tb.end())
        {
            //returns result stored at comp_entry
            return comp_tb_res->second;
        }
        BDD_ID x = topVar(i);
        BDD_ID high = ite(coFactorTrue(i, x), coFactorTrue(t, x), coFactorTrue(e, x));
        BDD_ID low = ite(coFactorFalse(i, x), coFactorFalse(t, x), coFactorFalse(e, x));
        if (high == low)
        {
            return high;
        };
        const BDD_ID res = find_or_add_unique_tb(x, high, low);
        computed_tb.insert(hashFunction(i,t,e), res);
        return res;
    }

    BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
        return 0;
    }

    BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){
        return 0;
    }

    BDD_ID Manager::coFactorTrue(BDD_ID f){
        return unique_tb.at(f).high;
    }

    BDD_ID Manager::coFactorFalse(BDD_ID f){
        return unique_tb.at(f).low;    
    }

    BDD_ID Manager::and2(BDD_ID a, BDD_ID b){
        return ite(a, b, FalseId);
    }

    BDD_ID Manager::or2(BDD_ID a, BDD_ID b){
        return ite(a, TrueId, b);
    }

    BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){
        return ite(a, neg(b), b);
    }

    BDD_ID Manager::neg(BDD_ID a){
        return ite(a, FalseId, TrueId);
    }

    BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){
        return ite(a, neg(b), TrueId);
    }

    BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){
        return ite(a, FalseId, neg(b));
    }

    BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){
        return ite(a, b, neg(b));
    }

    std::string Manager::getTopVarName(const BDD_ID &root){
        return unique_tb.at(root).label;
    }

    void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){
        nodes_of_root.emplace(root);
        if (root > TrueId){
            findNodes(coFactorTrue(root), nodes_of_root);
            findNodes(coFactorFalse(root), nodes_of_root);
        }
    }

    void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){

    }

    size_t Manager::uniqueTableSize(){
        return unique_tb.size();
    }

    void Manager::visualizeBDD(std::string filepath, BDD_ID &root){

    }
    
}

