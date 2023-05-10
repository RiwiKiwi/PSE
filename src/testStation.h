//
// Created by aburahman10 on 17/03/23.
//

#ifndef PROJECTSOFTWAREENGINEER_TESTSTATION_H
#define PROJECTSOFTWAREENGINEER_TESTSTATION_H

#endif //PROJECTSOFTWAREENGINEER_TESTSTATION_H

#include "iostream"
#include "fstream"
#include "sys/stat.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace std;

#include "Station.h"

class testStation : public ::testing::Test {
public:
    bool check_type(const string& input_type){
        const char* station_types[] = {"Metrostation","Halte"};
        vector<string> stations_types(station_types, station_types+ sizeof(station_types) / sizeof(station_types[0]));
        for (vector<string>::iterator it = stations_types.begin(); it != stations_types.end(); ++it) {
            if (input_type == *it){
                return true;
            }else{
                continue;
            }
        }
        return false;
    };
};


/*
 * TESTEN VAN DE CONSTRUCTOR
 */

TEST_F(testStation, constructor)
{
    Station* new_station = new Station;
    ASSERT_TRUE(new_station->properlyInitialized());
    ASSERT_TRUE(new_station->getNaam() == "");
    ASSERT_TRUE(new_station->getVolgende() == NULL);
    ASSERT_TRUE(new_station->getVorige() == NULL);
    ASSERT_TRUE(new_station->getNext() == "");
    ASSERT_TRUE(new_station->getPrev() == "");
    ASSERT_TRUE(new_station->getType() == "");
    ASSERT_TRUE(new_station->getSpoor() == 0);
    ASSERT_TRUE(new_station->getSpoorNrs().empty());
}

/*
 * TESTEN VAN GETTERS EN SETTERS
 */

// GETTER EN SETTER STRING NAAM
TEST_F(testStation, Naam)
{
    Station* station = new Station;
    ASSERT_EQ("",station->getNaam());
    station->setNaam("R");
    EXPECT_EQ(station->getNaam(),"R");
}

//GETTER EN SETTER VAN VOLGENDE
TEST_F(testStation, checkVolgendeStation)
{
    Station* station = new Station;
    ASSERT_EQ(NULL,station->getVolgende());
    Station* station_next = new Station;
    station->setVolgende(station_next);
    EXPECT_TRUE(station->getVolgende() == station_next);
}
// GETTER EN SETTER VOOR VORIGE
TEST_F(testStation, checkVorigeStation)
{
    Station* station = new Station;
    ASSERT_EQ(NULL,station->getVorige());
    Station* vorige_station = new Station;
    station->setVorige(vorige_station);
    EXPECT_EQ(vorige_station,station->getVorige());
}
// TESTING GETTER EN SETTER OF VOLGEND AND VORIG POINTERS TE SAMEN
TEST_F(testStation,Volgend_and_Vorig){
    Station* mid_station = new Station;
    ASSERT_EQ(NULL,mid_station->getVorige());
    ASSERT_EQ(NULL,mid_station->getVolgende());
    Station* next_station = new Station;
    Station* previous_station = new Station;
    mid_station->setVorige(previous_station);
    mid_station->setVolgende(next_station);
    EXPECT_EQ(next_station,mid_station->getVolgende());
    EXPECT_EQ(previous_station,mid_station->getVorige());
    EXPECT_EQ(NULL,next_station->getVolgende());
    EXPECT_EQ(NULL,previous_station->getVorige());
}
// GETTER EN SETTER VAN STRING PREV
TEST_F(testStation,Prev){
    Station* make_station = new Station;
    ASSERT_EQ(make_station->getPrev(),"");
    Station* prev_station = new Station;
    prev_station->setNaam("A");
    make_station->setPrev(prev_station->getNaam());
    EXPECT_EQ(prev_station->getNaam(),make_station->getPrev());
}
// GETTER EN SETTER VAN STRING NEXT

TEST_F(testStation,Next){
    Station* make_station = new Station;
    ASSERT_EQ(make_station->getNext(),"");
    Station* next_station = new Station;
    next_station->setNaam("A");
    make_station->setNext(next_station->getNaam());
    EXPECT_EQ(next_station->getNaam(), make_station->getNext());
}

// GETTERS EN SETTERS VAN NEXT EN PREV TE SAMEN

TEST_F(testStation,Prev_and_Next){
    Station* mid_station = new Station;
    ASSERT_EQ(mid_station->getNaam(),"");
    ASSERT_EQ(mid_station->getNext(),"");
    ASSERT_EQ(mid_station->getPrev(),"");
    mid_station->setNaam("B");
    EXPECT_EQ("B",mid_station->getNaam());
    Station* prev_station = new Station;
    ASSERT_EQ(prev_station->getNaam(),"");
    ASSERT_EQ(prev_station->getNext(),"");
    ASSERT_EQ(prev_station->getPrev(),"");
    prev_station->setNaam("A");
    EXPECT_EQ("A",prev_station->getNaam());
    mid_station->setPrev(prev_station->getNaam());
    prev_station->setNext(mid_station->getNaam());
    EXPECT_EQ(prev_station->getNaam(),mid_station->getPrev());
    EXPECT_EQ(mid_station->getNaam(),prev_station->getNext());
    EXPECT_EQ(prev_station->getPrev(),"");
    Station* next_station = new Station;
    ASSERT_EQ(next_station->getNaam(),"");
    ASSERT_EQ(next_station->getNext(),"");
    ASSERT_EQ(next_station->getPrev(),"");
    next_station->setNaam("C");
    EXPECT_EQ("C",next_station->getNaam());
    mid_station->setNext(next_station->getNaam());
    next_station->setPrev(mid_station->getNaam());
    EXPECT_EQ(next_station->getNaam(),mid_station->getNext());
    EXPECT_EQ(mid_station->getNaam(),next_station->getPrev());
    EXPECT_EQ(next_station->getNext(),"");
}

// GETTER EN SETTER VAN VECTOR SPOORNUMMERS
TEST_F(testStation,spoorNrs){
    Station* station = new Station;
    unsigned long int nul = 0;
    ASSERT_EQ(nul,station->getSpoorNrs().size());
    vector<int>my_numbers;
    my_numbers.push_back(12);
    my_numbers.push_back(13);
    EXPECT_TRUE(my_numbers.size() == 2);
    station->setSpoorNrs(my_numbers);
    EXPECT_EQ(my_numbers,station->getSpoorNrs());
    ASSERT_NE(station->getSpoorNrs().size(),nul);
}
// GETTER EN SETTER VAN INTEGER SPOORNUMMER

TEST_F(testStation,spoornummer){
    Station* make_station = new Station;
    ASSERT_EQ(make_station->getSpoor(),0);
    make_station->setSpoor(12);
    EXPECT_EQ(12,make_station->getSpoor());
}
// GETTER EN SETTER VAN STRING TYPE
TEST_F(testStation,type){
    Station* make_station = new Station;
    ASSERT_EQ(make_station->getType(),"");
    EXPECT_FALSE(check_type(make_station->getType()));
    make_station->setType("Metrostation");
    EXPECT_EQ("Metrostation",make_station->getType());
    ASSERT_NE(make_station->getType(),"");
    EXPECT_TRUE(check_type(make_station->getType()));
}
// TEST OP INGEVEN VAN VERSCHILLENDE TYPES VAN STATIONS
TEST_F(testStation,types_test){
    const char* station_types[] = {"Metrostation","Halte","Metrostation","Halte","Halte","Halte"};
    vector<string> stations_types(station_types, station_types+ sizeof(station_types) / sizeof(station_types[0]));
    for (unsigned int i = 0; i < stations_types.size(); ++i) {
        EXPECT_TRUE(check_type(stations_types[i]));
    }
    const char* station_fout_types[] = {"hallo","PCCS","TRAINS","icc","DFB","UA"};
    vector<string> stations_fout_types(station_fout_types, station_fout_types+ sizeof(station_fout_types) / sizeof(station_fout_types[0]));
    for (unsigned int i = 0; i < stations_fout_types.size(); ++i) {
        EXPECT_FALSE(check_type(stations_fout_types[i]));
    }
}
/*
 * CONTRACT VIOLATIONS
 */

// LEGE STRING ALS NAAM INITIALIZATIE
TEST_F(testStation,violate_checksetNaam)
{
    Station* my_station = new Station;
    EXPECT_DEATH(my_station->setNaam("\0"),"NAME CANNOT BE EMPTY");
    ASSERT_EQ(my_station->getNaam(),"");
}
// NULLPOINTER ALS VOLGENDE STATION
TEST_F(testStation,violate_checksetVolgende)
{
    Station* station = new Station;
    EXPECT_DEATH(station->setVolgende(NULL),"setVolgende nextptr CANNOT BE NULL");
    ASSERT_EQ(NULL,station->getVolgende());
}
// NULLPOINTER ALS VORIGE STATION
TEST_F(testStation,violate_cheksetVorige){
    Station* station = new Station;
    EXPECT_DEATH(station->setVorige(NULL),"setVorige prevptr CANNOT BE NULL");
    ASSERT_EQ(NULL,station->getVorige());
}
// LEGE STRING ALS NEXT INITIALIZATIE
TEST_F(testStation,violate_setNext){
    Station* station = new Station;
    EXPECT_DEATH(station->setNext("\0"),"setNext cannot be empty string");
    ASSERT_EQ(station->getNext(),"");
}
// LEGE STRING ALS PREV INITIALIZATIE
TEST_F(testStation,violate_setPrev){
    Station* station = new Station;
    EXPECT_DEATH(station->setPrev("\0"),"setPrev cannot be empty string");
    ASSERT_EQ(station->getPrev(),"");
}
// LEGE VECTOR GEVEN AAN EEN STATION => GEEN SPOREN
TEST_F(testStation,violate_setSpoornmr){
    Station* station = new Station;
    vector<int> leeg;
    EXPECT_DEATH(station->setSpoorNrs(leeg),"setSpporNrs as an empty vector as input!");
    unsigned int long nul = 0;
    ASSERT_EQ(station->getSpoorNrs().size(),nul);
}
// SIGNED INTEGER ALS SPOORNUMMER
TEST_F(testStation,violate_checksetSpoor){
    Station* station = new Station;
    EXPECT_DEATH(station->setSpoor(-1),"setSpoor precondition failed");
    ASSERT_EQ(station->getSpoor(),0);
}
// LEGE STRING ALS TYPE
TEST_F(testStation,violate_checkType){
    Station* station = new Station;
    EXPECT_DEATH(station->setType("\0"),"setType postcondition failed");
    ASSERT_EQ(station->getType(),"");
}



