//
// Created by aburahman10 on 6/03/23.
//

#include "Tram.h"
#include "DesignByContract.h"

int Tram::getLijnNr() const
{
    REQUIRE(this->properlyInitialized(),"getLijnNr precondition failed");
    ENSURE(lijnNr >= 0,"getLijnNr postcondition failed");
    return lijnNr;
}

void Tram::setLijnNr(int lineNr)
{
    REQUIRE(this->properlyInitialized(),"setLijnNr precondition failed");
    REQUIRE(lineNr >= 0,"setLijnNr must be equal or greater than 0");
    // linenumber not signed !
    Tram::lijnNr = lineNr;
    ENSURE(getLijnNr() == lineNr,"setLijnNr must be equal to lineNr");
}

int Tram::getSnelheid() const
{
    REQUIRE(this->properlyInitialized(),"getSnelheid precondition failed");
    ENSURE(snelheid >= 0, "getSnelheid postcondition failed");
    return snelheid;
}

void Tram::setSnelheid(int velocity)
{
    REQUIRE(this->properlyInitialized(),"setSnelheid precondition failed");
    REQUIRE(velocity >= 0,"setSnelheid precondition failed");
    Tram::snelheid = velocity;
    ENSURE(getSnelheid() == velocity,"setSnelheid post condition failed");
}

Station *Tram::getBeginStation() const
{
    REQUIRE(this->properlyInitialized(),"getBeginStation precondition failed");
    return beginStation;
}

void Tram::setBeginStation(Station *startStation)
{
    REQUIRE(this->properlyInitialized(),"setBeginStation precondition failed");
    REQUIRE(startStation != NULL,"setBeginStation precondition failed");
    Tram::beginStation = startStation;
    ENSURE(getBeginStation() == startStation,"setBeginStation post condition failed");
}

Tram::Tram()
{
    _initcheck = this;
    snelheid = 0;
    lijnNr = 0;
    beginStation = NULL;
    huidigeStation = NULL;
    beginstationname = "";
    voertuignummer = 0;
    type = "";
    ENSURE(this->properlyInitialized(),"CONSTRUCTOR OF CLASS TRAM NOT PROPERLY INITIALIZED");
}

bool Tram::properlyInitialized() const
{
    return _initcheck == this;
}

Station *Tram::getHuidigeStation() const
{
    REQUIRE(this->properlyInitialized(),"getHuidigeStation precondition failed");
    return huidigeStation;
}

void Tram::setHuidigeStation(Station *hdigStation)
{
    REQUIRE(this->properlyInitialized(),"setHuidigeStation precondition failed");
    REQUIRE(hdigStation !=NULL,"setHuidigeStation precondition failed");
    Tram::huidigeStation = hdigStation;
    ENSURE(getHuidigeStation() == hdigStation,"setHuidigeStation postcondition failed");
}

string Tram::getType() const {
    REQUIRE(this->properlyInitialized(),"getType precondition failed");
    return type;
}

void Tram::setType(const string &input_type) {
    REQUIRE(this->properlyInitialized(),"setType precondition failed");
    REQUIRE(input_type != "\0","setType precondition failed");
    Tram::type = input_type;
    ENSURE(getType() == input_type,"setType postcondition failed");

}

const string &Tram::getBeginstationname() const {
    REQUIRE(this->properlyInitialized(),"getBeginstationname precondition failed");
    return beginstationname;
}

void Tram::setBeginstationname(const string &input_name) {
    REQUIRE(this->properlyInitialized(),"setBeginstationname precondition failed");
    REQUIRE(input_name != "\0","setBeginstationname precondition failed");
    Tram::beginstationname = input_name;
    ENSURE(getBeginstationname() == input_name,"setBeginstationname postcondition failed ");
}

int Tram::getVoertuignummer() const {
    REQUIRE(this->properlyInitialized(),"getVoertuignummer precondition failed");
    ENSURE(voertuignummer >= 0, "getVoertuignummer postcondition failed");
    return voertuignummer;
}

void Tram::setVoertuignummer(int input_voertuignummer) {
    REQUIRE(this->properlyInitialized(),"setVoertuignummer precondition failed");
    REQUIRE(input_voertuignummer >= 0,"setVoertuignummer precondition failed");
    Tram::voertuignummer = input_voertuignummer;
    ENSURE(getVoertuignummer()== input_voertuignummer,"setVoertuignummer postcondition failed");
}



