#include "Odivision.h"
#include <fstream>
#include <iostream>
#include "Division.h"
#include <vector>
#include <string>
using namespace std;
string roleToString(Role role)
{
	switch (role)
	{
	case ROLE_DPS:
		return "DPS";
	case ROLE_TANK:
		return "Tank";
	case ROLE_SUPPORT:
		return "Support";
	case ROLE_ANY:
		return "Any";
	}
}
bool printToFile(ODivision oDivision)
{
	ofstream outf("Teams.csv");
	if (!outf)
	{
		cout << "Could not open file for writing";
		return false;
	}
	for (int i = 0; i < oDivision.m_ODivision.size(); ++i)
	{
		for (int j = 0; j < oDivision.m_ODivision[i].m_players.size(); ++j)
		{
			outf << oDivision.m_ODivision[i].m_players[j].m_name << ','
				<< oDivision.m_ODivision[i].m_players[j].m_battletag << ','
				<< oDivision.m_ODivision[i].m_players[j].m_email << ','
				<< roleToString(oDivision.m_ODivision[i].m_players[j].m_role) << '\n';
		}
		outf << "\n\n";
	}
	return true;
}
bool printToFile(ODivision oDivision, std::string filename)
{
	ofstream outf(filename);
	if (!outf)
	{
		cout << "Could not open file for writing";
		return false;
	}
	for (int i = 0; i < oDivision.m_ODivision.size(); ++i)
	{
		for (int j = 0; j < oDivision.m_ODivision[i].m_players.size(); ++j)
		{
			outf << oDivision.m_ODivision[i].m_players[j].m_name << ','
				<< oDivision.m_ODivision[i].m_players[j].m_battletag << ','
				<< oDivision.m_ODivision[i].m_players[j].m_email << ','
				<< roleToString(oDivision.m_ODivision[i].m_players[j].m_role) << '\n';
		}
		outf << "\n\n";
	}
	return true;
}
bool printToFile(ODivision oDivision, std::string filename, Division division)
{
	ofstream outf(filename);
	if (!outf)
	{
		cout << "Could not open file for writing";
		return false;
	}
	for (int i = 0; i < oDivision.m_ODivision.size(); ++i)
	{
		outf << "Team #" << i << '\n';
		for (int j = 0; j < oDivision.m_ODivision[i].m_players.size(); ++j)
		{
			outf << oDivision.m_ODivision[i].m_players[j].m_name << ','
				<< oDivision.m_ODivision[i].m_players[j].m_battletag << ','
				<< oDivision.m_ODivision[i].m_players[j].m_email << ','
				<< roleToString(oDivision.m_ODivision[i].m_players[j].m_role) << '\n';
		}
		outf << "\n\n";
	}
	outf << "Unsorted players:\n";
	for (int i = 0; i < division.m_division.size(); ++i)
	{
		if (!division.m_division[i].m_sorted)
		{
			outf << division.m_division[i].m_name << ','
				<< division.m_division[i].m_battletag << ','
				<< division.m_division[i].m_email << ','
				<< roleToString(division.m_division[i].m_role) << '\n';
		}
	}
	return true;
}
