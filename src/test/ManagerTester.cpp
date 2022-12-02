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

TEST_F(ManagerTester, true_fn) {
    int result = 1;
    int expected_result = 0;

    result = manager->True();

    ASSERT_EQ(result, expected_result);
}
