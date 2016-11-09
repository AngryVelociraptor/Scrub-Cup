#include <vector>
#include <iostream>
#include "Player.h"
#include <string>
#include "Role.h"
#include "Division.h"
using namespace std;
Division::Division(string name)
{
	m_name = name;
}
double Division::getAverageSR()
{
	double total = 0;
	for (int i = 0; i < m_division.size(); i++)
	{
		total += m_division[i].m_sr;
	}
	return total / m_division.size();
}
int Division::getSR(int index)
{
	return m_division[index].m_sr;
}
std::string Division::getName(int index)
{
	return m_division[index].m_name;
}
std::string Division::getBattletag(int index)
{
	return m_division[index].m_battletag;
}
Role Division::getRole(int index)
{
	return m_division[index].m_role;
}
int Division::search(int sr)
{
	for (int i = 0; i < m_division.size(); ++i)
	{
		if (m_division[i].m_sr == sr)
			return i;
	}
	cout << "None found with that SR.\n";
	return -1;
}

vector<int> Division::searchAll(int sr)										//searches for all players with that sr
{
	vector<int> solutions;
	int count = 0;
	solutions.resize(count);
	for (int i = 0; i < m_division.size(); ++i)
	{
		if (m_division[i].m_sr == sr)
		{
			count++;
			solutions.resize(count);
			solutions[count - 1] = i;
		}
	}
	if (solutions.size() == 0)
	{
		cout << "None found with that SR.\n";
		solutions.resize(1);
		solutions[0] = -1;
	}

	return solutions;
}
bool isIncluded(vector<int> list, int check)
{
	for (int i = 0; i < list.size(); ++i)
	{
		if (check == list[i])
			return true;
	}
	return false;
}
int Division::search(int sr, vector<int> exeptions)						//searches for a player with "sr" sr. Ignores any players with their index in the "exeptions"
{
	for (int i = 0; i < m_division.size(); ++i)
	{
		if (m_division[i].m_sr == sr && !isIncluded(exeptions, i))
			return i;
	}
	cout << "None found with that SR that was not in the exeptions.\n";
	return -1;
}
int Division::search(string name)										//searches for a player with that name
{
	for (int i = 0; i < m_division.size(); ++i)
	{
		if (m_division[i].m_name == name || m_division[i].m_battletag == name)
			return i;
	}
	cout << "None found with that SR.\n";
	return -1;
}
int Division::search(string name, vector<int> exeptions)				//same as above, with exeptions
{
	for (int i = 0; i < m_division.size(); ++i)
	{
		if ((m_division[i].m_name == name || m_division[i].m_battletag == name) && !isIncluded(exeptions, i))
			return i;
	}
	cout << "None found with that name or battletag that was not in the exeptions.\n";
	return -1;
}
int Division::search(int lower, int upper)								//searches for a player that is >= lower and <= upper
{
	for (int i = 0; i < m_division.size(); ++i)
	{
		if (m_division[i].m_sr <= upper && m_division[i].m_sr >= lower)
			return i;
	}
	cout << "None found within that range.\n";
	return -1;
}
int Division::search(int lower, int upper, Role role)
{
	for (int i = 0; i < m_division.size(); ++i)
	{
		if ((m_division[i].m_sr <= upper && m_division[i].m_sr >= lower) && m_division[i].m_role == role)
		{
			return i;
		}
	}
	cout << "None found within that range and with that role\n";
	return -1;
}
vector<int> Division::searchAll(int lower, int upper, Role role)		//same as above, but all players.
{
	vector<int> solutions;
	int count = 0;
	solutions.resize(count);
	for (int i = 0; i < m_division.size(); ++i)
	{
		if (m_division[i].m_sr <= upper && m_division[i].m_sr >= lower && m_division[i].m_role == role)
		{
			count++;
			solutions.resize(count);
			solutions[count - 1] = i;
		}
	}
	if (solutions.size() == 0)
	{
		cout << "None found within that range and with that role.\n";
		solutions.resize(1);
		solutions[0] = -1;
	}

	return solutions;
}
int Division::countRole(Role role)
{
	int count = 0;
	for (int i = 0; i < m_division.size(); i++)
	{
		if (m_division[i].m_role == role)
			count++;
	}
	switch (role)
	{
	case ROLE_DPS:
		cout << "There are " << count << " DPS players on " << m_name << "\n";
		break;
	case ROLE_TANK:
		cout << "There are " << count << " Tank players on " << m_name << "\n";
		break;
	case ROLE_SUPPORT:
		cout << "There are " << count << " Support players on " << m_name << "\n";
		break;
	case ROLE_ANY:
		cout << "There are " << count << " Any players on " << m_name << "\n";
		break;
	}
	return count;
}
void Division::tallyRoles()
{
	countRole(ROLE_DPS);
	countRole(ROLE_TANK);
	countRole(ROLE_SUPPORT);
	countRole(ROLE_ANY);
}
