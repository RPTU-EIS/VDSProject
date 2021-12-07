//
// Created by hiand on 07/12/2021.
//

#include "Tests.h"

using testing::Eq;

namespace {
    class ClassDeclaration : public testing::Test {
    public:
        ClassName obj;
        ClassDeclaration(){
            obj;
        }
    };
}

TEST_F(ClassDeclaration, nameOfTheTest1){
    ASSERT_EQ("","");
}

TEST_F(ClassDeclaration, nameOfTheTest2){
    ASSERT_EQ("","1");
}