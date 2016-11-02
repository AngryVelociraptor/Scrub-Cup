// Scrub Cup Work.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
/*
This program uses a .csv file. 
First column must be names, 
second must be battletags, 
third must be email addresses, 
fourth must be continent,
fifth must be SR,
sixth must be role.
THE MUST BE NO DATA FURTHER DOWN THAN THE PLAYERS
*/
using namespace std;
enum Role
{
	ROLE_DPS,
	ROLE_TANK,
	ROLE_SUPPORT,
	ROLE_ANY
};
class Player
{
public:
	string m_name;
	string m_battletag;
	string m_email;
	int m_sr;
	Role m_role;				//No bool for europe or NA, I plan to sort them as they are created.
};
void parse(vector<Player> &europe, vector<Player> &NA, int count, ifstream& file) //Count is the number of players to process. Path is the path to the .csv file
{
	europe.resize(count);
	NA.resize(count);
	int europeCounter = 0;
	int NACounter = 0;
	string name; 
	string battletag;
	string email;
	string srString;
	int sr;
	string roleString;
	Role role;
	string region;
	
	for (int i = 1; i <= count; ++i)
	{
		getline(file, name, ',');
		getline(file, battletag, ',');
		getline(file, email, ',');
		getline(file, region, ',');
		getline(file, srString, ',');
		sr = atoi(srString.c_str());
		getline(file, roleString);
		if (roleString == "DPS")
			role = ROLE_DPS;
		else if (roleString == "Tank")
			role = ROLE_TANK;
		else if (roleString == "Support")
			role = ROLE_SUPPORT;
		else if (roleString == "any")
			role = ROLE_ANY;
		else
			cout << "Something was wrong with the role choice of player number " << i << ". \n";
		if (region == "Europe")
		{							//Assigns the data to a Player with the index i in the correct vector.
			europe.at(europeCounter).m_name = name;
			europe.at(europeCounter).m_battletag = battletag;
			europe.at(europeCounter).m_email = email;
			europe.at(europeCounter).m_sr = sr;
			europe.at(europeCounter).m_role = role;
			europeCounter++;
		}
		else if (region == "Americas")
		{

			NA.at(NACounter).m_name = name;
			NA.at(NACounter).m_battletag = battletag;
			NA.at(NACounter).m_email = email;
			NA.at(NACounter).m_sr = sr;
			NA.at(NACounter).m_role = role;
			NACounter++;
		}
	}
	NA.resize(NACounter + 1);
	
	europe.resize(europeCounter + 1);
	
}
double findAverageSR(vector<Player> division)
{
	double total = 0;
	for (int i = 0; i < division.size(); i++)
	{
		total += division[i].m_sr;
	}
	return total / division.size();
}
int countRole(vector<Player> division, Role role)
{
	int count = 0;
	for (int i = 0; i < division.size(); i++)
	{
		if (division[i].m_role == role)
			count++;
	}
	return count;
}
int main()
{
	vector<Player> europe;
	vector<Player> NA;
	int count = 307;
	ifstream file("Players.csv");
	if (!file)
	{
		cout << "There was a problem opening the file. \n";
	}
	parse(europe, NA, count, file);
	cout << "There are " << NA.size() << " Players in NA.\n";
	cout << "The average SR of NA is " << findAverageSR(NA) << ".\n";
	cout << "There are " << europe.size() << " Players in Europe.\n";
	cout << "The average SR of Europe is " << findAverageSR(europe) << ".\n";
	cout << "There are " << countRole(NA, ROLE_DPS) << " DPS players on NA\n";
	cout << "There are " << countRole(NA, ROLE_TANK) << " Tank players on NA\n";
	cout << "There are " << countRole(NA, ROLE_SUPPORT) << " Support players on NA\n";
	cout << "There are " << countRole(NA, ROLE_ANY) << " Any players on NA\n";
	cout << "There are " << countRole(europe, ROLE_DPS) << " DPS players on Europe\n";
	cout << "There are " << countRole(europe, ROLE_TANK) << " Tank players on Europe\n";
	cout << "There are " << countRole(europe, ROLE_SUPPORT) << " Support players on Europe\n";
	cout << "There are " << countRole(europe, ROLE_ANY) << " Any players on Europe\n";
    return 0;
}

