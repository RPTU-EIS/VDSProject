//
// Created by ludwig on 22.11.16.
//

#include "Tests.h"
#include <gtest/gtest.h>

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TestTrue, TestReturn) {

    ClassProject::OBDDManager testClass = ClassProject::OBDDManager();    
    ASSERT_EQ(testClass.True(), 1);     
}

TEST(Testfalse, TestReturn) {

    ClassProject::OBDDManager testClass = ClassProject::OBDDManager();    
    ASSERT_EQ(testClass.False(), 0);  
}