#include "Manager.h"

using namespace ClassProject;

//Creates a new variable with the given label and returns its ID.
BDD_ID Manager::createVar(const std::string &label)
{
    return createNode(False(),True(),uniqueTableSize(),label);
}

//Returns the ID of the True node.
const BDD_ID &Manager::True()
{
    return TrueID;
}
//Returns the ID of the False node.
const BDD_ID &Manager::False()
{
    return FalseID;
}

//Returns true, if the given ID represents a leaf (terminal) node.
bool Manager::isConstant(BDD_ID f)
{
    return (f == True() || f == False());
}

//Returns true, if the given ID represents a variable.
bool Manager::isVariable(BDD_ID x)
{
    return (topVar(x) == x && x != True() && x != False());
}

//Returns the top variable ID of the given node.
BDD_ID Manager::topVar(BDD_ID f)
{
    return uniqueTable[f].TopVar;
}

//Implements the if-then-else algorithm. Returns the existing or new node that represents the given expression
BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e)
{
    if (isConstant(i)) return (i == True()) ? t : e;
    if (t == e) return t;
    if (computedTable.find(keyGen(i,t,e)) != computedTable.end()) return computedTable.at(keyGen(i,t,e));

    BDD_ID x = topVar(i);
    x = (!isConstant(t) && topVar(t) < x) ? topVar(t) : x;
    x = (!isConstant(e) && topVar(e) < x) ? topVar(e) : x;

    BDD_ID rHigh = ite(coFactorTrue(i, x), coFactorTrue(t, x), coFactorTrue(e, x));
    BDD_ID rLow = ite(coFactorFalse(i, x), coFactorFalse(t, x), coFactorFalse(e, x));
    if (rHigh == rLow) return rHigh;

    BDD_ID r = findOrAdd(x, rLow, rHigh);
    computedTable.insert({keyGen(i,t,e), r});
    return r;
}

//coFactorTrue(): Returns the positive co-factor of the function represented by ID f w.r.t. variable x. The second parameter is
//optional. If x is not specified, the co-factor is determined w.r.t. the top variable of f.
BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x)
{
    if (isConstant(f)) return f;
    if (topVar(f) == x) return uniqueTable[f].high;

    BDD_ID T = coFactorTrue(uniqueTable[f].high, x);
    BDD_ID F = coFactorTrue(uniqueTable[f].low, x);

    return ite(topVar(f),T,F);
}

//coFactorTrue(): Returns the positive co-factor of the function represented by ID f w.r.t. variable x. The second parameter is
//optional. If x is not specified, the co-factor is determined w.r.t. the top variable of f.
BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x)
{
    if (isConstant(f)) return f;
    if (topVar(f) == x) return uniqueTable[f].low;

    BDD_ID T = coFactorFalse(uniqueTable[f].high, x);
    BDD_ID F = coFactorFalse(uniqueTable[f].low, x);

    return ite(topVar(f),T,F);
}

BDD_ID Manager::coFactorTrue(BDD_ID f)
{
    return coFactorTrue(f, topVar(f));
}

BDD_ID Manager::coFactorFalse(BDD_ID f)
{
    return coFactorFalse(f, topVar(f));
}

BDD_ID Manager::neg(BDD_ID a)
{
    return ite(a, False(), True());
}

BDD_ID Manager::and2(BDD_ID a, BDD_ID b)
{
    return ite(a,b,False());
}

BDD_ID Manager::or2(BDD_ID a, BDD_ID b)
{
    return ite(a,True(),b);
}

BDD_ID Manager::xor2(BDD_ID a, BDD_ID b)
{
    return ite(a,neg(b),b);
}

BDD_ID Manager::nand2(BDD_ID a, BDD_ID b)
{
    return neg(and2(a,b));
}

BDD_ID Manager::nor2(BDD_ID a, BDD_ID b)
{
    return neg(or2(a,b));
}

BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b)
{
    return neg(xor2(a,b));
}

std::string Manager::getTopVarName(const BDD_ID &root)
{
    return uniqueTable[topVar(root)].label;
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root)
{
    nodes_of_root.insert(root);
    if (nodes_of_root.find(uniqueTable[root].low) ==nodes_of_root.end()) findNodes(uniqueTable[root].low, nodes_of_root);
    if (nodes_of_root.find(uniqueTable[root].high) ==nodes_of_root.end()) findNodes(uniqueTable[root].high, nodes_of_root);
}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root)
{
    std::set<BDD_ID> nodes;
    findNodes(root, nodes);
    for (auto node : nodes) if (!isConstant(node)) vars_of_root.insert(topVar(node));
}

size_t Manager::uniqueTableSize()
{
    return uniqueTable.size();
}
BDD_ID Manager::highSuccessor(BDD_ID a)
{
    return uniqueTable[a].high;
}

/**
 * Returns low successor of node
 * @param a id to be evaluated
 */
/*BDD_ID Manager::lowSuccessor(BDD_ID a)
{
    return uniqueTable[a].low;
}*/
std::string Manager::getLabel(BDD_ID f)
{
    return uniqueTable[f].label;
}



/*void Manager::visualizeBDD(std::string filepath, BDD_ID &root)
{
    std::ofstream outfile(filepath);

    if (!outfile.is_open()) {
        // Handle error: unable to open the file
        std::cerr << "Error: Unable to open file " << filepath << std::endl;
        return;
    }

    outfile << "digraph BDD {" << std::endl;

    // Call a recursive function to generate the DOT representation
    std::set<BDD_ID> visitedNodes;
    generateDot(outfile, root, visitedNodes);


    outfile << "}" << std::endl;

    outfile.close();

}

void Manager::generateDot(std::ofstream &outfile, const BDD_ID &root, std::set<BDD_ID> &visitedNodes)
{
    if (visitedNodes.count(root) > 0) return;
    visitedNodes.insert(root);
    // Output DOT representation for the current node
    outfile << "  " << uniqueTable[root].id << " [label=\"" << uniqueTable[root].label << "\"];" << std::endl;

    if (!isConstant(uniqueTable[root].high)) {
        outfile << "  " << uniqueTable[root].id << " -> " << uniqueTable[root].high << " [label=\"1\"];" << std::endl;
        generateDot(outfile, uniqueTable[root].high, visitedNodes);
    }

    if (!isConstant(uniqueTable[root].low)) {
        outfile << "  " << uniqueTable[root].id << " -> " << uniqueTable[root].low << " [label=\"0\"];" << std::endl;
        generateDot(outfile, uniqueTable[root].low, visitedNodes);
    }
} */

//Private functions

//creates a node in BDD
BDD_ID Manager::createNode(BDD_ID l, BDD_ID h, BDD_ID x, std::string label)
{
    uniqueTable.push_back(UniqueTableEntry {label, uniqueTableSize() - 1,h,l,x});
    uniqueTableMap.insert({keyGen(x,l,h), uniqueTableSize() - 1});
    return uniqueTableSize() - 1;
}

//Find or add unique table
BDD_ID Manager::findOrAdd(BDD_ID a, BDD_ID b, BDD_ID c)
{
    size_t key = keyGen(a, b, c);
    if (uniqueTableMap.find(key) != uniqueTableMap.end()) return uniqueTableMap.at(key);
    return createNode(b, c, a, "");
}

//Function to generate unique key to the uniqueTableMap: keyGen(TopVar, low, high)
//<< 21 shifts the bits by 21 places, which is equivalent to multiplying by 2^21.
//The expression a << 21 takes the ID a and multiplies it by 2^21, creating a large number that has 21 bits of space to accommodate the next ID b without overlapping.
size_t Manager::keyGen(BDD_ID a, BDD_ID b, BDD_ID c)
{
    return (((a << 21) + b) << 21) + c;
}

//Creates entries of False and True nodes in the unique table
Manager::Manager() {

    FalseID = createNode(0,0,0,"False");
    TrueID = createNode(1,1,1,"True");
}

Manager::~Manager() { }

