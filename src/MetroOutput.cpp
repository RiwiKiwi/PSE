//
// Created by riwi on 4/05/23.
//

#include "MetroOutput.h"
#include <fstream>
#include "DesignByContract.h"


MetroOutput::MetroOutput(const vector<Tram *> &trams, const vector<Station *> &stations) : trams(trams),stations(stations) {
}


void MetroOutput::writeOver(){
    REQUIRE(!stations.empty(),"simple writeOver precondition failed");
    REQUIRE(!trams.empty(),"simple writeOver precondition failed");
    ofstream out("../output_tests/normal_scenario0_output.txt");
    for (unsigned int i = 0; i < stations.size(); i++)
    {
        out<< "Station "<< stations[i]->getNaam() << endl;
        out << "<- "<< stations[i]->getPrev() << endl;
        out << "-> " << stations[i]->getNext() << endl;

        for (unsigned x = 0; x < stations[i]->getSpoorNrs().size(); x++)
        {
            out << "Spoor " << stations[i]->getSpoorNrs()[x] << endl;
        }

        out << endl;
    }

    for (unsigned int j = 0; j < trams.size(); j++)
    {
        out << "Tram " << trams[j]->getLijnNr() << " in Station " << trams[j]->getBeginStation()->getNaam() << endl;
    }

    ifstream file("../output_tests/normal_scenario0_output.txt");
    ENSURE(file.peek() != ifstream::traits_type::eof(),"writeOver postcondition failed");
}


void MetroOutput::simple_writeover() {
    ofstream out("../output_tests/normal_scenario1_output.txt");
    REQUIRE(!stations.empty(),"simple writeOver precondition failed");
    REQUIRE(!trams.empty(),"simple writeOver precondition failed");
    out << "--== STATIONS ==--" << endl;
    for (unsigned int i = 0; i < stations.size(); i++) {
        Station* write_station = stations[i];
        out <<"= "<<"Station "<<write_station->getNaam()<<" ="<<endl;
        out << "type: "<< write_station->getType() << endl;
        //bij onze versie is er alleen maar 1 spoor dus ik ga ni doorheen de vector loopen maar gwn getspoor oproepen en volgende en vorige laten wijzen
        out <<"*"<<" Spoor "<<write_station->getSpoor()<<":"<<endl;
        out <<"\t"<<"<- "<< stations[i]->getPrev() << endl;
        out <<"\t"<< "-> " << stations[i]->getNext() << endl;
    }
    out << "--== TRAMS ==--" << endl;
    for (unsigned int i = 0; i < trams.size(); ++i) {
        Tram* write_tram = trams[i];
        out << "Tram "<<write_tram->getLijnNr()<<" nr "<<write_tram->getVoertuignummer() << endl;
        out <<"\t"<<" type: " << write_tram->getType() << endl;
        if(write_tram->getType() == "PCC"){
            PCC* my_pcc = dynamic_cast<PCC*>(write_tram);
            out <<"\t "<<"aantalDefecten: " << my_pcc->getStorepccMoves()<< endl;
            out <<"\t "<<"reparatieTijd: " << my_pcc->getStorepccWaits() << endl;
        }
        out <<"\t"<<" snelheid: " << write_tram->getSnelheid() << endl;
        out <<"\t"<<" huidig station: " << write_tram->getHuidigeStation()->getNaam() << endl;
    }
    ifstream file("../output_tests/normal_scenario1_output.txt");

    ENSURE(file.peek() != ifstream::traits_type::eof(),"writeOver postcondition failed");
}

void MetroOutput::advanced_writeover() {
    /*
  * THIS IS USECASE 2.3
  */
    REQUIRE(!stations.empty(),"advanced writeOver precondition failed");
    REQUIRE(!stations.empty(),"advanced writeOver precondition failed");
    ofstream out("../output_tests/normal_scenario2_output.txt");
    //NOTE => We hebben stations met meerdere sporen niet beloofd dus er zal altijd maar 1 spoor zijn per XML file
    string my_station;
    my_station.push_back('=');
    // SETTING UP THE STRING STATION FIRST
    for (unsigned int i = 0; i < stations.size(); ++i) {
        Station* get_station = stations[i];
        my_station += get_station->getNaam();
        if (i == stations.size()-1){
            break;
        }else{
            my_station += "===";
        }
    }
    my_station.push_back('=');
    // GO THROUGH THE STRING STATION TO APPEND T WHERE THE TRAM IS !
    string my_tram;
    for (unsigned int i = 0; i < my_station.size(); i++)
    {
        //tostring
        string compare_char(1,my_station[i]);
        if (compare_char == "=")
        {
            my_tram += " ";
            continue;
        }
        else
        {
            //tostring
            string check_char(1,my_station[i]);
            for (unsigned int j = 0; j < trams.size(); ++j)
            {
                Tram* checking_tram = trams[j];
                string get_station = checking_tram->getHuidigeStation()->getNaam();
                if (check_char == get_station)
                {
                    my_tram +="T";
                }
                else
                {
                    my_tram +=" ";
                }
            }
        }
    }
    // REMOVING SPACES AFTER LAST TRAM
    unsigned long int aant_trams = 0;
    string final_tram;
    for (unsigned int i = 0; i < my_tram.length(); ++i)
    {
        char our_char = my_tram[i];
        final_tram += our_char;
        if (our_char == 'T')
        {
            aant_trams++;
        }
        if (aant_trams == trams.size())
        {
            break;
        }
    }

    out << my_station << endl << final_tram << endl;
    out.close();
}

void MetroOutput::verplaatstram() {
    REQUIRE(!trams.empty(),"verplaatstram precondition failed");

    ofstream out("../output_tests/automatic_simulation1_output.txt",ios_base::app);

    if (out.is_open())
    {
        for (unsigned int j = 0; j < trams.size(); j++)
        {
            string get_type = trams[j]->getType();
            string currentstation_type = trams[j]->getHuidigeStation()->getVolgende()->getType();
            if (get_type == "PCC"){
                //casting to it's object to use the getters and setters of it
                PCC* my_pcc = dynamic_cast<PCC*>(trams[j]);
                int get_moves = my_pcc->getCurrMoves();
                if (get_moves > 0){
                    out << "Tram " << my_pcc->getLijnNr() <<" van het type "<< my_pcc->getType()<< " reed van station " << my_pcc->getHuidigeStation()->getNaam()<<" naar het station "<<my_pcc->getHuidigeStation()->getVolgende()->getNaam()<<endl;
                    my_pcc->setHuidigeStation(trams[j]->getHuidigeStation()->getVolgende());
                    my_pcc->setCurrMoves(get_moves - 1);
                }else{
                    // geen moves meer left dus wachten ...
                    int current_wait = my_pcc->getCurrWaits();
                    if (current_wait == 0){
                        //RESTORING MY OLD VALUES AGAIN TO THIS PCC TRAM
                        int store_waits = my_pcc->getStorepccWaits();
                        int store_moves = my_pcc->getStorepccMoves();
                        my_pcc->setCurrMoves(store_moves);
                        my_pcc->setCurrWaits(store_waits);
                        out << "Tram "<< my_pcc->getLijnNr() << " van het type " << my_pcc->getType() << " is ready to go!"<< endl;
                    }else{
                        // Tram is in de panne gevallen dus wachttijd gaat iedere keer -= 1
                        out << "Tram " << my_pcc->getLijnNr() <<" van het type " << my_pcc->getType() << " heeft defect " << "estimated waitingtime: "<< my_pcc->getCurrWaits()<< endl;
                        my_pcc->setCurrWaits(current_wait - 1);
                    }

                }
                // move this tram and go to next tram !
                continue;
            }else{
                // MY TYPE IS NOW STADSLIJNER OR ALBATROS
                string volgend_station_type = trams[j]->getHuidigeStation()->getVolgende()->getType();
                if (volgend_station_type == "Metrostation"){
                    // THIS IS THE NOTIFICATION OF WHERE IT WILL GO FIRST
                    out << "Tram " << trams[j]->getLijnNr() <<" van het type "<< trams[j]->getType()<< " reed van station " << trams[j]->getHuidigeStation()->getNaam()<<" naar het station "<<trams[j]->getHuidigeStation()->getVolgende()->getNaam()<<endl;
                    trams[j]->setHuidigeStation(trams[j]->getHuidigeStation()->getVolgende());
                    // move this tram and go to next tram !
                    continue;
                }else{
                    // THIS IS FOR HALTE IF MY TRAMTYPE IS STADSLIJNER OR ALBATROS
                    string my_types;
                    // hou het start station van dit albatros of stadslijner bij !
                    Station* store_begin = trams[j]->getHuidigeStation();
                    // Dit is het station die bewerkt gaat blijven in de loop tot die een metrostation vindt !
                    Station* my_next = trams[j]->getHuidigeStation();
                    do{
                        my_next = trams[j]->getHuidigeStation()->getVolgende();
                        string store_type = my_next->getType();
                        trams[j]->setHuidigeStation(my_next);

                        my_types = store_type;
                    } while (my_types != "Metrostation");
                    // ik verplaats het al in men whileloop dus ik moet da hier niet doen !
                    out << "Tram " << trams[j]->getLijnNr() <<" van het type "<< trams[j]->getType()<< " reed van station " << store_begin->getNaam()<<" naar het station "<<my_next->getNaam()<<endl;
                }
            }
        }
    }

    out.close();
}

void MetroOutput::rijd(int stappen)
{
    REQUIRE(stappen > 0 , "rijd precondition failed");
    int stap = 0;

    while (stap < stappen)
    {
        verplaatstram();
        stap++;
    }
}



