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
// TESTING IF ALL INPUTFILES AREN'T EMPTY & that they all exist to test it out
TEST_F(testInput,Emptynesstest){
    unsigned int inconsistent_files = 6;
    unsigned int counter = 1;
    do{
        std::stringstream ss;
        ss << counter;
        bool dir_status = DirectoryExists("../input_tests");
        ASSERT_TRUE(dir_status);
        string check_file = "inconsistent_"+ss.str()+".xml";
        bool present_file = FileExists("../input_tests/"+check_file);
        EXPECT_TRUE(present_file);
        bool check_emptyness = FileIsEmpty("../input_tests/"+check_file);
        ASSERT_FALSE(check_emptyness);
        ss.str() = "";
        counter++;
    }while(counter <=inconsistent_files);

    counter = 1;

    unsigned int inputstation_files = 5;
    do{
        std::stringstream ss;
        ss << counter;
        bool dir_status = DirectoryExists("../input_tests");
        ASSERT_TRUE(dir_status);
        string check_file = "inputerror_station_"+ss.str()+".xml";
        bool present_file = FileExists("../input_tests/"+check_file);
        EXPECT_TRUE(present_file);
        bool check_emptyness = FileIsEmpty("../input_tests/"+check_file);
        ASSERT_FALSE(check_emptyness);
        ss.str() = "";
        counter++;
    }while(counter <= inputstation_files);

    counter = 1;

    unsigned int inputtram_files = 5;
    do{
        std::stringstream ss;
        ss << counter;
        bool dir_status = DirectoryExists("../input_tests");
        ASSERT_TRUE(dir_status);
        string check_file = "inputerror_tram_"+ss.str()+".xml";
        bool present_file = FileExists("../input_tests/"+check_file);
        EXPECT_TRUE(present_file);
        bool check_emptyness = FileIsEmpty("../input_tests/"+check_file);
        ASSERT_FALSE(check_emptyness);
        ss.str() = "";
        counter++;
    }while(counter <= inputtram_files);

    counter = 1;

    unsigned int syntax_files = 6;
    do{
        std::stringstream ss;
        ss << counter;
        bool dir_status = DirectoryExists("../input_tests");
        ASSERT_TRUE(dir_status);
        string check_file = "syntax_attributeerror_"+ss.str()+".xml";
        bool present_file = FileExists("../input_tests/"+check_file);
        EXPECT_TRUE(present_file);
        bool check_emptyness = FileIsEmpty("../input_tests/"+check_file);
        ASSERT_FALSE(check_emptyness);
        ss.str() = "";
        counter++;
    }while(counter <= syntax_files);

    counter = 1;

    unsigned int wrongobjectstations = 4;
    do{
        std::stringstream ss;
        ss << counter;
        bool dir_status = DirectoryExists("../input_tests");
        ASSERT_TRUE(dir_status);
        string check_file = "wrong_objectelements_station_"+ss.str()+".xml";
        bool present_file = FileExists("../input_tests/"+check_file);
        EXPECT_TRUE(present_file);
        bool check_emptyness = FileIsEmpty("../input_tests/"+check_file);
        ASSERT_FALSE(check_emptyness);
        ss.str() = "";
        counter++;
    }while(counter <= wrongobjectstations);

    counter = 1;

    unsigned int wrongobjecttrams = 4;
    do{
        std::stringstream ss;
        ss << counter;
        bool dir_status = DirectoryExists("../input_tests");
        ASSERT_TRUE(dir_status);
        string check_file = "wrong_objectelements_tram_"+ss.str()+".xml";
        bool present_file = FileExists("../input_tests/"+check_file);
        EXPECT_TRUE(present_file);
        bool check_emptyness = FileIsEmpty("../input_tests/"+check_file);
        ASSERT_FALSE(check_emptyness);
        ss.str() = "";
        counter++;
    }while(counter <= wrongobjecttrams);

    counter = 1;

    unsigned int wrongroot = 3;
    do{
        std::stringstream ss;
        ss << counter;
        bool dir_status = DirectoryExists("../input_tests");
        ASSERT_TRUE(dir_status);
        string check_file = "wrong_root_"+ss.str()+".xml";
        bool present_file = FileExists("../input_tests/"+check_file);
        EXPECT_TRUE(present_file);
        bool check_emptyness = FileIsEmpty("../input_tests/"+check_file);
        ASSERT_FALSE(check_emptyness);
        ss.str() = "";
        counter++;
    }while(counter <= wrongroot);

    counter = 1;

    unsigned int wrongsubroot = 3;
    do{
        std::stringstream ss;
        ss << counter;
        bool dir_status = DirectoryExists("../input_tests");
        ASSERT_TRUE(dir_status);
        string check_file = "wrong_subroot_"+ss.str()+".xml";
        bool present_file = FileExists("../input_tests/"+check_file);
        EXPECT_TRUE(present_file);
        bool check_emptyness = FileIsEmpty("../input_tests/"+check_file);
        ASSERT_FALSE(check_emptyness);
        ss.str() = "";
        counter++;
    }while(counter <= wrongsubroot);

}

// TESTING WRONG TAGNAME VOOR ROOT
TEST_F(testInput,check_return_wrongrootfiles){
    bool dir_status = DirectoryExists("../input_tests");
    ASSERT_TRUE(dir_status);
    Systeem new_system;
    unsigned int counter = 1;
    std::ofstream output("../input_tests/tag_errors.txt",ios_base::app);
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
    std::ofstream output("../input_tests/tag_errors.txt",ios_base::app);
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
    std::ofstream output("../input_tests/tag_errors.txt",ios_base::app);
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
    std::ofstream output("../input_tests/tag_errors.txt",ios_base::app);
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
TEST_F(testInput,syntax_error1){
    std::ofstream make_file("../input_tests/syntax_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/syntax_attributeerror_1.xml");
    EXPECT_TRUE(file);
    Systeem make_system_one;
    SuccessEnum result = MetroReader::importXml("../input_tests/syntax_attributeerror_1.xml",make_file,make_system_one);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}

TEST_F(testInput,syntax_error2){
    std::ofstream make_file("../input_tests/syntax_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/syntax_attributeerror_2.xml");
    EXPECT_TRUE(file);
    Systeem make_system_one;
    SuccessEnum result = MetroReader::importXml("../input_tests/syntax_attributeerror_2.xml",make_file,make_system_one);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}
TEST_F(testInput,syntax_error3){
    std::ofstream make_file("../input_tests/syntax_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/syntax_attributeerror_3.xml");
    EXPECT_TRUE(file);
    Systeem make_system_one;
    SuccessEnum result = MetroReader::importXml("../input_tests/syntax_attributeerror_3.xml",make_file,make_system_one);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}

TEST_F(testInput,syntax_error4){
    std::ofstream make_file("../input_tests/syntax_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/syntax_attributeerror_4.xml");
    EXPECT_TRUE(file);
    Systeem make_system_one;
    SuccessEnum result = MetroReader::importXml("../input_tests/syntax_attributeerror_4.xml",make_file,make_system_one);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}
TEST_F(testInput,syntax_error5){
    std::ofstream make_file("../input_tests/syntax_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/syntax_attributeerror_5.xml");
    EXPECT_TRUE(file);
    Systeem make_system_one;
    SuccessEnum result = MetroReader::importXml("../input_tests/syntax_attributeerror_5.xml",make_file,make_system_one);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}

TEST_F(testInput,syntax_error6){
    std::ofstream make_file("../input_tests/syntax_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/syntax_attributeerror_6.xml");
    EXPECT_TRUE(file);
    Systeem make_system_one;
    SuccessEnum result = MetroReader::importXml("../input_tests/syntax_attributeerror_6.xml",make_file,make_system_one);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}

// CHECKING FOR WRONG INPUTS FROM THE USER FOR STATION
TEST_F(testInput,input_error_station1){
    std::ofstream make_file("../input_tests/inputstation_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/inputerror_station_1.xml");
    EXPECT_TRUE(file);
    Systeem make_system_one;
    SuccessEnum result = MetroReader::importXml("../input_tests/inputerror_station_1.xml",make_file,make_system_one);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}
TEST_F(testInput,input_error_station2){
    std::ofstream make_file("../input_tests/inputstation_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/inputerror_station_2.xml");
    EXPECT_TRUE(file);
    Systeem make_system;
    SuccessEnum result = MetroReader::importXml("../input_tests/inputerror_station_2.xml",make_file,make_system);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}
TEST_F(testInput,input_error_station3){
    std::ofstream make_file("../input_tests/inputstation_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/inputerror_station_3.xml");
    EXPECT_TRUE(file);
    Systeem make_system;
    SuccessEnum result = MetroReader::importXml("../input_tests/inputerror_station_3.xml",make_file,make_system);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}
TEST_F(testInput,input_error_station4){
    std::ofstream make_file("../input_tests/inputstation_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/inputerror_station_4.xml");
    EXPECT_TRUE(file);
    Systeem make_system;
    SuccessEnum result = MetroReader::importXml("../input_tests/inputerror_station_4.xml",make_file,make_system);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}
TEST_F(testInput,input_error_station5){
    std::ofstream make_file("../input_tests/inputstation_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/inputerror_station_5.xml");
    EXPECT_TRUE(file);
    Systeem make_system;
    SuccessEnum result = MetroReader::importXml("../input_tests/inputerror_station_5.xml",make_file,make_system);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}
// CHECKING FOR WRONG INPUTS FROM THE USER FOR TRAM
TEST_F(testInput,input_error_tram1){
    std::ofstream make_file("../input_tests/inputtram_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/inputerror_tram_1.xml");
    EXPECT_TRUE(file);
    Systeem make_system;
    SuccessEnum result = MetroReader::importXml("../input_tests/inputerror_tram_1.xml",make_file,make_system);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}
TEST_F(testInput,input_error_tram2){
    std::ofstream make_file("../input_tests/inputtram_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/inputerror_tram_2.xml");
    EXPECT_TRUE(file);
    Systeem make_system;
    SuccessEnum result = MetroReader::importXml("../input_tests/inputerror_tram_2.xml",make_file,make_system);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}
TEST_F(testInput,input_error_tram3){
    std::ofstream make_file("../input_tests/inputtram_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/inputerror_tram_3.xml");
    EXPECT_TRUE(file);
    Systeem make_system;
    SuccessEnum result = MetroReader::importXml("../input_tests/inputerror_tram_3.xml",make_file,make_system);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}
TEST_F(testInput,input_error_tram4){
    std::ofstream make_file("../input_tests/inputtram_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/inputerror_tram_4.xml");
    EXPECT_TRUE(file);
    Systeem make_system;
    SuccessEnum result = MetroReader::importXml("../input_tests/inputerror_tram_4.xml",make_file,make_system);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}
TEST_F(testInput,input_error_tram5){
    std::ofstream make_file("../input_tests/inputtram_errors.txt");
    bool Dir_exists = DirectoryExists("../input_tests");
    ASSERT_TRUE(Dir_exists);
    bool file = FileExists("../input_tests/inputerror_tram_5.xml");
    EXPECT_TRUE(file);
    Systeem make_system;
    SuccessEnum result = MetroReader::importXml("../input_tests/inputerror_tram_5.xml",make_file,make_system);
    make_file << "\n" << endl;
    EXPECT_TRUE(result == ImportAborted);
}