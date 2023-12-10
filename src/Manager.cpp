#include "Manager.h"
#include <algorithm>

/**
 * @brief ClassProject Class.
 *
 * Me gusta la fafa.
 * @return What you can expect to get back from the function.
 */

namespace ClassProject
{

    Manager::Manager()
    {

        Table.emplace(Unique_Table_Key{0, 0, 0}, Unique_Table_Entry{"False", 0});

        Table.emplace(Unique_Table_Key{1, 1, 1}, Unique_Table_Entry{"True", 1});
    }

    /**
     * @brief createVar
     *
     * Creates a new variable with the given ID.
     * @param label String of the label of the variable.
     * @return returns the ID of the created variable.
     */
  
    

    BDD_ID Manager::createVar(const std::string &label)
    {

        Unique_Table_Key key_Var;
        BDD_ID ID = Table.size();
        key_Var.high = 1;
        key_Var.low = 0;
        key_Var.TopVar = ID;

        Unique_Table_Entry entry_Var;

        entry_Var.label = label;
        entry_Var.id = ID;

        Table.emplace(key_Var, entry_Var);
        return ID;
    };

    /**
     * @brief False
     *
     * Returns the id of the False node
     * @return const BDD_ID&
     */
    const BDD_ID &Manager::False()
    {
        static const BDD_ID ret = 0;
        return ret;
    }

    /**
     * @brief True
     *
     * Returns the id of the True node
     * @return const BDD_ID&
     */
    const BDD_ID &Manager::True()
    {
        static const BDD_ID ret = 1;
        return ret;
    }

    /**
     * @brief isConstant
     *
     * Returns true if the node is a leaf node.
     * @param f ID of the node.
     * @return returns true if the node is a leaf node.
     */
    bool Manager::isConstant(BDD_ID f)
    {
        for (auto &it : Table)
        {
            if (it.second.id == f)
            {
                if (it.first.low == it.first.high)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        return false;
    };

    /**
     * @brief isVariable
     *
     * checks whether the item corresponding to a given ID is a variable or not.
     * @param x: ID of the node.
     * @return returns true if the ID represents a variable.
     */
   bool Manager::isVariable( BDD_ID x) {

       for (auto & it : Table) {
           if (it.second.id == x) {
               if (it.second.label.size() == 1 &&
                   std::all_of(it.second.label.begin(), it.second.label.end(), ::isalpha)) {
                   return true;
               } else {
                   return false;
               }
           }
       }
       return false;
   }

    /**
      * @brief topVar
      *
      * returns the top variable ID of the given node.
      * @param f: ID of the node.
      * @return returns the ID of the top variable.
      */
    BDD_ID Manager::topVar(BDD_ID f) {
        if (isVariable(f) || isConstant(f)) {
            return f;
        }

        else {
            for (auto & it : Table) {
                if(it.second.id == f)
                {
                    return it.first.TopVar;
                }
            }
        }
        return False(); //In case of failure.
    }


    BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e)
    {
        if (i == True()) {
            return t;
        }else if (i == False()){
            return e;
        }else if (t == False()) {
            return e;
        } else if (t == e) {
            return t;
        } else if (t == True() && e == False()){
            return i;
        } else if (auto search = Table.find({i,t,e}); search != Table.end()){
            return search->second.id;
        }

        BDD_ID top_variable_t = isConstant(t) ? topVar(i) : std::min(topVar(i), topVar(t));

        BDD_ID top_variable_e = isConstant(e) ? topVar(i) : std::min(topVar(i), topVar(e));

        BDD_ID top_variable = std::min(top_variable_t, top_variable_e);

        BDD_ID f_high = ite(coFactorTrue(i, top_variable), coFactorTrue(t, top_variable), coFactorTrue(e, top_variable));

        BDD_ID f_low = ite(coFactorFalse(i, top_variable), coFactorFalse(t, top_variable), coFactorFalse(e, top_variable));

        if (f_high == f_low){
            return f_low;
        }

        if (auto search = computed_table.find({top_variable, f_high, f_low}); search != computed_table.end())
        {
            computed_table[{i, t, e}] = search->second;
            return search->second;
        }

        BDD_ID p = Table.size();
        Table.emplace(Unique_Table_Key({top_variable,f_high,f_low}),Unique_Table_Entry({std::to_string(p), p}));

        computed_table.emplace(Unique_Table_Key({top_variable,f_high,f_low}),Table.size());
        return p;
  }

    BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x)
    {
        BDD_ID T, F;
        Unique_Table_Key f_key;

        /* Find Key of f, which is used later */
        for(auto &it : Table)
        {
            if(it.second.id == f)
            {
                f_key = it.first;
            }
        }

        /* Terminal cases */
        if(isConstant(f) || isConstant(x) || f_key.TopVar > x)
        {
            return f;
        }

        if(f_key.TopVar == x)
        {
            return f_key.high;
        }
        else
        {
            T = coFactorTrue(f_key.high, x);
            F = coFactorTrue(f_key.low, x);
            return ite(f_key.TopVar, T, F);
        }
    }

    BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x)
    {
        BDD_ID T, F;
        Unique_Table_Key f_key;

        /* Find Key of f, which is used later */
        for(auto &it : Table)
        {
            if(it.second.id == f)
            {
                f_key = it.first;
            }
        }

        /* Terminal cases */
        if(isConstant(f) || isConstant(x) || f_key.TopVar > x)
        {
            return f;
        }

        if(f_key.TopVar == x)
        {
            return f_key.low;
        }
        else
        {
            T = coFactorFalse(f_key.high, x);
            F = coFactorFalse(f_key.low, x);
            return ite(f_key.TopVar, T, F);
        }
    }

    /**
    * @brief getTopVarName
    *
    * returns the name of the top variable of the given node.
    * @param root: ID of the node.
    * @return returns the name of the top variable.
    */
    std::string Manager::getTopVarName(const BDD_ID &root) {
        BDD_ID temp;
        for (auto &it: Table) {
            if (it.second.id == root) {
                temp = it.first.TopVar;
            }
        }
        for (auto &it: Table) {
            if (it.second.id == temp) {
                return it.second.label;
            }
        }
        return ""; //It should never reach here...
    }

    /**
   * @brief neg
   *
   * Creates a negated version of a given function and returns its ID.
   * @param a ID of the function to be negated.
   * @return: Returns the ID representing the negation of the given function.
   */

    BDD_ID Manager::neg(BDD_ID a)
    {
        return ite(a, 0 ,1);
    }


    /**
    * @brief and2
    *
    * returns the id numbers required for the ite operation
    * @param a and b: ID's of variables
    * @return returns the id numbers required for the ite operation
    */
    BDD_ID Manager::and2(BDD_ID a, BDD_ID b)
    {
        return ite(a, b, 0);
    }

    /**
    * @brief or2
    *
    * returns the id numbers required for the ite operation
    * @param a and b: ID's of variables
    * @return returns the id numbers required for the ite operation
    */
    BDD_ID Manager::or2(BDD_ID a, BDD_ID b) //ite(a, 1, b)
    {
        return ite(a, 1, b);
    }

    /**
    * @brief xor2
    *
    * returns the id numbers required for the ite operation
    * @param a and b: ID's of variables
    * @return returns the id numbers required for the ite operation
    */
    BDD_ID Manager::xor2(BDD_ID a, BDD_ID b) //ite(a, ~b, b)
    {
        return ite(a, neg(b), b);
    }

    /**
    * @brief nand2
    *
    * returns the id numbers required for the ite operation
    * @param a and b: ID's of variables
    * @return returns the id numbers required for the ite operation
    */

    BDD_ID Manager::nand2(BDD_ID a, BDD_ID b)
    {
        return ite(a, 1, b);
    }

    /**
    * @brief nor2
    *
    * returns the id numbers required for the ite operation
    * @param a and b: ID's of variables
    * @return returns the id numbers required for the ite operation
    */

    BDD_ID Manager::nor2(BDD_ID a, BDD_ID b)  //ite(a, 0, ~b)
    {
        return ite(a, 0, neg(b));
    }

    /**
    * @brief xnor2
    *
    * returns the id numbers required for the ite operation
    * @param a and b: ID's of variables
    * @return returns the id numbers required for the ite operation
    */

    BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b) //ite(a, b, ~b)
    {
        return ite(a, b, neg(b));
    }




}
        