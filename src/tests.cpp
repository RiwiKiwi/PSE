//
// Created by aburahman10 on 17/03/23.
//

#include "DesignByContract.h"
#include "gtest/gtest.h"
#include "testInput.h"
#include "testTram.h"
#include "testStation.h"
#include "testSysteem.h"
#include "testOutput.h"
#include "testPCC.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}