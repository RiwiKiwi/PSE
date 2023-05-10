//
// Created by aburahman10 on 20/03/2023.
//

#ifndef VERKEERSSIMULATIE_SIMULATIONUTILS_H
#define VERKEERSSIMULATIE_SIMULATIONUTILS_H
#include "iostream"



bool DirectoryExists(const std::string dirname);

bool FileExists(const std::string dirname);

bool FileIsEmpty(const std::string filename);

bool FileCompare(const std::string& leftFileName,const std::string& rightFileName);


#endif //VERKEERSSIMULATIE_SIMULATIONUTILS_H
