//
// Created by aburahman10 on 6/03/23.
//

#ifndef TICTACTOE10_TRAM_H
#define TICTACTOE10_TRAM_H
#include "Station.h"
#include "iostream"
#include "DesignByContract.h"

using namespace std;

class Tram
{
protected:

    int lijnNr;
    int snelheid;
    int voertuignummer;
    Station* beginStation;
    Station* huidigeStation;
    string beginstationname;

    string type;

    Tram* _initcheck;
public:
    /**
     * REQUIRE(this->properlyInitialized(),"getVoertuignummer precondition failed");
     * @return unsigned integer
     */
    int getVoertuignummer() const;
    /**
     * REQUIRE(this->properlyInitialized(),"setVoertuignummer precondition failed");
     * REQUIRE(input_voertuignummer >= 0,"setVoertuignummer precondition failed");
     * ENSURE(getVoertuignummer()== input_voertuignummer,"setVoertuignummer postcondition failed");
     * @param input_voertuignummer : integervariable or integer
     */
    void setVoertuignummer(int input_voertuignummer);

    /**
     * REQUIRE(this->properlyInitialized(),"getBeginstationname precondition failed");
     * @return string
     */
    const string &getBeginstationname() const;
    /**
     * REQUIRE(this->properlyInitialized(),"setBeginstationname precondition failed");
     * REQUIRE(input_name != "\0","setBeginstationname precondition failed");
     * ENSURE(getBeginstationname() == input_name,"setBeginstationname postcondition failed ");
     * @param input_name : string variable or string
     */
    void setBeginstationname(const string &input_name);
    /**
     * REQUIRE(this->properlyInitialized(),"getType precondition failed");
     * @return string
     */
    virtual string getType() const;
    /**
     * REQUIRE(this->properlyInitialized(),"setType precondition failed");
     * REQUIRE(input_type != "\0","setType precondition failed");
     * ENSURE(getType() == input_type,"setType postcondition failed");
     * @param input_type : string variable or string
     */
    virtual void setType(const string &input_type);
    /**
     * REQUIRE(this->properlyInitialized(),"getHuidigeStation precondition failed");
     * @return Station* (pointer to a variable of Stationtype)
     */
    Station *getHuidigeStation() const;
    /**
     * REQUIRE(this->properlyInitialized(),"setHuidigeStation precondition failed");
     * REQUIRE(hdigStation !=NULL,"setHuidigeStation precondition failed");
     * ENSURE(getHuidigeStation() == hdigStation,"setHuidigeStation postcondition failed");
     * @param huidigeStation : Station* (input pointer to a variable of Stationtype)
     */

    void setHuidigeStation(Station *huidigeStation);
    /**
     * REQUIRE(this->properlyInitialized(),"getLijnNr precondition failed");
     * ENSURE(lijnNr >= 0,"getLijnNr postcondition failed");
     * @return integer
     */
    int getLijnNr() const;
    /**
     * REQUIRE(this->properlyInitialized(),"setLijnNr precondition failed");
     * REQUIRE(lineNr >= 0,"setLijnNr must be equal or greater than 0");
     * ENSURE(getLijnNr() == lineNr,"setLijnNr must be equal to lineNr");
     * @param lijnNr : input integer to set lijnnummer
     */
    void setLijnNr(int lijnNr);
    /**
     * REQUIRE(this->properlyInitialized(),"getSnelheid precondition failed");
     * @return unsigned integer
     */
    virtual int getSnelheid() const;
    /**
     * REQUIRE(this->properlyInitialized(),"setSnelheid precondition failed");
     * REQUIRE(velocity >= 0,"setSnelheid precondition failed");
     * ENSURE(getSnelheid() == velocity,"setSnelheid post condition failed");
     * @param snelheid : input integer to set velocity
     */
    virtual void setSnelheid(int snelheid);
    /**
     *  REQUIRE(this->properlyInitialized(),"getBeginStation precondition failed");
     * @return Station* (pointer to a variable of Stationtype)
     */
    Station *getBeginStation() const;

    /**
     * REQUIRE(this->properlyInitialized(),"setBeginStation precondition failed");
     * REQUIRE(startStation != NULL,"setBeginStation precondition failed");
     * ENSURE(getBeginStation() == startStation,"setBeginStation post condition failed");
     * @param beginStation : input pointer has to be of Stationtype
     */
    void setBeginStation(Station *beginStation);

    bool properlyInitialized() const;
    /**
     * Constructor
     * ENSURE(this->properlyInitialized(),"CONSTRUCTOR OF CLASS TRAM NOT PROPERLY INITIALIZED");
     */
    Tram();
};

class PCC: public Tram{

    int storepcc_moves;
    int storepcc_waits;
    int curr_moves;
    int curr_waits;

    PCC* __inicheck;

public:
    /**
     * Constructor
     * ENSURE(this->properlyInitialized(),"CONSTRUCTOR OF PCC NOT PROPERLY INITIALIZED");
     */
    PCC(){
        __inicheck = this;
        storepcc_waits = 0;
        storepcc_moves = 0;
        curr_waits = 0;
        curr_moves = 0;
        ENSURE(this->properlyInitialized(),"CONSTRUCTOR OF PCC NOT PROPERLY INITIALIZED");
    };

    bool properlyInitialized() {
        return _initcheck == this;
    }
    /**
     * REQUIRE(_initcheck->properlyInitialized(),"getStorepccMoves precondition failed");
     * @return unsigned integer
     */

    int getStorepccMoves() const {
        REQUIRE(_initcheck->properlyInitialized(),"getStorepccMoves precondition failed");
        return storepcc_moves;
    }
    /**
     * REQUIRE(this->properlyInitialized(),"setStorepccMoves precondition failed");
     * REQUIRE(storepccMoves > 0,"setStorepccMoves precondition failed");
     * @param storepccMoves: unsigned integer
     * ENSURE(getStorepccMoves() == storepccMoves,"setStorepccMoves postcondition failed");
     * ENSURE(getCurrMoves() == storepccMoves,"setStorepccMoves postcondition failed");
     */
    void setStorepccMoves(int storepccMoves) {
        REQUIRE(this->properlyInitialized(),"setStorepccMoves precondition failed");
        REQUIRE(storepccMoves > 0,"setStorepccMoves precondition failed");
        storepcc_moves = storepccMoves;
        curr_moves = storepccMoves;
        ENSURE(getStorepccMoves() == storepccMoves,"setStorepccMoves postcondition failed");
        ENSURE(getCurrMoves() == storepccMoves,"setStorepccMoves postcondition failed");
    }
    /**
     * REQUIRE(_initcheck->properlyInitialized(),"getStorepccWaits preconditon failed");
     * @return unsigned integer
     */
    int getStorepccWaits() const {
        REQUIRE(_initcheck->properlyInitialized(),"getStorepccWaits preconditon failed");
        return storepcc_waits;
    }
    /**
     * REQUIRE(this->properlyInitialized(),"setStorepccWaits precondition failed");
     * REQUIRE(storepccWaits > 0,"setStorepccWaits precondition failed");
     * @param storepccWaits: unsigned integer
     * ENSURE(getStorepccWaits() == storepccWaits,"setStorepccWaits postcondition failed");
     * ENSURE(getCurrWaits() == storepccWaits,"setStorepccWaits postcondition failed");
     */
    void setStorepccWaits(int storepccWaits) {
        REQUIRE(this->properlyInitialized(),"setStorepccWaits precondition failed");
        REQUIRE(storepccWaits > 0,"setStorepccWaits precondition failed");
        storepcc_waits = storepccWaits;
        curr_waits = storepccWaits;
        ENSURE(getStorepccWaits() == storepccWaits,"setStorepccWaits postcondition failed");
        ENSURE(getCurrWaits() == storepccWaits,"setStorepccWaits postcondition failed");
    }
    /**
     * REQUIRE(__inicheck->properlyInitialized(),"getCurrMoves preconditon failed");
     * @return unsigned integer
     */
    int getCurrMoves() const {
        REQUIRE(__inicheck->properlyInitialized(),"getCurrMoves preconditon failed");
        return curr_moves;
    }
    /**
     * REQUIRE(this->properlyInitialized(),"setCurrMoves preconditon failed");
     * REQUIRE(currMoves >= 0 , "setCurrMoves precondition failed");
     * @param currMoves: unsigned integer
     * ENSURE(getCurrMoves() == currMoves,"setCurrMoves postcondition failed");
     */
    void setCurrMoves(int currMoves) {
        REQUIRE(this->properlyInitialized(),"setCurrMoves preconditon failed");
        REQUIRE(currMoves >= 0 , "setCurrMoves precondition failed");
        curr_moves = currMoves;
        ENSURE(getCurrMoves() == currMoves,"setCurrMoves postcondition failed");
    }
    /**
     * REQUIRE(__inicheck->properlyInitialized(),"getCurrWaits precondition failed");
     * @return unsigned integer
     */
    int getCurrWaits() const {
        REQUIRE(__inicheck->properlyInitialized(),"getCurrWaits precondition failed");
        return curr_waits;
    }
    /**
     * REQUIRE(this->properlyInitialized(),"setCurrWaits preconditon failed");
     * REQUIRE(currWaits >= 0, "setCurrWaits precondition failed");
     * @param currWaits: unsigned integer
     * ENSURE(getCurrWaits() == currWaits,"setCurrWaits postcondition failed");
     */
    void setCurrWaits(int currWaits) {
        REQUIRE(this->properlyInitialized(),"setCurrWaits preconditon failed");
        REQUIRE(currWaits >= 0, "setCurrWaits precondition failed");
        curr_waits = currWaits;
        ENSURE(getCurrWaits() == currWaits,"setCurrWaits postcondition failed");
    }

};


#endif //TICTACTOE10_TRAM_H
