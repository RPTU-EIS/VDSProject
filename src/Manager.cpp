#include "Manager.h"
#include <stdexcept>
#include <iostream> //FIXME check final lib dependencies

namespace ClassProject {

    std::ostream& operator <<(std::ostream& stream, const Node& node) {
        return stream << node.label << " : " << node.data.low << "," << node.data.high << "," << node.data.topVar;
    }  

    const BDD_ID Manager::FALSE_ADDRESS = 0;
    const BDD_ID Manager::TRUE_ADDRESS = 1;

    const Node Manager::FALSE_NODE = {.label = "0", .data = {.topVar = Manager::FALSE_ADDRESS}};
    const Node Manager::TRUE_NODE =  {.label = "1", .data = {.topVar = Manager::TRUE_ADDRESS}};

    BDD_ID Manager::createVar(const std::string &label){}

    std::string Manager::getTopVarName(const BDD_ID &root){}

    void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){}

    void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){}

    size_t Manager::uniqueTableSize(){}    
    
    /**
    * @brief Manager class standard constructor
    * @author Victor Herbert
    * 
    * @return BDD_ID ID of top variable node
    */
    Manager::Manager(){
        nodes = {FALSE_NODE, TRUE_NODE};
    }

    Manager::Manager(std::vector<Node> nodes) : nodes(nodes){        
        if(!(nodes[0] == FALSE_NODE) || !(nodes[1] == TRUE_NODE)){
            throw std::invalid_argument("true and false nodes are invalid");
        }

        for(size_t i=0; i < nodes.size(); i++){                
            unique_table.insert({nodes[i].data, i});                
        }  
    }

    /**
     * @brief returns a pointer for the True node
     * @author Victor Herbert
     * 
     * @return const BDD_ID& of the True node
     */
    const BDD_ID &Manager::True(){
        return TRUE_ADDRESS;
    }

    /**
     * @brief returns a pointer for the False node
     * @author Victor Herbert
     * 
     * @return const BDD_ID& of the False node
     */
    const BDD_ID &Manager::False(){
        return FALSE_ADDRESS;
    }


    /**
     * @brief Checks if a given node is a constant
     * @author Victor Herbert
     * 
     * @return bool stating if the node is constant
     */
    bool Manager::isConstant(BDD_ID f){
        return (f == True() || f == False());
    }

    /**
     * @brief Checks if a given node is a variable
     * @author Victor Herbert
     * 
     * @return bool stating if the node is variable
     */
    bool Manager::isVariable(BDD_ID x){
        return !isConstant(x);//FIXME
    }

    /**
     * @brief Adds a new entry on the unique table only if there is not a previous entry with same data
     * @author Victor Herbert
     * 
     * @param data of the to be added node
     * @return BDD_ID of the added node
     */
    BDD_ID Manager::add_unique_table(NodeData data){
        if(unique_table.find(data) != unique_table.end()){
            nodes.push_back(Node{.data=data});
            unique_table[data] = nodes.size()-1;
        }
        return unique_table[data];
    }

    /**
     * @brief If Then Else routine
     * 
     * @param i ID of the If node
     * @param t ID of the Then node
     * @param e ID of the Else node
     * @return BDD_ID of the added node
     * 
     * Performs the IF Then Else recursive algorithm, adding nodes on demand
     */
    BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){        
        if(i == True()) return t;
        if(i == False()) return e;
        if(t == True() and e == False()) return i;
        if(t == e) return t;
        
        NodeData nodeData = {.low=t, .high=e, .topVar=i};
    
        if(computed_table.find(nodeData) == computed_table.end()){
            BDD_ID top = std::min(topVar(i), std::min(topVar(t), topVar(e)));
            BDD_ID high = ite(coFactorTrue(i,top), coFactorTrue(t,top), coFactorTrue(e,top));
            BDD_ID low = ite(coFactorFalse(i,top), coFactorFalse(t,top), coFactorFalse(e,top));

            if(high == low){
                computed_table[nodeData] = high;
            }
            else{
                BDD_ID result = add_unique_table({.low=low, .high=high, .topVar=top});
                computed_table[nodeData] = result;
            }
        }

        return computed_table[nodeData];
    }

    /**
     * @brief  
     * 
     * @param id 
     * @param a 
     * @param b 
     * @param op 
     * @return true 
     * @return false 
     */
    bool Manager::updateNodeLabel(BDD_ID id, BDD_ID a, BDD_ID b, std::string op){
        if(nodes[id].label == "")
            nodes[id].label = op + "(" + nodes[a].label + "," + nodes[b].label + ")";
    }

    /**
     * @brief creates a node that represents the AND operation between other two nodes
     * @author Victor Herbert
     * 
     * @param a operand
     * @param b operand 
     * @return BDD_ID of the node which encapsulates the operation
     */
    BDD_ID Manager::and2(BDD_ID a, BDD_ID b){
        BDD_ID id = ite(a,b, 0);
        updateNodeLabel(id, a, b, "and2");
        return id;
    }

    /**
     * @brief creates a node that represents the OR operation between other two nodes
     * @author Victor Herbert
     * 
     * @param a operand
     * @param b operand 
     * @return BDD_ID of the node which encapsulates the operation
     */
    BDD_ID Manager::or2(BDD_ID a, BDD_ID b){
        BDD_ID id = ite(a, 1, b);
        updateNodeLabel(id, a, b, "or2");
        return id;
    }

    /**
     * @brief creates a node that represents the XOR operation between other two nodes
     * @author Victor Herbert
     * 
     * @param a operand
     * @param b operand 
     * @return BDD_ID of the node which encapsulates the operation
     */
    BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){
        BDD_ID id = ite(a,neg(b), b);
        updateNodeLabel(id, a, b, "xor2");
        return id;
    }

    /**
     * @brief creates a node that represents the negated version of a node
     * @author Victor Herbert
     * 
     * @param a operand 
     * @return BDD_ID of the node which encapsulates the operation
     * 
     * //TODO
     */
    BDD_ID Manager::neg(BDD_ID a){    
        //TODO
        BDD_ID id;
        if(nodes[id].label == "")
            nodes[id].label = "~(" + nodes[a].label + ")";
        return id;
    }

    /**
     * @brief creates a node that represents the NAND operation between other two nodes
     * @author Victor Herbert
     * 
     * @param a operand
     * @param b operand 
     * @return BDD_ID of the node which encapsulates the operation
     */
    BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){
        BDD_ID id = ite(a,neg(b), 1);
        updateNodeLabel(id, a, b, "nand2");
        return id;
    }

    /**
     * @brief creates a node that represents the NOR operation between other two nodes
     * @author Victor Herbert
     * 
     * @param a operand
     * @param b operand 
     * @return BDD_ID of the node which encapsulates the operation
     */
    BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){
        BDD_ID id = ite(a, 0, neg(b));
        updateNodeLabel(id, a, b, "nor2");
        return id;
    }

    /**+
     * @brief creates a node that represents the XNOR operation between other two nodes
     * @author Victor Herbert
     * 
     * @param a operand
     * @param b operand 
     * @return BDD_ID of the node which encapsulates the operation
     */
    BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){
        BDD_ID id = ite(a,b, neg(b));
        updateNodeLabel(id, a, b, "xnor2");
        return id;
    }

    /**
     * @brief Creates an human readable visualization of the OBDD
     * 
     * @param filepath of the output
     * @param root of the subtree to be printed
     * 
     * Creates a .svg diagram of the desired subtree
     */
    void Manager::bfs(BDD_ID root, std::vector<BDD_ID> &order, std::vector<bool> &marc){
        if(!isConstant(root)){
            order.push_back(root);

            if(!marc[nodes[root].data.low]){
                marc[nodes[root].data.low] = true;
                bfs(nodes[root].data.low, order, marc);
            }

            if(!marc[nodes[root].data.high]){
                marc[nodes[root].data.high] = true;
                bfs(nodes[root].data.high, order, marc); 
            }
        }
    }


    /**
     * @brief Creates an human readable visualization of the OBDD
     * 
     * @param filepath of the output
     * @param root of the subtree to be printed
     * 
     * Creates a .svg diagram of the desired subtree
     */
    void Manager::visualizeBDD(std::string filepath, BDD_ID &root){
        //TODO implement filewrite
        std::vector<bool> marc (uniqueTableSize(), false);
        std::vector<BDD_ID> order;
        order.reserve(uniqueTableSize());

        bfs(root, order, marc);

        std::cout << "stateDiagram-v2\n";

        for (BDD_ID node : order){
            std::cout << nodes[node].label << " --> " << nodes[nodes[node].data.low].label << ": 0\n";
            std::cout << nodes[node].label << " --> " << nodes[nodes[node].data.high].label << ": 1\n";
        }
        std::cout << "classDef leaf fill:white\nclass 1 leaf\nclass 0 leaf";
    }


    /**
    * @brief returns the id of the top variable of the given node f
    * @author Kamel Fakih
    * 
    * @param f ID of node representing function f
    * @return BDD_ID ID of top variable node
    */
    BDD_ID Manager::topVar(BDD_ID f){
        return nodes[f].data.topVar;
    }

    /**
    * @brief returns the id of the high node of the given node f
    * @author Kamel Fakih
    * 
    * @param f ID of node representing function f
    * @return BDD_ID ID of top variable node
    */
    BDD_ID Manager::low(BDD_ID f){
        return nodes[f].data.low;
    }

    /**
    * @brief returns the id of the low of the given node f
    * @author Kamel Fakih
    * 
    * @param f ID of node representing function f
    * @return BDD_ID ID of top variable node
    */
    BDD_ID Manager::high(BDD_ID f){
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
    BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){

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
    BDD_ID Manager::coFactorTrue(BDD_ID f){
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
    BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){

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
    BDD_ID Manager::coFactorFalse(BDD_ID f){
        return coFactorFalse(f, topVar(f));
    }

}