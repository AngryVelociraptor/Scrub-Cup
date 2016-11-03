#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "ODivision.h"
#include "Team.h"
#include "role.h"
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
bool ODivision::printToFile()
{
	ofstream outf("Teams.csv");
	if (!outf)
	{
		cout << "Could not open file for writing";
			return false;
	}
	for (int i = 0; i < m_ODivision.size(); ++i)
	{
		for (j = 0; j < m_ODivision[i].m_players.size(); ++j)
		{
			outf << m_ODivision[i].m_players[j].m_name << ','
				<< m_ODivision[i].m_players[j].m_battletag << ','
				<< m_ODivision[i].m_players[j].m_email << ','
				<< roleToString(m_ODivision[i].m_players[j].m_role) << '\n';
		}
		outf << "\n\n";
	}
	return true;
}
bool ODivision::printToFile(string filename)
{
	ofstream outf(filename);
	if (!outf)
	{
		cout << "Could not open file for writing";
		return false;
	}
	for (int i = 0; i < m_ODivision.size(); ++i)
	{
		for (j = 0; j < m_ODivision[i].m_players.size(); ++j)
		{
			outf << m_ODivision[i].m_players[j].m_name << ','
				<< m_ODivision[i].m_players[j].m_battletag << ','
				<< m_ODivision[i].m_players[j].m_email << ','
				<< roleToString(m_ODivision[i].m_players[j].m_role) << '\n';
		}
		outf << "\n\n";
	}
	return true;
}