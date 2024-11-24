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

    Manager::~Manager(){
    }

    BDD_ID createVar(const std::string &label){
    return 0;
    }

        const BDD_ID &True(){
        return 0;
        }

        const BDD_ID &False(){
        return 0;
        }

        bool isConstant(BDD_ID f){
        return 0;
        }

        bool isVariable(BDD_ID x){
        return 0;
        }

        BDD_ID topVar(BDD_ID f){
        return 0;
        }

        BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e){
        return 0;
        }

        BDD_ID coFactorTrue(BDD_ID f, BDD_ID x){
        return 0;
        }

        BDD_ID coFactorFalse(BDD_ID f, BDD_ID x){
        return 0;
        }

        BDD_ID coFactorTrue(BDD_ID f){
        return 0;
        }

        BDD_ID coFactorFalse(BDD_ID f){
        return 0;
        }

        BDD_ID and2(BDD_ID a, BDD_ID b){
        return 0;
        }

        BDD_ID or2(BDD_ID a, BDD_ID b){
        return 0;
        }

        BDD_ID xor2(BDD_ID a, BDD_ID b){
        return 0;
        }

        BDD_ID neg(BDD_ID a){
        return 0;
        }

        BDD_ID nand2(BDD_ID a, BDD_ID b){
        return 0;
        }

        BDD_ID nor2(BDD_ID a, BDD_ID b){
        return 0;
        }

        BDD_ID xnor2(BDD_ID a, BDD_ID b){
        return 0;
        }

        std::string getTopVarName(const BDD_ID &root){
        return 0;
        }

        void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){
        }

        void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){

        }

        size_t uniqueTableSize(){
        return 0;
        }

        void visualizeBDD(std::string filepath, BDD_ID &root){

        }
      
}

