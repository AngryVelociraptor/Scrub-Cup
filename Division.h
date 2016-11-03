#pragma once
#include <vector>
#include "Player.h"
#include <string>
#include "role.h"
#include "ODivision.h"
class Division
{
public:
	std::string m_name;
	std::vector<Player> m_division;


	int getSR(int index);
	int countRole(Role role);
	void tallyRoles();
	std::string getName(int index);
	std::string getBattletag(int index);
	Role getRole(int index);
	double getAverageSR();
	ODivision teamSort(int seed);											//Sorts the players into teams. "seed" is the index of the value that the algorithm starts on. Seed MUST START ON A PLAYER WHO DID NOT CHOOSE ANY AS THIER FIRST ROLE PICK
	//all search functions return -1 if nothing is found, as well as printing a message
	int search(int sr);														//searches for a player with that sr
	std::vector<int> searchAll(int sr);										//searches for all players with that sr
	int search(int sr, std::vector<int> exeptions);							//searches for a player with "sr" sr. Ignores any players with their index in the "exeptions"
	int search(std::string name);											//searches for a player with that name. Works with battletags as well
	int search(std::string name, std::vector<int> exeptions);				//searches for a player with that name. Works with battletags as well. with exeptions.
	int search(int lower, int upper);										//searches for a player between those bounds. Can be equal to those bounds.
	int search(int lower, int upper, Role role);							//searches for a player with x role that >= lower and <= upper
	std::vector<int> searchAll(int lower, int upper, Role role);			//searches for all players with x role that >= lower and <= upper
	int findSolution(double goal, Role role);
};


//to add: searchAll functions with exeptions
