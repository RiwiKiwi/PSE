//
// Created by riwi on 8/04/23.
//

#include "MetroReader.h"
#include <iostream>
#include <cctype>
#include <algorithm>
#include "DesignByContract.h"

SuccessEnum MetroReader::importXml(const char* input_filename,std::ostream& errStream,Systeem& input_system) {
    REQUIRE(input_system.properlyInitialized(),"importXml precondition failed");
    // We will put our xml-file in the doc
    TiXmlDocument doc;
    SuccessEnum endResult = Success;
    // THIS IF STATEMENT WILL CHECK TE SYNTAX ERROR FOR YOU ALREADY ! ( WE JUST NEED TO TEST IF A SYNTAX ERROR XML WILL GIVE IMPORTABORTED AS OUTPUT!)
    if(!doc.LoadFile(input_filename))
    {
        errStream<<"XML IMPORT ABORTED: "<< doc.ErrorDesc() << std::endl;
        return ImportAborted;
    }
    // Get the root out to do some operations with it !
    TiXmlElement* get_root = doc.FirstChildElement();
    if(get_root == NULL){
        errStream << "XML PARTIAL IMPORT: Root isn't properly initialized! "<< endl;
        return PartialImport;
    }
    std::string rootname = get_root->Value();
    // check if the root pointer isn' t a rootnode & it must be correctly written !
    if(rootname != "METRONET") {
        errStream << "XML PARTIAL IMPORT: EXPECTED <METRONET> ... </METRONET> and got <" << rootname << "> ... </" << rootname << ">." << endl;
        endResult =  PartialImport;
    }
    // HERE WE MAKE THE TRAMS AND STATIONS BUT THE PREVIOUS AND NEXT POINTERS ARE STILL NULL HERE !
    for (TiXmlElement* current = get_root->FirstChildElement(); current != NULL; current = current->NextSiblingElement()) {
        string inside = current->Value();
        bool check_result = check_object(inside,true);
        // VERIFICATION OF STATIONS AND TRAMS
        if (check_result)
        {
            if (inside == "STATION"){
                // VERIFICATION OF STATION ELEMENTS
                bool elements_result = check_object_elements(inside,current,true);
                if (elements_result)
                {
                    //making the station objects
                    Station* new_station = new Station;
                    for (TiXmlElement* elements = current->FirstChildElement(); elements != NULL; elements = elements->NextSiblingElement()) {
                        std::string check_element = elements->Value();
                        if (check_element == "naam"){
                            if (elements->FirstChild() == NULL){
                                errStream << "XML IMPORT ABORTED: NAAM NOT PROPERLY INITIALIZED!"<<endl;
                                endResult = ImportAborted;
                                continue;
                            }
                            string get_naam = elements->FirstChild()->ValueTStr().c_str();
                            bool result = is_Alphabet(get_naam);
                            if (result){
                                new_station->setNaam(get_naam);
                            }else{
                                errStream <<"XML IMPORT ABORTED: expected an upper char for stationname but got => "<< get_naam << endl;
                                errStream << "---------------------------------------------------------------------"<< endl;
                                endResult = ImportAborted;
                                continue;
                            }
                        }
                        if (check_element == "type"){
                            if (elements->FirstChild() == NULL){
                                errStream << "XML IMPORT ABORTED: TYPE NOT PROPERLY INITIALIZED!" << endl;
                                endResult = ImportAborted;
                            }
                            string get_type = elements->FirstChild()->ValueTStr().c_str();
                            bool result = check_type(get_type,true);
                            if (result){
                                new_station->setType(get_type);
                            }else{
                                errStream <<"XML IMPORT ABORTED: expected Metrostation or Halte as type but got => "<<get_type<< endl;
                                errStream << "---------------------------------------------------------------------"<< endl;
                                endResult = ImportAborted;
                                continue;
                            }
                        }
                        if (check_element == "volgende"){
                            if (elements->FirstChild() == NULL){
                                errStream << "XML IMPORT ABORTED: VOLGENDE NOT PROPERLY INITIALIZED!" << endl;
                                endResult = ImportAborted;
                                continue;
                            }
                            string get_volgend = elements->FirstChild()->ValueTStr().c_str();
                            bool result = is_Alphabet(get_volgend);
                            if (result){
                                new_station->setNext(get_volgend);
                            }else{
                                errStream <<"XML IMPORT ABORTED: expected an upper char for station volgende but got => "<<get_volgend<< endl;
                                errStream << "---------------------------------------------------------------------"<< endl;
                                endResult = ImportAborted;
                                continue;
                            }
                        }
                        if (check_element == "vorige"){
                            if (elements->FirstChild() == NULL){
                                errStream << "XML IMPORT ABORTED: VORIGE NOT PROPERLY INITIALIZED!" << endl;
                                endResult = ImportAborted;
                                continue;
                            }
                            string get_vorig = elements->FirstChild()->ValueTStr().c_str();
                            bool result = is_Alphabet(get_vorig);
                            if (result){
                                new_station->setPrev(get_vorig);
                            }else{
                                errStream <<"XML IMPORT ABORTED: expected an upper char for station vorige but got => "<<get_vorig << endl;
                                errStream << "---------------------------------------------------------------------"<< endl;
                                endResult = ImportAborted;
                                continue;
                            }
                        }
                        if (check_element == "spoor"){
                            if (elements->FirstChild() == NULL){
                                errStream << "XML IMPORT ABORTED: SPOOR NOT PROPERLY INITIALIZED!" << endl;
                                endResult = ImportAborted;
                                continue;
                            }
                            const char *get_spoor = elements->FirstChild()->ValueTStr().c_str();
                            string tostring(get_spoor);
                            bool result = is_Number(tostring);
                            if (result){
                                new_station->setSpoor(atoi(get_spoor));
                                vector<int> new_station_sporen = new_station->getSpoorNrs();
                                new_station_sporen.push_back(atoi(get_spoor));
                                new_station->setSpoorNrs(new_station_sporen);
                            }else{
                                errStream <<"XML IMPORT ABORTED: expected an integer for spoor but got => "<<tostring<< endl;
                                errStream << "---------------------------------------------------------------------"<< endl;
                                endResult = ImportAborted;
                                continue;
                            }
                        }
                    }

                    // ADDING THE MADE STATION TO THE VECTOR OF STATIONS !
                    vector<Station*> adding_vector = input_system.getStations();
                    adding_vector.push_back(new_station);
                    input_system.setStations(adding_vector);
                }
                else
                {
                    // WE HAVE READ SOMETHING ELSE THAN <naam>/<type>/<volgende>/<vorige>/<spoor>
                    errStream << "XML IMPORT ABORTED: UNKNOWN tag occured in <STATION>...</STATION> or a tag is missing in the xml file"<<endl;
                    endResult = ImportAborted;
                }
            }
            if (inside == "TRAM"){
                // VERIFICATION OF TRAM ELEMENTS
                bool elements_result = check_object_elements(inside,current,true);
                if (elements_result)
                {
                    again:

                    string checking_tramtype = get_tram_type(current);
                    if (checking_tramtype == "PCC"){
                        SuccessEnum get_result = set_tram(true,current,input_system,errStream);
                        if (get_result == ImportAborted){
                            errStream << "XML IMPORT ABORTED: Failed to make PCC-tram" << endl;
                            endResult =  ImportAborted;
                        }
                    }
                    else if(checking_tramtype == "Albatros" or checking_tramtype == "Stadslijner"){
                        SuccessEnum get_result_two = set_tram(false,current,input_system,errStream);
                        if (get_result_two == ImportAborted){
                            errStream << "XML IMPORT ABORTED: Failed to make Albatros or Stadslijner" << endl;
                            endResult = ImportAborted;
                        }
                    }
                    else{
                        errStream << "XML IMPORT ABORTED: expected PCC or Stadslijner or Albatros as tramtype but got "<< checking_tramtype << endl;
                        endResult = ImportAborted;
                    }
                }
                else
                {
                    // WE HAVE READ SOMETHING ELSE THAN <naam>/<type>/<volgende>/<vorige>/<spoor>
                    errStream << "XML IMPORT ABORTED: UNKNOWN tag occured in <TRAM>...</TRAM> or a tag is missing in the xml file"<<endl;
                    endResult = ImportAborted;
                    goto again;
                }
            }
        }
        else
        {
            // WE HAVE READ SOMETHING ELSE THAN <STATION>/<TRAM>
            errStream << "XML IMPORT ABORTED: EXPECTED tag <STATION> or <TRAM> but got <"<< inside << "> ... </"<<inside<<">." <<endl;
            return ImportAborted;
        }
    }
    // NEED TO MANAGE THE POINTERS NOW !

    // FIRST WE WILL MANAGE THE POINTERS OF THE STATIONS!
    vector<Station*> get_stations = input_system.getStations();
    // station per station
    for (unsigned int i = 0; i< get_stations.size(); ++i) {
        // huidige value van de loop
        Station* current_station = get_stations[i];
        // huidige value zijn previous en next string naar buiten (DIT IS U ALGORITME)
        std::string save_volgend = get_stations[i]->getNext();
        std::string save_vorig = get_stations[i]->getPrev();
        // elk station
        for (unsigned int j = 0; j < get_stations.size(); ++j) {
            //Initialize the volgende
            if (get_stations[j]->getNaam() == save_volgend){
                current_station->setVolgende(get_stations[j]);
            }
            //Initialize the vorige
            if (get_stations[j]->getNaam() == save_vorig){
                current_station->setVorige(get_stations[j]);
            }
        }
    }
    // NOW WE WILL MANAGE THE POINTERS FOR TRAMS
    vector<Tram*> get_trams = input_system.getTrams();
    // loop through every tram to set it' s beginstation
    for (unsigned int i = 0; i < get_trams.size(); ++i) {
        Tram* current_tram = get_trams[i];;
        std::string save_beginstation = get_trams[i]->getBeginstationname(); // Dit heb ik dus zelf erbij toegevoegd
        // going through the stations to check if the name will be the same
        for (unsigned int j = 0; j < get_stations.size(); ++j) {
            if (get_stations[j]->getNaam() == save_beginstation){
                // set this tram it' s begin station !
                current_tram->setBeginStation(get_stations[j]);
                // this tram will start at this station too
                current_tram->setHuidigeStation(get_stations[j]);
                break;
            }else{
                continue;
            }
        }
    }
    // Sluit het bestand
    doc.Clear();
    if (input_system.getTrams().empty()){
        errStream << "XML IMPORT ABORTED: THERE ARE NO TRAMS IN YOUR METRONET!" << endl;
        endResult = ImportAborted;
    }
    if (input_system.getStations().empty()){
        errStream <<"XML IMPORT ABORTED: THERE ARE NO STATIONS IN YOUR METRONET!" << endl;
        endResult = ImportAborted;
    }
    ENSURE(!input_system.getTrams().empty(),"importXml postcondition failed!");
    ENSURE(!input_system.getStations().empty(),"importXml postconditon failed!");
    return endResult;
}

bool MetroReader::check_object(string &input_element,bool root_initialized) {
    // check vector
    REQUIRE(root_initialized == true,"root isn't properlyinitialized");
    const char* my_objects[] = {"STATION", "TRAM"};
    vector<string> volgorde(my_objects, my_objects + sizeof(my_objects) / sizeof(my_objects[0]));
    for (vector<string>::iterator it = volgorde.begin(); it != volgorde.end(); ++it) {
        if ((*it) == input_element){
            return true;
        }
        else{
            continue;
        }
    }
    return false;
}
bool MetroReader::check_object_elements(string &input_object,TiXmlElement* input_root,bool subroot_initialized) {
    REQUIRE(subroot_initialized == true,"check_object_elements precondition failed");
    const char* s_Elements[] = {"naam", "type", "volgende", "vorige", "spoor"};
    vector<string> station_elements(s_Elements, s_Elements + sizeof(s_Elements) / sizeof(s_Elements[0]));
    const char* t_Elements[] = {"lijnNr","type","beginStation","snelheid","voertuigNr","aantalDefecten","reparatieTijd"};
    vector<string> tram_elements(t_Elements,t_Elements + sizeof(t_Elements)/sizeof(t_Elements[0]));
    if (input_object == "STATION"){
        for (TiXmlElement* elements = input_root->FirstChildElement(); elements != NULL; elements = elements->NextSiblingElement()) {
            // store the checking element
            std::string get_element = elements->Value();
            std::vector<string>::iterator it = std::find(station_elements.begin(),station_elements.end(),get_element);
            if (it != station_elements.end()){
                // element is present there
                continue;
            }else{
                return false;
            }
        }
        return true;
    }
    if (input_object == "TRAM"){
        TiXmlElement* objects = input_root->FirstChildElement();
        while (objects != NULL){
            std::string get_element = objects->Value();
            std::vector<string>::iterator it = std::find(tram_elements.begin(),tram_elements.end(),get_element);
            if (it != tram_elements.end()){
                objects = objects->NextSiblingElement();
            }else{
                return false;
            }
        }
    }
    return true;
}

bool MetroReader::is_Alphabet(string &check_string) {
    for (unsigned int i = 0; i < check_string.length(); ++i) {
        // check gwn of dit string een alphabet is ofniet
        if (!isalpha(check_string[i])){
            return false;
        }else{
            // het is een alphabet maar nu check of het in hoofdletter is geschreven ofniet want het zijn station namen
            if (!isupper(check_string[i])){
                return false;
            }else{
                continue;
            }
        }
    }
    return true;
}

bool MetroReader::check_type(string &input_type,bool is_station) {
    // true means it' s station and false means it' s for tram
    const char* tram_types[] = {"PCC","Albatros","Stadslijner"};
    vector<string> trams_types(tram_types, tram_types+ sizeof(tram_types) / sizeof(tram_types[0]));
    const char* station_types[] = {"Metrostation","Halte"};
    vector<string> stations_types(station_types, station_types+ sizeof(station_types) / sizeof(station_types[0]));
    if (is_station){
        for (unsigned int i = 0; i < stations_types.size();++i) {
            if (stations_types[i] == input_type){
                return true;
            }else{
                continue;
            }
        }
        return false;
    }
    else{
        for (unsigned int i = 0; i < trams_types.size();++i) {
            if (trams_types[i] == input_type){
                return true;
            }else{
                continue;
            }
        }
        return false;
    }
}

bool MetroReader::is_Number(string &check_string) {
    // check if this string is a number or not ..
    for (unsigned int i = 0; i < check_string.length(); ++i) {
        if (isdigit(check_string[i])){
            continue;
        }else{
            return false;
        }
    }
    return true;
}

string MetroReader::get_tram_type(TiXmlElement *input_root) {
    for (TiXmlElement* elements = input_root->FirstChildElement(); elements != NULL; elements = elements->NextSiblingElement()) {
        std::string get_element = elements->Value();
        if (get_element == "type"){
            if (elements->FirstChild() == NULL){
                return "NULL";
            }
            string store_type = elements->FirstChild()->Value();
            return store_type;
        }else{
            continue;
        }
    }
    return std::string();
}

SuccessEnum MetroReader::set_tram(bool is_pcc, TiXmlElement *input_root, Systeem &input_systeem,std::ostream& errStream) {
    REQUIRE(input_systeem.properlyInitialized(),"The system wasn' t properlyinitialized correctly!");
    SuccessEnum last = Success;
    if (is_pcc){
        const char* t_Elements[] = {"lijnNr","type","beginStation","snelheid","voertuigNr","aantalDefecten","reparatieTijd"};
        vector<string> pcc_elements(t_Elements, t_Elements + sizeof(t_Elements) / sizeof(t_Elements[0]));
        vector<string>present;
        PCC* make_pcc = new PCC;
        make_pcc->setSnelheid(40);
        make_pcc->setType("PCC");
        for (TiXmlElement* elements = input_root->FirstChildElement(); elements != NULL; elements = elements->NextSiblingElement()) {
            std::string check_element = elements->Value();
            if (check_element == "lijnNr"){
                if (elements->FirstChild() == NULL){
                    errStream << "XML IMPORT ABORTED: LIJNNR NOT PROPERLY INITIALIZED!" << endl;
                    last = ImportAborted;
                    continue;
                }
                const char* get_lijnnummer = elements->FirstChild()->ValueTStr().c_str();
                string to_string(get_lijnnummer);
                bool result = is_Number(to_string);
                if(result){
                    make_pcc->setLijnNr(atoi(get_lijnnummer));
                }else{
                    errStream << "XML IMPORT ABORTED: expected an integer for setting up lijnnummer but got => "<< to_string << endl;
                    errStream << "---------------------------------------------------------------------"<< endl;
                    last = ImportAborted;
                    continue;

                }
            }
            else if (check_element == "aantalDefecten"){
                if (elements->FirstChild() == NULL){
                    errStream << "XML IMPORT ABORTED: AANTAL DEFECTEN NOT PROPERLY INITIALIZED!" << endl;
                    last = ImportAborted;
                    continue;
                }
                const char* get_moves = elements->FirstChild()->ValueTStr().c_str();
                string verify(get_moves);
                if (is_Number(verify)){
                    make_pcc->setStorepccMoves(atoi(get_moves));
                }else{
                    errStream << "XML IMPORT ABORTED: expected an integer for setting up aantaldefecten but got => "<<verify << endl;
                    errStream << "---------------------------------------------------------------------"<< endl;
                    last = ImportAborted;
                    continue;
                }
            }
            else if (check_element == "reparatieTijd"){
                if (elements->FirstChild() == NULL){
                    errStream << "XML IMPORT ABORTED: REPARATIETIJD NOT PROPERLY INITIALIZED!" << endl;
                    last = ImportAborted;
                    continue;
                }
                const char* get_waits = elements->FirstChild()->ValueTStr().c_str();
                string verify(get_waits);
                if (is_Number(verify)){
                    make_pcc->setStorepccWaits(atoi(get_waits));
                }else{
                    errStream << "XML IMPORT ABORTED: expected an integer for setting up reparatieTijd but got => "<<verify << endl;
                    errStream << "---------------------------------------------------------------------"<< endl;
                    last = ImportAborted;
                }
            }
            else if (check_element == "beginStation"){
                if (elements->FirstChild() == NULL){
                    errStream << "XML IMPORT ABORTED: BEGINSTATION NOT PROPERLY INITIALIZED!" << endl;
                    last = ImportAborted;
                    continue;
                }
                string get_beginstation_naam = elements->FirstChild()->ValueTStr().c_str();
                bool result = is_Alphabet(get_beginstation_naam);
                if (result){
                    make_pcc->setBeginstationname(get_beginstation_naam);
                }else{
                    errStream <<"XML IMPORT ABORTED: expected an upper char for initilalizing the beginstation but got => "<<get_beginstation_naam << endl;
                    errStream << "---------------------------------------------------------------------"<< endl;
                    last = ImportAborted;
                    continue;
                }
            }
            else if (check_element == "voertuigNr"){
                if (elements->FirstChild() == NULL){
                    errStream << "XML IMPORT ABORTED: VOERTUIGNR NOT PROPERLY INITIALIZED!"<<endl;
                    last = ImportAborted;
                    continue;
                }
                const char* get_voertuignummer = elements->FirstChild()->ValueTStr().c_str();
                string tostring(get_voertuignummer);
                bool result = is_Number(tostring);
                if (result){
                    make_pcc->setVoertuignummer(atoi(get_voertuignummer));
                }else{
                    errStream << "XML IMPORT ABORTED: expected an integer for voertuigNr but got => "<<tostring << endl;
                    errStream << "---------------------------------------------------------------------"<< endl;
                    last = ImportAborted;
                }
            }
        }
        int check_reparatietijd = make_pcc->getStorepccWaits();
        int check_aantaldefecten = make_pcc->getStorepccMoves();
        if (check_reparatietijd == 0){
            errStream << "XML IMPORT ABORTED: repairtime for pcc not present because current value: "<<check_reparatietijd << endl;
            last = ImportAborted;
        }
        if (check_aantaldefecten == 0){
            errStream << "XML IMPORT ABORTED: moves not present before defect for pcc because current value: "<<check_aantaldefecten << endl;
            last = ImportAborted;
        }

        vector<Tram*> adding_vector = input_systeem.getTrams();
        adding_vector.push_back(make_pcc);
        input_systeem.setTrams(adding_vector);
    }
    else{
        Tram* new_tram = new Tram;
        for (TiXmlElement* elements = input_root->FirstChildElement(); elements != NULL; elements = elements->NextSiblingElement()) {
            std::string check_element = elements->Value();
            if (check_element == "lijnNr"){
                if (elements->FirstChild() == NULL){
                    errStream << "XML IMPORT ABORTED: LIJNNR NOT PROPERLY INITIALIZED!" << endl;
                    last = ImportAborted;
                    continue;
                }
                const char* get_lijnnummer = elements->FirstChild()->ValueTStr().c_str();
                string to_string(get_lijnnummer);
                bool result = is_Number(to_string);
                if(result){
                    new_tram->setLijnNr(atoi(get_lijnnummer));
                }else{
                    errStream << "XML IMPORT ABORTED: expected an integer for setting up lijnnummer but got => "<< to_string << endl;
                    errStream << "---------------------------------------------------------------------"<< endl;
                    last = ImportAborted;
                }
            }
            if (check_element == "type"){
                if (elements->FirstChild() == NULL){
                    errStream << "XML IMPORT ABORTED: TYPE NOT PROPERLY INITIALIZED FOR ALBATROS OR STADSLIJNER" << endl;
                    last = ImportAborted;
                    continue;
                }
                string get_type = elements->FirstChild()->ValueTStr().c_str();
                bool result = check_type(get_type,false);
                if (result){
                    new_tram->setType(get_type);
                    if (new_tram->getType() == "Albatros" or new_tram->getType() == "Stadslijner"){
                        new_tram->setSnelheid(70);
                    }
                }else{
                    errStream <<"XML IMPORT ABORTED: expected PCC or Albatros or Stadslijner but got => "<< get_type << endl;
                    errStream << "---------------------------------------------------------------------"<< endl;
                    last = ImportAborted;
                }
            }
            if (check_element == "beginStation"){
                if (elements->FirstChild() == NULL){
                    errStream << "XML IMPORT ABORTED: BEGINSTATION NOT PROPERLY INITIALIZED!" << endl;
                    last = ImportAborted;
                    continue;
                }
                string get_beginstation_naam = elements->FirstChild()->ValueTStr().c_str();
                bool result = is_Alphabet(get_beginstation_naam);
                if (result){
                    // TRAMS VAN TYPE METRO
                    for (unsigned int i = 0; i < input_systeem.getStations().size(); ++i) {
                        string get_naam = input_systeem.getStations()[i]->getNaam();
                        if (get_naam == get_beginstation_naam){
                            string get_type = input_systeem.getStations()[i]->getType();// metrostation of een halte
                            string get_tramtype = new_tram->getType();
                            if ((get_tramtype == "Stadslijner" or get_tramtype == "Albatros") and get_type == "Metrostation"){
                                new_tram->setBeginstationname(get_beginstation_naam);
                                continue;
                            }
                            if (get_tramtype == "PCC"){
                                new_tram->setBeginstationname(get_beginstation_naam);
                                continue;
                            }
                            errStream << "XML PARTIAL IMPORT: tramtype of albatros or stadslijner can only be initialized to a metrostation but got: "<< get_type << endl;
                            errStream << "---------------------------------------------------------------------"<< endl;
                            last = ImportAborted;
                        }
                    }
                }
                else{
                    errStream <<"XML IMPORT ABORTED: expected an upper char for initilalizing the beginstation but got => "<<get_beginstation_naam << endl;
                    errStream << "---------------------------------------------------------------------"<< endl;
                    last = ImportAborted;
                }
            }
            if (check_element == "voertuigNr"){
                if (elements->FirstChild() == NULL){
                    errStream << "XML IMPORT ABORTED: VOERTUIGNR NOT PROPERLY INITIALIZED!"<<endl;
                    last = ImportAborted;
                    continue;
                }
                const char* get_voertuignummer = elements->FirstChild()->ValueTStr().c_str();
                string tostring(get_voertuignummer);
                bool result = is_Number(tostring);
                if (result){
                    new_tram->setVoertuignummer(atoi(get_voertuignummer));
                }else{
                    errStream << "XML IMPORT ABORTED: expected an integer for voertuigNr but got => "<<tostring << endl;
                    errStream << "---------------------------------------------------------------------"<< endl;
                    last = ImportAborted;
                    continue;
                }
            }
        }
        //copy constructed the vector from class
        vector<Tram*> adding_vector = input_systeem.getTrams();
        adding_vector.push_back(new_tram);
        input_systeem.setTrams(adding_vector);
    }
    return last;
}