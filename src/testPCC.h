//
// Created by riwi on 7/05/23.
//

#ifndef PROJECTSOFTWAREENGINEER_TESTPCC_H
#define PROJECTSOFTWAREENGINEER_TESTPCC_H

#endif //PROJECTSOFTWAREENGINEER_TESTPCC_H
#include <gtest/gtest.h>
#include "Systeem.h"
#include "simulationUtils.h"
#include "MetroOutput.h"
class testPCC: public ::testing::Test{};

/*
 * TESTEN VAN DE CONSTRUCTOR
 */
TEST_F(testPCC,constructor){
    PCC* make_pcc = new PCC;
    EXPECT_TRUE(make_pcc->properlyInitialized());
}
/*
 * TESTEN VAN GETTERS EN SETTERS
 */
// GETTER EN SETTER VAN STOREPCCMOVES
TEST_F(testPCC,storePCCmoves){
    PCC* make_pcc = new PCC;
    ASSERT_TRUE(make_pcc->getStorepccMoves() == 0);
    ASSERT_TRUE(make_pcc->getCurrMoves() == 0);
    make_pcc->setStorepccMoves(9);
    EXPECT_TRUE(make_pcc->getStorepccMoves() == 9);
    EXPECT_FALSE(make_pcc->getStorepccMoves() == 0);
    EXPECT_FALSE(make_pcc->getStorepccMoves() == 9000);
}
// GETTER EN SETTER VAN STOREPCCWAITS
TEST_F(testPCC,storePCCwaits){
    PCC* make_pcc = new PCC;
    ASSERT_TRUE(make_pcc->getStorepccWaits() == 0);
    ASSERT_TRUE(make_pcc->getCurrWaits() == 0);
    make_pcc->setStorepccWaits(10);
    EXPECT_TRUE(make_pcc->getStorepccWaits() == 10);
    EXPECT_FALSE(make_pcc->getStorepccWaits() == 0);
    EXPECT_FALSE(make_pcc->getStorepccWaits() == 90);
}
//GETTER EN SETTER VAN CURRMOVES
TEST_F(testPCC,currMoves){
    PCC* make_pcc = new PCC;
    ASSERT_TRUE(make_pcc->getStorepccWaits() == 0);
    ASSERT_TRUE(make_pcc->getStorepccMoves() == 0);
    ASSERT_TRUE(make_pcc->getCurrMoves() == 0);
    make_pcc->setCurrMoves(90);
    EXPECT_TRUE(make_pcc->getCurrMoves() == 90);
    EXPECT_FALSE(make_pcc->getCurrMoves() == 18);
}
// GETTER EN SETTER VAN CURRWAITS
TEST_F(testPCC,currWaits){
    PCC* make_pcc = new PCC;
    ASSERT_TRUE(make_pcc->getStorepccWaits() == 0);
    ASSERT_TRUE(make_pcc->getStorepccMoves() == 0);
    ASSERT_TRUE(make_pcc->getCurrWaits() == 0);
    make_pcc->setCurrWaits(100);
    EXPECT_TRUE(make_pcc->getCurrWaits() == 100);
    EXPECT_FALSE(make_pcc->getCurrWaits() == 10000);
}
/*
 * TESTEN VAN CONTRACT VIOLATIONS
 */
//SETTER VAN STOREMOVESLEFT MAG NIET UNSIGNED ZIJN
TEST_F(testPCC,violate_storemoves){
    PCC* make_pcc = new PCC;
    ASSERT_TRUE(make_pcc->getStorepccWaits() == 0);
    ASSERT_TRUE(make_pcc->getStorepccMoves() == 0);
    ASSERT_TRUE(make_pcc->getCurrWaits() == 0);
    ASSERT_TRUE(make_pcc->getCurrMoves() == 0);
    EXPECT_DEATH(make_pcc->setStorepccMoves(-12),"setStorepccMoves precondition failed");
    ASSERT_NE(make_pcc->getStorepccMoves(),-12);
}
// SETTER VAN STOREWAITSLEFFT MAG NIET UNSIGNED ZIJN
TEST_F(testPCC,violate_storewaits){
    PCC* make_pcc = new PCC;
    ASSERT_TRUE(make_pcc->getStorepccWaits() == 0);
    ASSERT_TRUE(make_pcc->getStorepccMoves() == 0);
    ASSERT_TRUE(make_pcc->getCurrWaits() == 0);
    ASSERT_TRUE(make_pcc->getCurrMoves() == 0);
    EXPECT_DEATH(make_pcc->setStorepccWaits(-10),"setStorepccWaits precondition failed");
    ASSERT_NE(make_pcc->getStorepccWaits(),-10);
}

TEST_F(testPCC,violate_currmoves){
    PCC* make_pcc = new PCC;
    ASSERT_TRUE(make_pcc->getStorepccWaits() == 0);
    ASSERT_TRUE(make_pcc->getStorepccMoves() == 0);
    ASSERT_TRUE(make_pcc->getCurrWaits() == 0);
    ASSERT_TRUE(make_pcc->getCurrMoves() == 0);
    EXPECT_DEATH(make_pcc->setCurrMoves(-100),"setCurrMoves precondition failed");
    ASSERT_NE(make_pcc->getCurrMoves(),-100);
}

TEST_F(testPCC,violate_currwaits)
{
    PCC* make_pcc = new PCC;
    ASSERT_TRUE(make_pcc->getStorepccWaits() == 0);
    ASSERT_TRUE(make_pcc->getStorepccMoves() == 0);
    ASSERT_TRUE(make_pcc->getCurrWaits() == 0);
    ASSERT_TRUE(make_pcc->getCurrMoves() == 0);
    EXPECT_DEATH(make_pcc->setCurrWaits(-10),"setCurrWaits precondition failed");
    ASSERT_NE(make_pcc->getCurrWaits(),-10);
}
