//
// Created by riwi on 20/03/23.
//

#ifndef PROJECTSOFTWAREENGINEER_TESTOUTPUT_H
#define PROJECTSOFTWAREENGINEER_TESTOUTPUT_H

#endif //PROJECTSOFTWAREENGINEER_TESTOUTPUT_H
#include <gtest/gtest.h>
#include "Systeem.h"
#include "simulationUtils.h"
#include "MetroOutput.h"

class testOutput : public ::testing::Test {};

TEST_F(testOutput,check_outputttest_directory)
{
    bool directory_exits = DirectoryExists("../output_tests");
    ASSERT_TRUE(directory_exits);
}

TEST_F(testOutput,BasicFileCompare)
{
    bool directory_exits = DirectoryExists("../output_tests");
    ASSERT_TRUE(directory_exits);

    //opening the 2 testing files
    std::ofstream myfile;
    myfile.open("../output_tests/file1.txt");
    myfile.close();
    myfile.open("../output_tests/file2.txt");
    myfile.close();

    //emptyfile exists and ofcourse it is empty too
    EXPECT_TRUE(FileExists("../output_tests/file1.txt"));
    EXPECT_TRUE(FileExists("../output_tests/file2.txt"));
    EXPECT_TRUE(FileIsEmpty("../output_tests/file1.txt"));
    EXPECT_TRUE(FileIsEmpty("../output_tests/file2.txt"));


    //compare 2 empty files
    EXPECT_TRUE(FileCompare("../output_tests/file1.txt", "../output_tests/file2.txt"));
    EXPECT_TRUE(FileCompare("../output_tests/file2.txt", "../output_tests/file1.txt"));

    //compare an empty and a non-empty files
    myfile.open("../output_tests/file1.txt");
    myfile << "xxx" << std::endl << "yyy";
    myfile.close();
    //file 1 is not empty anymore
    EXPECT_TRUE(FileExists("../output_tests/file1.txt"));
    EXPECT_FALSE(FileIsEmpty("../output_tests/file1.txt"));
    EXPECT_FALSE(FileCompare("../output_tests/file1.txt", "../output_tests/file2.txt"));
    EXPECT_FALSE(FileCompare("../output_tests/file2.txt", "../output_tests/file1.txt"));

    //compare two equal files
    myfile.open("../output_tests/file2.txt");
    myfile << "xxx" << std::endl << "yyy";
    myfile.close();
    //file 2 is not empty anymore
    EXPECT_TRUE(FileExists("../output_tests/file2.txt"));
    EXPECT_FALSE(FileIsEmpty("../output_tests/file2.txt"));
    EXPECT_TRUE(FileCompare("../output_tests/file1.txt", "../output_tests/file2.txt"));
    EXPECT_TRUE(FileCompare("../output_tests/file2.txt", "../output_tests/file1.txt"));

    //compare 2 non-empty files which are off by a character in the middle
    myfile.open("../output_tests/file2.txt");
    myfile << "xxx" << std::endl << "xyy";
    myfile.close();
    EXPECT_FALSE(FileCompare("../output_tests/file1.txt", "../output_tests/file2.txt"));
    EXPECT_FALSE(FileCompare("../output_tests/file2.txt", "../output_tests/file1.txt"));

    //compare 2 non-empty files where one is one character shorter than the other
    myfile.open("../output_tests/file2.txt");
    myfile << "xxx" << std::endl << "yy";
    myfile.close();
    // these 2 files are not the same anymore
    EXPECT_FALSE(FileCompare("../output_tests/file1.txt", "../output_tests/file2.txt"));
    EXPECT_FALSE(FileCompare("../output_tests/file2.txt", "../output_tests/file1.txt"));

    //compare existing against non existing file
    EXPECT_FALSE(
            FileCompare("../output_tests/file1.txt", "../output_tests/nonexisting.txt"));
    EXPECT_FALSE(
            FileCompare("../output_tests/nonexisting.txt", "../output_tests/file1.txt"));
}
//TESTING OUR AUTOMATIC SIMULATION WHEN WE MOVE THE TRAM 20 TIMES
TEST_F(testOutput, check_automatic_simulation)
{
    bool directory_exits = DirectoryExists("../output_tests");
    ASSERT_TRUE(directory_exits);

    Systeem systeem;
    SuccessEnum succes = MetroReader::importXml("../src/advanced_ascii.xml",cerr,systeem);

    if (succes == Success)
    {
        ASSERT_TRUE(systeem.checkConsistent());
        //Generate output using outputclass object
        MetroOutput print(systeem.getTrams(),systeem.getStations());
        systeem.rijd(20);
        bool compare = FileCompare("../output_tests/automatic_simulation1_output.txt","../output_tests/automatic_expect_20.txt");
        EXPECT_TRUE(compare);
    }
}
// TESTING WRITEOVER FUNCTION OF OUR OUTPUTCLASS
TEST_F(testOutput, check_scenario0)
{
    bool directory_exits = DirectoryExists("../output_tests");
    ASSERT_TRUE(directory_exits);

    Systeem systeem;

    SuccessEnum succes = MetroReader::importXml("../src/advanced_ascii.xml",cerr,systeem);

    if (succes == Success)
    {
        ASSERT_TRUE(systeem.checkConsistent());
        //Generate output using outputclass object
        MetroOutput print(systeem.getTrams(),systeem.getStations());
        print.writeOver();
        bool compare = FileCompare("../output_tests/normal_scenario0_expect.txt","../output_tests/normal_scenario0_output.txt");
        EXPECT_TRUE(compare);
    }
}
//TESTING THE SIMPLE WRITEOVER OF OUR OUTPUTCLASS
TEST_F(testOutput, check_scenario1)
{
    bool directory_exits = DirectoryExists("../output_tests");
    ASSERT_TRUE(directory_exits);

    Systeem systeem;

    SuccessEnum succes = MetroReader::importXml("../src/advanced_ascii.xml",cerr,systeem);

    if (succes == Success)
    {
        ASSERT_TRUE(systeem.checkConsistent());
        //Generate output using outputclass object
        MetroOutput print(systeem.getTrams(),systeem.getStations());
        print.simple_writeover();
        bool compare = FileCompare("../output_tests/normal_scenario1_expect.txt","../output_tests/normal_scenario1_output.txt");
        EXPECT_TRUE(compare);
    }
}
// TESTING OUR ADVANCED WRITEOVER OF OUR OUTPUTCLASS
TEST_F(testOutput, check_scenario2)
{
    bool directory_exits = DirectoryExists("../output_tests");
    ASSERT_TRUE(directory_exits);

    Systeem systeem;

    SuccessEnum succes = MetroReader::importXml("../src/advanced_ascii.xml",cerr,systeem);

    if (succes == Success)
    {
        ASSERT_TRUE(systeem.checkConsistent());
        //Generate output using outputclass object
        MetroOutput print(systeem.getTrams(),systeem.getStations());
        print.advanced_writeover();
        bool compare = FileCompare("../output_tests/normal_scenario2_expect.txt","../output_tests/normal_scenario2_output.txt");
        EXPECT_TRUE(compare);
    }
}