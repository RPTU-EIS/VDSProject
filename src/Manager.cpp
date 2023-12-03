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
    bool Manager::isVariable(BDD_ID x)
    {

        for (auto &it : Table)
        {
            if (it.second.id == x)
            {
                if (it.second.label.size() == 1 &&
                    std::all_of(it.second.label.begin(), it.second.label.end(), ::isalpha))
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
    }

    BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e)
    {
        if (i == True()) {
            return t;
        } else if (t == False()) {
            return e;
        } else if (t == e) {
            return t;
        } else if (t == True() && e == False()){
            return i;
        } else if (auto search = Table.find({i,t,e}); search != Table.end()){
            return search->second.id;
        }
  }

    BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x)
    {
        BDD_ID T, F;
        Unique_Table_Key f_key;

        if(isConstant(f) || isConstant(x)) //f == constant
        {
            return f;
        }
        for(auto &it : Table)
        {
            if(it.second.id == f)
            {
                f_key = it.first;        
            }
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

    /**
    * @brief and2
    *
    * returns the id numbers required for the ite operation
    * @param &a and &b: variable names
    * @return returns the id numbers required for the ite operation
    */
    BDD_ID Manager::and2(std::string &a, std::string &b) {
        BDD_ID f_op, s_op;

        for (auto& it: Table ) {
            if (it.second.label == a)
            {
                f_op = it.second.id;
            }

            if (it.second.label == b)
            {
                s_op = it.second.id;
            }
        }
        return ite(f_op, s_op, 0);
    }


}