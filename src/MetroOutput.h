//
// Created by riwi on 4/05/23.
//

#ifndef PROJECTSOFTWAREENGINEER_METROOUTPUT_H
#define PROJECTSOFTWAREENGINEER_METROOUTPUT_H
#include <vector>
#include "Tram.h"
#include "Station.h"
class MetroOutput {
private:
    std::vector<Tram*>trams;
    std::vector<Station*>stations;

    MetroOutput* _inicheck;
public:

    /**
     * Constructor
     * ENSURE(this->properlyInitialized(),"CONSTRUCTOR OF OUTPUTCLASS NOT PROPERLY INITIALIZED!");
     * @param trams: inputvector of trams from our system
     * @param stations: inputvector of stations from our system
     */
    MetroOutput(const std::vector<Tram *> &trams, const std::vector<Station *> &stations);
    /**
     * Simple Output of our specification 1 (USECASE 2.1)
     * REQUIRE(this->properlyInitialized(),"CONSTRUCTOR OF OUTPUTCLASS NOT PROPERLY INITIALIZED!");
     * REQUIRE(!stations.empty(),"writeOver precondition failed");
     * REQUIRE(!trams.empty(),"writeOver precondition failed");
     * ENSURE(file.peek() != ifstream::traits_type::eof(),"writeOver postcondition failed");
     */
    void writeOver();
    /**
     * Simple Output of our specification 2 (USECASE 2.2)
     * REQUIRE(this->properlyInitialized(),"CONSTRUCTOR OF OUTPUTCLASS NOT PROPERLY INITIALIZED!");
     * REQUIRE(!stations.empty(),"simple writeOver precondition failed");
     * REQUIRE(!trams.empty(),"simple writeOver precondition failed");
     * ENSURE(file.peek() != ifstream::traits_type::eof(),"writeOver postcondition failed");
     */
    void simple_writeover();
    /**
     * Advanced Output of our specification 2 (USECASE 2.3)
     * REQUIRE(this->properlyInitialized(),"CONSTRUCTOR OF OUTPUTCLASS NOT PROPERLY INITIALIZED!");
     * REQUIRE(!stations.empty(),"advanced writeOver precondition failed");
     * REQUIRE(!trams.empty(),"advanced writeOver precondition failed");
     * ENSURE(file.peek() != ifstream::traits_type::eof(),"writeOver postcondition failed");
     */
    void advanced_writeover();
    /**
     * Function to stimulate automatic simulation of our specification 2 (USECASE 3.1/3.2/3.3)
     * REQUIRE(this->properlyInitialized(),"CONSTRUCTOR OF OUTPUTCLASS NOT PROPERLY INITIALIZED!");
     * REQUIRE(!trams.empty(),"verplaatstram precondition failed");
     * REQUIRE(!stations.empty(),"verplaatstram precondition failed");
     * ENSURE(file.peek()!= ifstream::traits_type::eof(),"verplaatstram postcondition failed");
     */
    void verplaatstram();

    bool properlyInitialized() const;


};


#endif //PROJECTSOFTWAREENGINEER_METROOUTPUT_H
