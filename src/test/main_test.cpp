//
// Created by ludwig on 22.11.16.
//


#include "Tests.h"
TEST(test1, t1) {
    ASSERT_EQ(1, 1);
}

TEST(test2, t2) {
ASSERT_EQ(1, 2);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
