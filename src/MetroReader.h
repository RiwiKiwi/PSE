//
// Created by riwi on 8/04/23.
//

#ifndef PROJECTSOFTWAREENGINEER_METROREADER_H
#define PROJECTSOFTWAREENGINEER_METROREADER_H
#include <iostream>
#include "Systeem.h"
#include "../tinyxml/tinyxml.h"

enum SuccessEnum {ImportAborted, PartialImport, Success};

class MetroReader {
public:
    /*
 * Read an XML description of metro simulation from importXML and add it to the Systeem& inputsysteem
 * if error occur, report them on errStream
 * Return whether succesful in the errorcode:
 *  - ImportAborted = unchanged; reason for abortion is reported on errStream
 *  - PartialImport = Some semantic errors reported on errStream; state is partially imported and board might have changed
 *  - Success = No importer errors; no errors reported
 *
 * */
    /**
     * XML-reader function
     * REQUIRE(input_system.properlyInitialized(),"The system wasn' t correctly initialized!");
     * ENSURE(!input_system.getTrams().empty(),"importXml postcondition failed!");
     * ENSURE(!input_system.getStations().empty(),"importXml postconditon failed!");
     * @param input_filename : string (directory where we will read our file ) or variable where our path is stored
     * @param errStream : outstream for declaring message
     * @param input_system : inputvariable of type System
     * @return SuccessEnum => declaration for if the filereading went well or not
     */
    static SuccessEnum importXml(const char* input_filename,std::ostream& errStream,Systeem& input_system);
    /**
     * Function for subrootchecker
     * REQUIRE(root_initialized == true,"root isn't properlyinitialized");
     * @param input_object string or stringvariable
     * @param root_initialized inputbool
     * @return bool
     */
    static bool check_object(std::string& input_object,bool root_initialized);
    /**
     * Function for elements of subroot checker
     * REQUIRE(subroot_initialized == true,"check_object_elements precondition failed");
     * @param input_object string => STATION OR TRAM
     * @param check_root TiXmlElement* our checking root of xmlfile
     * @param subroot_initialized : inputbool
     * @return bool
     */
    static bool check_object_elements(std::string& input_object, TiXmlElement* check_root,bool subroot_initialized);
    /**
     * Function to check if the given string is an alphabet
     * @param check_string inputstringvariable or string
     * @return bool
     */
    static bool is_Alphabet(std::string&check_string);
    /**
     * Function to check if the inputstring is convertible to a number
     * @param check_string inputstringvariable or string
     * @return bool
     */
    static bool is_Number(std::string& check_string);
    /**
     * Funciton to check if the inputted type in xmlfile is good or not
     * @param input_type inputstring or stringvariable
     * @param is_station give true if station and false if it is a tram that we want to check for
     * @return bool
     */
    static bool check_type(std::string& input_type,bool is_station);
    /**
     * Function that will give back which tramtype this is
     * @param input_root : inputsubroot for getting the type
     * @return string => PCC OR ALBATROS OR STADSLIJNER
     */
    static string get_tram_type(TiXmlElement* input_root);
    /**
     * Function to setup our PCC or TRAM object
     * REQUIRE(input_systeem.properlyInitialized(),"The system wasn' t properlyinitialized correctly!");
     * @param is_pcc true if we have to make PCC and else false => making TRAM object
     * @param input_root inputroot of the xmlfile
     * @param input_systeem: our Metrosystem
     * @param errStream: outstream for errormessage
     * @return SuccessEnum
     */
    static SuccessEnum set_tram(bool is_pcc, TiXmlElement* input_root,Systeem&input_systeem,std::ostream& errStream);
};


#endif //PROJECTSOFTWAREENGINEER_METROREADER_H
