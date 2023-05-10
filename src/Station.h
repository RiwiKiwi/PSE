//
// Created by aburahman10 on 6/03/23.
//

#ifndef TICTACTOE10_STATION_H
#define TICTACTOE10_STATION_H


#include "iostream"

using namespace std;

#include "vector"

class Station
{
private:

    string naam;
    Station* volgende;
    Station* vorige;

    string next;
    string prev;
    string type;

    int spoor;

    vector<int> spoorNrs;

    Station* _initcheck;

public:
    /**
     * REQUIRE(this->properlyInitialized(),"getSpoor precondition failed");
     * @return integer
     */
    int getSpoor() const;
    /**
     * REQUIRE(this->properlyInitialized(),"setSpoor precondition failed");
     * ENSURE(input_spoor>=0,"setSpoor precondition failed");
     * ENSURE(getSpoor() == input_spoor,"setSpoor postcondtition failed");
     * @param input_spoor : integer or integervariable
     */
    void setSpoor(int input_spoor);
    /**
     * REQUIRE(this->properlyInitialized(),"getType precondition failed");
     * @return string
     */
    const string &getType() const;
    /**
     * REQUIRE(this->properlyInitialized(),"getType precondition failed");
     * ENSURE(input_type != "\0","setType postcondition failed");
     * ENSURE(getType() == input_type,"setType postcondition failed");
     * @param input_type : string or stringvariable
     */
    void setType(const string &input_type);
    /**
     * REQUIRE(this->properlyInitialized(),"getSpoorNrs precondition failed");
     * @return : vector of integers
     */
    const vector<int> &getSpoorNrs() const;
    /**
     * REQUIRE(this->properlyInitialized(),"setSpoorNrs precondition failed");
     * ENSURE(spNrs.size() != 0,"setSpporNrs as an empty vector as input!");
     * ENSURE(getSpoorNrs() == spNrs,"setSpoorNrs postcondition failed");
     * @param spoorNrs : vector of integers
     */
    void setSpoorNrs(const vector<int> &spoorNrs);
    /**
     * REQUIRE(this->properlyInitialized(),"getNext precondition failed");
     * @return string
     */
    const string &getNext() const;
    /**
     * REQUIRE(this->properlyInitialized(),"setNext precondition failed");
     * ENSURE(nextptr != "\0","setNext cannot be empty string");
     * ENSURE(getNext() == nextptr,"setNext postcondition failed");
     * @param next
     */
    void setNext(const string &next);
    /**
     * REQUIRE(this->properlyInitialized(),"getPrev precondition failed");
     * @return string
     */
    const string &getPrev() const;
    /**
     * REQUIRE(this->properlyInitialized(),"setPrev precondition failed");
     * ENSURE(prevptr != "\0","setPrev cannot be empty string");
     * ENSURE(getPrev() == prevptr,"setPrev postcondition failed");
     * @param prev : inputstring or stringvariable
     */
    void setPrev(const string &prev);
    /**
     * EQUIRE(this->properlyInitialized(),"getNaam precondition failed");
     * @return string
     */
    const string &getNaam() const;
    /**
     * REQUIRE(this->properlyInitialized(),"setNaam precondition failed");
     * ENSURE(name != "\0","NAME CANNOT BE EMPTY");
     * ENSURE(getNaam() == name,"setNaam postcondition failed");
     * @param naam
     */
    void setNaam(const string &naam);
    /**
     * REQUIRE(this->properlyInitialized(),"getVolgende precondition failed");
     * @return pointer to a station
     */
    Station *getVolgende() const;
    /**
     * REQUIRE(this->properlyInitialized(),"setVolgende precondition failed");
     * ENSURE(nextptr != NULL,"setVolgende nextptr CANNOT BE NULL");
     * ENSURE(getVolgende() == nextptr,"setVolgende postcondtion failed");
     * @param volgende : variable of pointer to station
     */
    void setVolgende(Station *volgende);
    /**
     * REQUIRE(this->properlyInitialized(),"getVorige precondition failed");
     * @return pointer to a station
     */
    Station *getVorige() const;
    /**
     * REQUIRE(this->properlyInitialized(),"setVorige precondition failed");
     * ENSURE(prevptr != NULL,"setVorige prevptr CANNOT BE NULL");
     * ENSURE(getVorige() == prevptr,"setVorige postcondition failed");
     * @param vorige : variable of pointer to a station
     */
    void setVorige(Station *vorige);

    bool properlyInitialized() const;
    /**
     * ENSURE(this->properlyInitialized(),"CONSTRUCTOR OF CLASS STATION NOT PROPERLY INITIALIZED");
     */
    Station();

};


#endif //TICTACTOE10_STATION_H
