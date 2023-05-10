//
// Created by aburahman10 on 6/03/23.
//

#include "Station.h"
#include "DesignByContract.h"

const string &Station::getNaam() const
{
    REQUIRE(this->properlyInitialized(),"getNaam precondition failed");
    return naam;
}

void Station::setNaam(const string &name)
{
    REQUIRE(this->properlyInitialized(),"setNaam precondition failed");
    Station::naam = name;
    ENSURE(name != "\0","NAME CANNOT BE EMPTY");
    ENSURE(getNaam() == name,"setNaam postcondition failed");

}

Station *Station::getVolgende() const
{
    REQUIRE(this->properlyInitialized(),"getVolgende precondition failed");
    return volgende;

}

void Station::setVolgende(Station *nextptr)
{
    REQUIRE(this->properlyInitialized(),"setVolgende precondition failed");
    Station::volgende = nextptr;
    ENSURE(nextptr != NULL,"setVolgende nextptr CANNOT BE NULL");
    ENSURE(getVolgende() == nextptr,"setVolgende postcondtion failed");

}

Station *Station::getVorige() const
{
    REQUIRE(this->properlyInitialized(),"getVorige precondition failed");
    return vorige;
}

void Station::setVorige(Station *prevptr)
{
    REQUIRE(this->properlyInitialized(),"setVorige precondition failed");
    Station::vorige = prevptr;
    ENSURE(prevptr != NULL,"setVorige prevptr CANNOT BE NULL");
    ENSURE(getVorige() == prevptr,"setVorige postcondition failed");

}

const string &Station::getNext() const
{
    REQUIRE(this->properlyInitialized(),"getNext precondition failed");
    return next;

}

void Station::setNext(const string &nextptr)
{
    REQUIRE(this->properlyInitialized(),"setNext precondition failed");
    Station::next = nextptr;
    ENSURE(nextptr != "\0","setNext cannot be empty string");
    ENSURE(getNext() == nextptr,"setNext postcondition failed");

}

const string &Station::getPrev() const
{
    REQUIRE(this->properlyInitialized(),"getPrev precondition failed");
    return prev;
}

void Station::setPrev(const string &prevptr)
{
    REQUIRE(this->properlyInitialized(),"setPrev precondition failed");
    Station::prev = prevptr;
    ENSURE(prevptr != "\0","setPrev cannot be empty string");
    ENSURE(getPrev() == prevptr,"setPrev postcondition failed");
}

const vector<int> &Station::getSpoorNrs() const
{
    REQUIRE(this->properlyInitialized(),"getSpoorNrs precondition failed");
    return spoorNrs;
}

void Station::setSpoorNrs(const vector<int> &spNrs)
{
    REQUIRE(this->properlyInitialized(),"setSpoorNrs precondition failed");
    Station::spoorNrs = spNrs;
    ENSURE(spNrs.size() != 0,"setSpporNrs as an empty vector as input!");
    ENSURE(getSpoorNrs() == spNrs,"setSpoorNrs postcondition failed");
}

Station::Station()
{
    naam = "";
    next = "";
    prev = "";
    type = "";
    _initcheck = this;
    volgende = NULL;
    vorige = NULL;
    spoor = 0;
    ENSURE(this->properlyInitialized(),"CONSTRUCTOR OF CLASS STATION NOT PROPERLY INITIALIZED");
}

bool Station::properlyInitialized() const
{
    return _initcheck == this;
}

const string &Station::getType() const {
    REQUIRE(this->properlyInitialized(),"getType precondition failed");
    return type;
}

void Station::setType(const string &input_type) {
    REQUIRE(this->properlyInitialized(),"getType precondition failed");
    Station::type = input_type;
    ENSURE(input_type != "\0","setType postcondition failed");
    ENSURE(getType() == input_type,"setType postcondition failed");
}

int Station::getSpoor() const {
    REQUIRE(this->properlyInitialized(),"getSpoor precondition failed");
    return spoor;
}

void Station::setSpoor(int input_spoor) {
    REQUIRE(this->properlyInitialized(),"setSpoor precondition failed");
    Station::spoor = input_spoor;
    ENSURE(input_spoor>=0,"setSpoor precondition failed");
    ENSURE(getSpoor() == input_spoor,"setSpoor postcondtition failed");
}


