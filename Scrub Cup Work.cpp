#include <string>											//Remember, prepare for the "not found" error when searching, it returns -1.
#include <vector>
#include <fstream>
#include <iostream>
#include "Parse.h"
#include "Division.h"
using namespace std;

const string fileName = "Players.csv";					//This is where you put the name of the .csv file you want read.
															//I tried to make it take it as a command line input, but that was too hard
int main()													//instructions for how the file must be formatted are in parse.h and parse.cpp
{
	Division europe;
	Division NA;
	int count = 307;											//the exact number or players in the .csv file.
	parse(europe, NA, count, fileName);
	NA.tallyRoles();
	cout << NA.getName(NA.search(2100, 2200, ROLE_ANY)) << '\n';
    return 0;
}

