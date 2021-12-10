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

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
