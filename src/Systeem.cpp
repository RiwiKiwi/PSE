//
// Created by aburahman10 on 6/03/23.
//

#include "Systeem.h"
#include "iostream"
#include "Station.h"
#include "vector"
#include <fstream>
#include "DesignByContract.h"
#include "unistd.h"
#include "algorithm"
using namespace std;

void Systeem::checkConsistent()
{
    REQUIRE(this->properlyInitialized(), "checkConsistent precondition failed");
    inconsistent = 0;
    //VOORWAARDE 1 : PREVIOUS AND NEXT OF EVERY STATIONS CAN' T BE NULL
    for (unsigned int stats = 0; stats < stations.size(); stats++)
    {
        // 1ste stap consistentie
        if (stations[stats]->getVolgende() == NULL or stations[stats]->getVorige() == NULL)
        {
            ofstream one("../input_tests/inconsistent1_output.txt");
            one <<"XML PARTIAL IMPORT: Inconsistent voorwaarde 1 failed";
            inconsistent = 1;
            one.close();
            break;
        }else{
            inconsistent = 0;
            continue;
        }
    }
    // VOORWAARDE 2 : THE LIJNNMR OF A TRAM HAS TO BE THE SAME AS THE SPOORNUMMER IN IT'S STARTING STATION
    bool lijnNR_bestaat = false;
    for (unsigned int tram = 0; tram < trams.size(); tram++)
    {
        // get the lijnnummer of this specific tram !
        int check_lijnnummer = trams[tram]->getLijnNr();
        string get_starting_station = trams[tram]->getBeginstationname();
        for (unsigned int i = 0; i < stations.size(); ++i) {
            // i found the starting station
            if (stations[i]->getNaam() == get_starting_station){
                // We moeten doorheen dees bs loopen
                vector<int>check_vector = stations[i]->getSpoorNrs();
                //going through all sporen of this station to check if 1 of the spoornumber is the same as the lijnnmr
                for (unsigned int j = 0 ; j < check_vector.size(); ++j) {
                    if (check_lijnnummer == check_vector[j]){
                        lijnNR_bestaat = true;
                        break;
                    }else{
                        continue;
                    }
                }
            }
            else
            {
                continue;
            }
        }
        if (!lijnNR_bestaat)
        {
            ofstream two("../input_tests/inconsistent2_output.txt");
            two <<"XML PARTIAL IMPORT: Inconsistent voorwaarde 2 failed";
            inconsistent = 1;
            two.close();
            break;
        }
    }
    //VOORWAARDE 3: EVERY SPOOR MUST HAVE A TRAM
    bool lijn_bestaat = false;
    for (unsigned int stats = 0; stats < stations.size(); stats++)
    {
        //my checking station
        Station* checking_station = stations[stats];
        //get the vector of it's spoornummer
        vector<int> spoor_NRS = checking_station->getSpoorNrs();
        for (unsigned int tram = 0; tram < trams.size(); tram++)
        {
            for (unsigned int spoornr = 0; spoornr < spoor_NRS.size(); spoornr++)
            {
                if (spoor_NRS[spoornr] == trams[tram]->getLijnNr())
                {
                    lijn_bestaat = true;
                    break;
                }
            }
        }
        if (!lijn_bestaat)
        {
            ofstream three("../input_tests/inconsistent3_output.txt");
            three << "XML PARTIAL IMPORT: Inconsistent voorwaarde 3 failed";
            inconsistent = 1;
            three.close();
            break;
        }
    }
    //VOORWAARDE 4 : STARTING STATION OF A TRAM HAS TO BE IN THE METRONET !
    // NOTE => ALS U BEGIN STATTION VAN U TRAM EEN NULLPOINTER IS DAN BESTAAT DIE STATION SOWISO NIET ..
    for (unsigned int tram = 0; tram < trams.size(); tram++) {
        Tram* checking_tram = trams[tram];
        if (checking_tram->getBeginStation() == NULL){
            ofstream four("../input_tests/inconsistent4_output.txt");
            four << "XML PARTIAL IMPORT: Inconsistent voorwaarde 4 failed";
            inconsistent = 1;
            four.close();
            break;
        }else{
            // DIT BETEKENT DAT DIT STATION IN ONZE METRONET BESTAAT DUS CONTINUE
            continue;
        }
    }
    // RIWAAZ: VOORWAARDE 5: EVERY SPOORNUMMER CAN' T APPEAR DOUBLE IN THE VECTOR !
    for (unsigned int i = 0; i < stations.size(); ++i) {
        Station* checking_station = stations[i];
        vector<int>checking_station_sporen = checking_station->getSpoorNrs();
        for (unsigned int j = 0; j < checking_station_sporen.size(); ++j) {
            int result = std::count(checking_station_sporen.begin(),checking_station_sporen.end(),checking_station_sporen[j]);
            if (result >= 2){
                ofstream five("../input_tests/inconsistent5_output.txt");
                five << "XML PARTIAL IMPORT: Inconsistent voorwaarde 5 failed";
                inconsistent = 1;
                five.close();
                goto final;
            }else{
                continue;
            }
        }
    }

    // RIWAAZ: DEES IS EEN EXTRA CHECK DA IK ZELF NOG SCHRIJF => IK HEB GEEN STATION MET MEERDERE SPOREN GEDAAN DUS IK CHECK OF DAT IEDERE STATION MAAR 1 SPOOR HEEFT !
    // IK MOEST DIT DOEN VOOR GEAVANCEERDE UITVOER DEFTIG TE KUNNEN DOEN !
    for (unsigned int i = 0; i < stations.size(); ++i) {
        Station* first_station = stations[i];
        vector<int> first_station_sporen = first_station->getSpoorNrs();
        for (unsigned int j = 0; j < stations.size(); ++j) {
            Station* second_station = stations[j];
            vector<int> second_station_sporen = second_station->getSpoorNrs();
            if (first_station == second_station){
                continue;
            }else{
                if (first_station_sporen.size() == second_station_sporen.size() && first_station->getSpoor() == second_station->getSpoor()){
                    continue;
                }else{
                    inconsistent = 1;
                    goto final;
                }
            }
        }
    }

    // RIWAAZ: VOORWAARDE 6: THERE ARE NO TRAMS WITH SAME VOERTUIGNUMMER
    for (unsigned int i = 0; i < trams.size(); ++i) {
        Tram* checking_tram = trams[i];
        int checking_tram_voertuignummer = checking_tram->getVoertuignummer();
        for (unsigned int j = 0; j < trams.size(); ++j) {
            Tram* check_tram = trams[j];
            int check_tram_getvoertuignummer = check_tram->getVoertuignummer();
            // if the pointer of above is the same as the pointer of here means that these trams are the same so skip we need to check with others
            if (check_tram == checking_tram){
                continue;
            }else{
                // This section is for checking other tram
                if (check_tram_getvoertuignummer == checking_tram_voertuignummer){
                    ofstream six("../input_tests/inconsistent6_output.txt");
                    six << "XML PARTIAL IMPORT: Inconsistent voorwaarde 6 failed";
                    inconsistent = 1;
                    six.close();
                    goto final;
                }else{
                    continue;
                }
            }
        }
    }
    final:
    if (inconsistent == 1)
    {
        ofstream voorwaardes("../input_tests/consistent_errors.txt");
        voorwaardes << "Inconsistent metronet" << endl;
        voorwaardes.close();
    }
}

Systeem::Systeem()
{
    _initcheck = this;
    ENSURE(this->properlyInitialized(),"CONSTRUCTOR OF CLASS SYSTEEM NOT PROPERLY INITIALIZED");
}

bool Systeem::properlyInitialized() const
{
    return _initcheck == this;
}

const vector<Station *> &Systeem::getStations() const
{
    REQUIRE(this->properlyInitialized(),"getStations precondition failed");
    return stations;
}

const vector<Tram *> &Systeem::getTrams() const
{
    REQUIRE(this->properlyInitialized(),"getTrams precondition failed");
    return trams;
}

void Systeem::setStations(const vector<Station*> &input_stations) {
    REQUIRE(this->properlyInitialized(),"setStations precondition failed");
    Systeem::stations = input_stations;
    ENSURE(getStations() == input_stations,"setStations postcondition failed");
}

void Systeem::setTrams(const vector<Tram *> &input_trams) {
    REQUIRE(this->properlyInitialized(),"setTrams precondition failed");
    Systeem::trams = input_trams;
    ENSURE(getTrams() == input_trams,"setTrams postcondition failed");
}


