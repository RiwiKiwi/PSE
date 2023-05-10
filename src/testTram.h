//
// Created by aburahman10 on 17/03/23.
//

#ifndef PROJECTSOFTWAREENGINEER_TESTTRAM_H
#define PROJECTSOFTWAREENGINEER_TESTTRAM_H

#endif //PROJECTSOFTWAREENGINEER_TESTTRAM_H

#include "iostream"
#include "fstream"
#include "sys/stat.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace std;

#include "Station.h"
#include "Tram.h"
#include "MetroReader.h"

class testTram : public ::testing::Test {
public:
    bool check_type(const string& input_tramtype){
        const char* tram_types[] = {"PCC","Albatros","Stadslijner"};
        vector<string> trams_types(tram_types, tram_types+ sizeof(tram_types) / sizeof(tram_types[0]));
        for (vector<string>::iterator it = trams_types.begin(); it != trams_types.end(); ++it) {
            if (input_tramtype == *it){
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

TEST_F(testTram,constructor)
{
    Tram* make_tram = new Tram;
    ASSERT_TRUE(make_tram->properlyInitialized());
    ASSERT_TRUE(make_tram->getLijnNr() == 0);
    ASSERT_TRUE(make_tram->getSnelheid() == 0);
    ASSERT_TRUE(make_tram->getBeginStation() == NULL);
    ASSERT_TRUE(make_tram->getHuidigeStation() == NULL);
    ASSERT_TRUE(make_tram->getType() == "");
    ASSERT_TRUE(make_tram->getBeginstationname() == "");
    ASSERT_TRUE(make_tram->getVoertuignummer() == 0);
}

/*
 * TESTEN VAN GETTERS EN SETTERS
 */

// GETTER EN SETTER VOOR SNELHEID
TEST_F(testTram,Snelheid){
    Tram * tram = new Tram;
    ASSERT_EQ(tram->getSnelheid(),0);
    tram->setSnelheid(100);
    EXPECT_EQ(tram->getSnelheid(),100);
    ASSERT_NE(tram->getSnelheid(),0);
}
// GETTTER EN SETTER VOOR SETLIJNNUMMER
TEST_F(testTram,LijnNr){
    Tram* tram = new Tram;
    EXPECT_EQ(tram->getLijnNr(),0);
    tram->setLijnNr(50);
    EXPECT_EQ(50,tram->getLijnNr());
    ASSERT_NE(tram->getLijnNr(),0);
}
//GETTER EN SETTER VOOR BEGINSTATIONPOINTER
TEST_F(testTram,BeginStationpointer){
    Tram * tram = new Tram;
    ASSERT_EQ(NULL,tram->getBeginStation());
    Station* station = new Station;
    tram->setBeginStation(station);
    EXPECT_EQ(tram->getBeginStation(),station);
    // can''t be equal to nullpointer
    Tram* compare_tram = new Tram;
    ASSERT_NE(compare_tram->getBeginStation(),tram->getBeginStation());
}
//GETTER EN SETTER VOOR HUIDIGESTATIONPOINTER
TEST_F(testTram,HuidigeStationpointer)
{
    Tram* tram = new Tram;
    ASSERT_EQ(NULL,tram->getHuidigeStation());
    Station* station = new Station;
    tram->setHuidigeStation(station);
    EXPECT_EQ(tram->getHuidigeStation(),station);
    Tram* compare_tram = new Tram;
    ASSERT_NE(tram->getHuidigeStation(),compare_tram->getHuidigeStation());
}
// GETTER EN SETTER VOOR TYPE
TEST_F(testTram,Type){
    Tram* tram = new Tram;
    ASSERT_EQ(tram->getType(),"");
    EXPECT_FALSE(check_type(tram->getType()));
    tram->setType("Albatros");
    EXPECT_EQ(tram->getType(),"Albatros");
    ASSERT_NE(tram->getType(),"");
    EXPECT_TRUE(check_type(tram->getType()));

}
// GETTER EN SETTER VOOR BEGINSTATIONNAMESTRING
TEST_F(testTram,Beginstationname){
    Tram* tram = new Tram;
    ASSERT_EQ(tram->getBeginstationname(),"");
    tram->setBeginstationname("D");
    EXPECT_EQ(tram->getBeginstationname(),"D");
    ASSERT_NE(tram->getBeginstationname(),"");
}
//GETTER EN SETTER VOOR VOERTUIGNUMMER
TEST_F(testTram,Voertuignummer){
    Tram* tram = new Tram;
    ASSERT_EQ(tram->getVoertuignummer(),0);
    tram->setVoertuignummer(10);
    EXPECT_EQ(tram->getVoertuignummer(),10);
    ASSERT_NE(tram->getVoertuignummer(),0);
}
//TESTEN OP VERSCHILLENDE TYPES VOOR INITIALIZATIE VAN TRAM
TEST_F(testTram,types_test){
    const char* tram_types[] = {"Albatros","Stadslijner","PCC","Albatros","Albatros","Albatros"};
    vector<string> trams_types(tram_types, tram_types + sizeof(tram_types) / sizeof(tram_types[0]));
    for (unsigned int i = 0; i < trams_types.size(); ++i) {
        EXPECT_TRUE(check_type(trams_types[i]));
    }
    const char* tram_fout_types[] = {"hallo", "PCCS", "TRAINS", "icc", "DFB", "UA"};
    vector<string> trams_fout_types(tram_fout_types, tram_fout_types + sizeof(tram_fout_types) / sizeof(tram_fout_types[0]));
    for (unsigned int i = 0; i < trams_fout_types.size(); ++i) {
        EXPECT_FALSE(check_type(trams_fout_types[i]));
    }
}
/*
 * CONTRACT VIOLATIONS (SETTERS)
 */

// lijnnummer kan ook niet signed zijn!
TEST_F(testTram,violate_setLijnnummer)
{
    Tram *tram = new Tram;
    EXPECT_DEATH(tram->setLijnNr(-1),"setLijnNr must be equal or greater than 0");
    ASSERT_EQ(tram->getLijnNr(),0);
}
// snelheid kan geen signed integer zijn !
TEST_F(testTram,violate_setSnelheid)
{
    Tram *tram = new Tram;
    EXPECT_DEATH(tram->setSnelheid(-1),"setSnelheid precondition failed");
    ASSERT_EQ(tram->getSnelheid(),0);
}
// Beginstation moet ook initialized pointer zijn !
TEST_F(testTram,violate_setBeginStation)
{
    Tram *tram = new Tram;
    EXPECT_DEATH(tram->setBeginStation(NULL),"setBeginStation precondition failed");
    ASSERT_EQ(NULL, tram->getBeginStation());
}
// Currentstation moet een initialized pointer zijn !
TEST_F(testTram,violate_setHuidigeStation)
{
    Tram *tram = new Tram;
    EXPECT_DEATH(tram->setHuidigeStation(NULL),"setHuidigeStation precondition failed");
    ASSERT_EQ(NULL,tram->getHuidigeStation());
}
// Lege string als settype mag niet !
TEST_F(testTram,violate_setType){
    Tram * tram = new Tram;
    EXPECT_DEATH(tram->setType(""),"setType precondition failed");
    ASSERT_EQ(tram->getType(),"");
}
// Lijnnummer mag geen signed int zijn
TEST_F(testTram,violate_setVoertuignummer){
    Tram* tram = new Tram;
    EXPECT_DEATH(tram->setVoertuignummer(-1),"setVoertuignummer precondition failed");
    ASSERT_EQ(tram->getVoertuignummer(),0);
}
// Lege string als setname voor beginstation mag niet !
TEST_F(testTram,checksetbeginstationstring){
    Tram* tram = new Tram;
    EXPECT_DEATH(tram->setBeginstationname("\0"),"setBeginstationname precondition failed");
    ASSERT_EQ(tram->getBeginstationname(),"");
}
