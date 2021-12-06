#include"Tests.h"
#include"../Manager.h"
// using ::testing::Return;
TEST(Manager, True)
{
    ClassProject::Manager *manager = new ClassProject::Manager;
    
    EXPECT_TRUE(manager->True());
}

TEST(Manager, False)
{
    ClassProject::Manager *manager = new ClassProject::Manager;
    EXPECT_TRUE(0);
}