#pragma once
#include "ODivision.h"
#include "Division.h"
#include <string>
bool printToFile(ODivision oDivision);
bool printToFile(Division, std::string);
bool printToFile(ODivision oDivision, std::string filename);
bool printToFile(ODivision oDivision, std::string filename, Division division);
