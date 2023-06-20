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
     * @param trams: inputvector of trams from our system
     * @param stations: inputvector of stations from our system
     */
    MetroOutput(const std::vector<Tram *> &trams, const std::vector<Station *> &stations);
    /**
     * REQUIRE(!stations.empty(),"writeOver precondition failed");
     * REQUIRE(!trams.empty(),"writeOver precondition failed");
     * ENSURE(file.peek() != ifstream::traits_type::eof(),"writeOver postcondition failed");
     */
    void writeOver();
    /**
     * REQUIRE(!stations.empty(),"simple writeOver precondition failed");
     * REQUIRE(!trams.empty(),"simple writeOver precondition failed");
     * ENSURE(file.peek() != ifstream::traits_type::eof(),"writeOver postcondition failed");
     */
    void simple_writeover();
    /**
     * REQUIRE(!stations.empty(),"advanced writeOver precondition failed");
     * REQUIRE(!trams.empty(),"advanced writeOver precondition failed");
     * ENSURE(file.peek() != ifstream::traits_type::eof(),"writeOver postcondition failed");
     */
    void advanced_writeover();
    /**
     * REQUIRE(!trams.empty(),"verplaatstram precondition failed");
     * REQUIRE(!stations.empty(),"verplaatstram precondition failed");
     */
    void verplaatstram();


};


#endif //PROJECTSOFTWAREENGINEER_METROOUTPUT_H
