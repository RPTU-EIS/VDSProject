//
// Created by eloi on 12/1/22.
//

#ifndef VDSPROJECT_MANAGERTESTER_H
#define VDSPROJECT_MANAGERTESTER_H

#include "Tests.h"
#include <gtest/gtest.h>
#include "Manager.h"

class ManagerTester : public ::testing::Test {
public:
    // Will be called ONLY ONCE at start of testing
    static void SetUpTestSuite();

    // Will be called ONLY ONCE at the end of testing
    static void TearDownTestSuite();

    // Will be called before EVERY unit test
    virtual void SetUp();

    // Will be called after EVERY unit test
    virtual void TearDown();

    static ClassProject::Group7Manager* manager;
};


#endif //VDSPROJECT_MANAGERTESTER_H

