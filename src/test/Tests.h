//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include <gtest/gtest.h>
#include "../Manager.h"
#include <vector>

namespace ClassProject {
    class Managertest : public testing::Test {
    protected:

        ClassProject::Manager lectureExample;

        void SetUp() override {
            lectureExample.nodes = {
                ClassProject::Manager::FALSE_NODE,
                ClassProject::Manager::TRUE_NODE
            };
        }

    };

    TEST_F(Managertest, VisualizeBDDTest) {
        lectureExample.visualizeBDD("", (const BDD_ID) lectureExample.nodes.size()-1);
    }
}

#endif