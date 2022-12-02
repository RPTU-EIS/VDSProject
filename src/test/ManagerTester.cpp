//
// Created by eloi on 12/1/22.
//

#include "ManagerTester.h"

ClassProject::Group7Manager *ManagerTester::manager;

void ManagerTester::SetUpTestSuite() {
    if (manager == nullptr) {
        manager = new ClassProject::Group7Manager;
    }
}

void ManagerTester::TearDownTestSuite() {
    if (manager != nullptr)
        delete manager;
    manager = nullptr;
}

void ManagerTester::SetUp() {
}

void ManagerTester::TearDown() {
}

TEST_F(ManagerTester, fn_True) {
    ClassProject::BDD_ID expected_id = 1;
    auto id = manager->True();

    ASSERT_EQ(expected_id, id);
}

TEST_F(ManagerTester, fn_False) {
    ClassProject::BDD_ID expected_id = 0;
    auto id = manager->False();

    ASSERT_EQ(expected_id, id);
}

TEST_F(ManagerTester, fn_uniqueTableSize) {
    size_t expected_result = 2;
    size_t result = manager->uniqueTableSize();

    EXPECT_EQ(result, expected_result);
}