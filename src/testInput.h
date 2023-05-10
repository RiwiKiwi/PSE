//
// Created by aburahman10 on 17/03/23.
//

#ifndef PROJECTSOFTWAREENGINEER_TESTINPUT_H
#define PROJECTSOFTWAREENGINEER_TESTINPUT_H

#endif //PROJECTSOFTWAREENGINEER_TESTINPUT_H

#include "iostream"
#include "fstream"
#include "sys/stat.h"
#include <gtest/gtest.h>
#include <sstream>
#include "simulationUtils.h"
#include "MetroReader.h"

using namespace std;

class testInput : public ::testing::Test {
};
// checking if the input test directory exists
TEST_F(testInput,check_inputttest_directory){
    bool dir_status = DirectoryExists("../input_tests");
    ASSERT_TRUE(dir_status);
}
// TESTING IF ALL INPUTFILES AREN'T EMPTY

// TESTING WRONG TAGNAME VOOR ROOT
TEST_F(testInput,check_return_wrongrootfiles){
    bool dir_status = DirectoryExists("../input_tests");
    ASSERT_TRUE(dir_status);
    Systeem new_system;
    unsigned int counter = 1;
    std::ofstream output("../input_tests/errors.txt",ios_base::app);
    while(counter < 4){
        // converting counter to string
        std::stringstream ss;
        ss << counter;
        string xml_file = "wrong_root_"+ss.str()+".xml";
        bool check_file = FileExists("../input_tests/"+xml_file);
        ASSERT_TRUE(check_file);
        bool not_empty = FileIsEmpty("../input_tests/"+xml_file);
        EXPECT_FALSE(not_empty);
        string file = "../input_tests/"+xml_file;
        // omzetting naar const char * => c_str()
        SuccessEnum result = MetroReader::importXml(file.c_str(),output,new_system);
        EXPECT_EQ(PartialImport,result);
        //reset the string for next number
        ss.str() = "";
        counter += 1;
    }
}
// TESTING WRONG TAGNAME FOR SUBROOT
TEST_F(testInput,check_return_wrongsubrootfiles){
    bool dir_status = DirectoryExists("../input_tests");
    ASSERT_TRUE(dir_status);
    unsigned int counter = 1;
    Systeem new_system;
    std::ofstream output("../input_tests/errors.txt",ios_base::app);
    // THERE ARE 3 FILES IN TOTAL TO CHECK FOR WRONG ROOT NAMES !
    while (counter < 4){
        // converting counter to string
        std::stringstream ss;
        ss << counter;
        string xml_file = "wrong_subroot_"+ss.str()+".xml";
        bool check_file = FileExists("../input_tests/"+xml_file);
        ASSERT_TRUE(check_file);
        bool not_empty = FileIsEmpty("../input_tests/"+xml_file);
        EXPECT_FALSE(not_empty);
        string file = "../input_tests/"+xml_file;
        // omzetting naar const char * => c_str()
        SuccessEnum result = MetroReader::importXml(file.c_str(),output,new_system);
        EXPECT_EQ(ImportAborted,result);
        //reset the string for next number
        ss.str() = "";
        counter += 1;
    }
}
// CHECKING VOOR WRONG TAG NAMES FOR STATIONELEMENTS
TEST_F(testInput,check_return_wrongstation_elements){
    bool dir_status = DirectoryExists("../input_tests");
    ASSERT_TRUE(dir_status);
    unsigned int counter = 1;
    Systeem new_system;
    std::ofstream output("../input_tests/errors.txt",ios_base::app);
    // THERE ARE 4 FILES IN TOTAL TO CHECK FOR WRONG ROOT NAMES !
    while (counter < 5){
        // converting counter to string
        std::stringstream ss;
        ss << counter;
        string xml_file = "wrong_objectelements_station_"+ss.str()+".xml";
        bool check_file = FileExists("../input_tests/"+xml_file);
        ASSERT_TRUE(check_file);
        bool not_empty = FileIsEmpty("../input_tests/"+xml_file);
        EXPECT_FALSE(not_empty);
        string file = "../input_tests/"+xml_file;
        // omzetting naar const char * => c_str()
        SuccessEnum result = MetroReader::importXml(file.c_str(),output,new_system);
        EXPECT_EQ(ImportAborted, result);
        //reset the string for next number
        ss.str() = "";
        counter += 1;
    }
}
//CHECKING VOOR WRONG TAG NAMES FOR TRAMELEMENTS
TEST_F(testInput,check_wrongtram_elements){
    Systeem make_system;
    unsigned int counter = 1;
    std::ofstream output("../input_tests/errors.txt",ios_base::app);
    while (counter < 5){
        std::stringstream ss;
        ss << counter;
        string xml_file = "wrong_objectelements_tram_"+ss.str()+".xml";
        bool check_file = FileExists("../input_tests/"+xml_file);
        ASSERT_TRUE(check_file);
        bool not_empty = FileIsEmpty("../input_tests/"+xml_file);
        EXPECT_FALSE(not_empty);
        string file = "../input_tests/"+xml_file;
        // omzetting naar const char * => c_str()
        SuccessEnum result = MetroReader::importXml(file.c_str(),output,make_system);
        EXPECT_EQ(ImportAborted, result);
        ss.str() = "";
        counter += 1;
    }
}

// CHECKER FOR SYNTAXERRORS
TEST_F(testInput,syntax_attributeerrors){
    Systeem new_system;
    unsigned int counter = 1;
    std::ofstream output("../input_tests/errors.txt",ios_base::app);
    do {
        std::stringstream ss;
        ss << counter;
        string xml_file = "syntax_attributeerror_"+ss.str()+".xml";
        bool check_file = FileExists("../input_tests/"+xml_file);
        ASSERT_TRUE(check_file);
        bool not_empty = FileIsEmpty("../input_tests/"+xml_file);
        EXPECT_FALSE(not_empty);
        string file = "../input_tests/"+xml_file;
        // omzetting naar const char * => c_str()
        SuccessEnum result = MetroReader::importXml(file.c_str(),output,new_system);
        EXPECT_EQ(ImportAborted, result);
        ss.str() = "";
        counter += 1;
    }while(counter < 6);
}
// CHECKING FOR WRONG INPUTS FROM THE USER FOR STATION
TEST_F(testInput,wrong_inputs_station){
    Systeem new_system;
    unsigned int counter = 1;
    std::ofstream output("../input_tests/errors.txt",ios_base::app);
    do {
        std::stringstream ss;
        ss << counter;
        string xml_file = "inputerror_station_"+ss.str()+".xml";
        bool check_file = FileExists("../input_tests/"+xml_file);
        ASSERT_TRUE(check_file);
        bool not_empty = FileIsEmpty("../input_tests/"+xml_file);
        EXPECT_FALSE(not_empty);
        string file = "../input_tests/"+xml_file;
        // omzetting naar const char * => c_str()
        SuccessEnum result = MetroReader::importXml(file.c_str(),output,new_system);
        EXPECT_EQ(ImportAborted, result);
        ss.str() = "";
        counter += 1;
    }while(counter < 6);
}
// CHECKING FOR WRONG INPUTS FROM THE USER FOR TRAM
TEST_F(testInput,wrong_inputs_tram){
    Systeem new_system;
    std::ofstream output("../input_tests/errors.txt",ios_base::app);
    unsigned int counter = 1;
    do {
        std::stringstream ss;
        ss << counter;
        string xml_file = "inputerror_tram_"+ss.str()+".xml";
        bool check_file = FileExists("../input_tests/"+xml_file);
        ASSERT_TRUE(check_file);
        bool not_empty = FileIsEmpty("../input_tests/"+xml_file);
        EXPECT_FALSE(not_empty);
        string file = "../input_tests/"+xml_file;
        // omzetting naar const char * => c_str()
        SuccessEnum result = MetroReader::importXml(file.c_str(),output,new_system);
        EXPECT_EQ(ImportAborted, result);
        ss.str() = "";
        counter += 1;
    }while(counter <= 5);
}