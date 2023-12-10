//
// Created by Carolina P. Nogueira 2016
//

/**
 * @brief Me gusta la fafa.
 * 
 * A detailed description of why this algorithm works and what behavior to expect.
 * @param arg1 What the first argument to the function should be.
 * @return What you can expect to get back from the function.
 */


#include <iostream>
#include <string>
#include "Manager.h"


int main(int argc, char* argv[])
{
    ClassProject::Manager manager;
    manager.createVar("a");
    manager.createVar("b");
    manager.createVar("c");
    manager.createVar("d");
    manager.Table[{2,3,1}] = {"a+b", 6};
    manager.Table[{4,0,5}] = {"c*d", 7};
    manager.Table[{3,0,7}] = {"b*c*d", 8};
    manager.Table[{2,8,7}] = {"f", 9};


    std::cout << "START!" << std::endl;

    for(auto [key, value] : manager.Table){
        std::cout<<value.id<<":"<<key.high<<","<<key.low<<","<<key.TopVar<<std::endl;
    }
    ClassProject::BDD_ID id;
    manager.visualizeBDD("Test", id);
}