//
// Created by aburahman10 on 6/03/23.
//

#ifndef TICTACTOE10_SYSTEEM_H
#define TICTACTOE10_SYSTEEM_H

#include "iostream"
#include "../tinyxml/tinyxml.h"
#include "vector"
#include "Tram.h"
class Station;
using namespace std;

class Systeem
{
private:
    vector<Station*> stations;
    vector<Tram*> trams;

    Systeem* _initcheck;
    int inconsistent;

public:
    /**
     * REQUIRE(this->properlyInitialized(),"setTrams precondition failed");
     * ENSURE(getTrams() == input_trams,"setTrams postcondition failed");
     * @param input_trams : vector of type pointer to Tram
     */
    void setTrams(const vector<Tram *> &input_trams);
    /**
     * REQUIRE(this->properlyInitialized(),"setStations precondition failed");
     * ENSURE(getStations() == input_stations,"setStations postcondition failed");
     * @param input_stations : vector of type pointer to Station
     */
    void setStations(const vector<Station *> &input_stations);
    /**
     * REQUIRE(this->properlyInitialized(),"getStations precondition failed");
     * @return vector of type pointer to Station variables
     */
    const vector<Station *> &getStations() const;
    /**
     * REQUIRE(this->properlyInitialized(),"getTrams precondition failed");
     * @return vector of type pointer to Tram
     */
    const vector<Tram *> &getTrams() const;

    bool properlyInitialized() const;
    /**
     * REQUIRE(this->properlyInitialized(), "checkConsistent precondition failed");
     */
    void checkConsistent();
    /**
     * ENSURE(this->properlyInitialized(),"CONSTRUCTOR OF CLASS SYSTEEM NOT PROPERLY INITIALIZED");
     */
    Systeem();

};


#endif //TICTACTOE10_SYSTEEM_H
