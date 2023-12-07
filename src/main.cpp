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

    std::cout << "START!" << std::endl;

    for(auto [key, value] : manager.Table){
        std::cout<<value.id<<":"<<key.high<<","<<key.low<<","<<key.TopVar<<std::endl;
    }

    
}