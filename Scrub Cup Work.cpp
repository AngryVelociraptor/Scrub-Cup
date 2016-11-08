#include <string>											//Remember, prepare for the "not found" error when searching, it returns -1.
#include <vector>
#include <fstream>
#include <iostream>
#include "Parse.h"
#include "Division.h"
#include "ODivision.h"
#include "PrintToFile.h"
using namespace std;


const string fileName = "Players.csv";						//This is where you put the name of the .csv file you want read.
															//I tried to make it take it as a command line input, but that was too hard
int main()													//instructions for how the file must be formatted are in parse.h and parse.cpp
{
	Division europe("Europe");
	Division NA("North America");
	int count = 465;										//the exact number or players in the .csv file.
	parse(europe, NA, count, fileName);
	printToFile(europe, "EUPlayers.csv");
	printToFile(NA, "NAPlayers.csv");
	NA.tallyRoles();
	europe.tallyRoles();
	ODivision sortedEurope = europe.teamSort(0);
	ODivision sortedNA = NA.teamSort(0);
	cout << "The average sr for NA is "<< NA.getAverageSR() << '\n';
	cout << "The average sr for Europe is " << europe.getAverageSR() << '\n';
	printToFile(sortedNA, "NA Teams.csv", NA);
	printToFile(sortedEurope, "Europe Teams.csv", europe);
	std::cin.clear(); // reset any error flags
	std::cin.ignore(32767, '\n'); // ignore any characters in the input buffer until we find an enter character
	std::cin.get(); // get one more char from the user
    return 0;
}

