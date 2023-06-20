//
// Created by aburahman10 on 6/03/23.
//


#include "../tinyxml/tinyxml.h"
#include "Systeem.h"
#include "MetroReader.h"
#include "MetroOutput.h"
using namespace std;

int main()
{
    Systeem test;
    // Initializing the system using xmlimporter class
    SuccessEnum result = MetroReader::importXml("../src/advanced_ascii.xml",std::cerr,test);
    if (result == Success)
    {
        //consistentiecheck before generating output
        test.checkConsistent();
        //Generate output using outputclass object
        MetroOutput print(test.getTrams(),test.getStations());
        print.writeOver();
        print.simple_writeover();
        print.advanced_writeover();
        test.rijd(20);
        print.advanced_writeover();
    }
    return 0;
}