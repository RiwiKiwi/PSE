//
// Created by aburahman10 on 17/03/23.
//

#ifndef PROJECTSOFTWAREENGINEER_TESTSYSTEEM_H
#define PROJECTSOFTWAREENGINEER_TESTSYSTEEM_H

#endif //PROJECTSOFTWAREENGINEER_TESTSYSTEEM_H
#include "iostream"
#include "fstream"
#include "sys/stat.h"
#include <gtest/gtest.h>
#include <sstream>
#include "Systeem.h"
#include "simulationUtils.h"
using namespace std;

#include "Systeem.h"

class testSysteem : public ::testing::Test {};

/*
 * TESTEN VAN DE CONSTRUCTOR
 */

TEST_F(testSysteem, constructor)
{
    Systeem* systeem = new Systeem;
    ASSERT_TRUE(systeem->properlyInitialized());
    ASSERT_TRUE(systeem->getTrams().empty());
    ASSERT_TRUE(systeem->getStations().empty());
}

/*
 * TESTEN VAN GETTERS EN SETTERS
 */

// GETTER & SETTER STATIONS*
TEST_F(testSysteem,Stationsvector)
{
    Systeem* systeem = new Systeem;
    vector<Station*>get_stations = systeem->getStations();
    unsigned long int nul = 0;
    ASSERT_EQ(nul,get_stations.size());
    Station* station_one = new Station;
    Station* station_two = new Station;
    get_stations.push_back(station_one);
    get_stations.push_back(station_two);
    unsigned long int twee = 2;
    EXPECT_EQ(twee,get_stations.size());
    systeem->setStations(get_stations);
    ASSERT_TRUE(systeem->getStations() == get_stations);
}
//GETTER EN SETTER TRAMS*
TEST_F(testSysteem,Tramsvector)
{
    Systeem* systeem = new Systeem;
    vector<Tram*> get_trams = systeem->getTrams();
    unsigned long int nul = 0;
    ASSERT_EQ(nul,get_trams.size());
    Tram* tram_one = new Tram;
    Tram* tram_two = new Tram;
    get_trams.push_back(tram_one);
    get_trams.push_back(tram_two);
    unsigned long int twee = 2;
    EXPECT_EQ(twee,get_trams.size());
    systeem->setTrams(get_trams);
    ASSERT_TRUE(systeem->getTrams() == get_trams);
}
/*
 * TESTEN VAN INCONSISTENTIE VAN JE SYSTEEM
 */
// LOOPING THROUGH EVERY INCONSISTENT XML-FILES
TEST_F(testSysteem,inconsistentie_metronet){
    /*
     * ALLE INCONSISTENTIE VOORWAARDES WORDEN HIER GETEST VIA LOOP !
     */
    bool dir_status = DirectoryExists("../input_tests");
    ASSERT_TRUE(dir_status);
    unsigned int counter = 1;
    do{
        // INT TO STRING
        std::stringstream ss;
        ss << counter;
        // -------------
        string xml_file = "inconsistent_"+ss.str()+".xml";
        Systeem new_system;
        string import_file = "../input_tests/"+xml_file;
        MetroReader::importXml(import_file.c_str(),std::cerr,new_system);
        bool checker = new_system.checkConsistent();
        ASSERT_FALSE(checker);
        string output_file = "../input_tests/inconsistent"+ss.str()+"_output.txt";
        EXPECT_TRUE(FileExists(output_file));
        string expect_file =  "../input_tests/inconsistent"+ss.str()+"_expect.txt";
        EXPECT_TRUE(FileCompare(output_file,expect_file));
        ss.str() = "";
        counter++;
    }
    while(counter <= 6);
}


