//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"
#include "../Manager.cpp"
namespace ClassProject {
//    TEST(uniqueTableSizeTest, ChecksSizeOfTable) {
//        EXPECT_EQ(uniqueTableSize(), 3);
//    }

    int main(int argc, char *argv[]) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

}
