#include "ODivision.h"
#include <vector>
#include "Player.h"
#include "Division.h"
#include <cmath>
#include <iostream>
class Index
{
public:
	int m_team;
	int m_player;
	Role m_role;
	bool m_sorted = false;
	Index(int team, int player, Role role)
	{
		m_team = team;
		m_player = player;
		m_role = role;
	}
};
int Division::findSolution(double goal, Role role)								//remember to sort
{
	int index = 1;
	double difference = 5000;													//starts out at 5000, all sr's should be closer than 5000. Therefore should never return 0.
	bool foundSolution = false;
	for (int i = 0; i < m_division.size(); ++i)									//its returning 0 a ton. I dont understand why. If you could look into that, Im done for tonight,
	{
		if (m_division[i].m_sorted == false)									//whether it is already in a team, so no dublicates
		{
			if (std::abs((m_division[i].m_sr - goal)) < difference && (m_division[i].m_role == role))
			{																	
				difference = std::abs((m_division[i].m_sr - goal));	
				foundSolution = true;
				index = i;
			}
		}
	}
	if (foundSolution == false)
	{
		return -1;
	}
	m_division[index].m_sorted = true;
	m_division[index].m_roleSorted = role;
	return index;
}

ODivision Division::teamSort(int seed)
{
	double goal = getAverageSR();
	ODivision teams;
	teams.name = m_name;
	int teamCount = (m_division.size() / 6);									// Teams of six, therfore players divided by 6 is number of teams.
	if ((m_division.size() % 6) > 0)
		teamCount++;
	teams.m_ODivision.resize(teamCount);
	std::vector<Index> fails;
	for (int i = 0; i < teams.m_ODivision.size(); ++i)
	{
		int newSeed = seed;
		do
		{
			seed = newSeed;
			if (m_division[seed].m_sorted == true)							//wouldnt check to see if sorted if first was sorted and second was
				newSeed = seed + 1;
			else
			{
				switch (m_division[seed].m_role)
				{
				case ROLE_ANY:
					if (seed == m_division.size()-1)
					{
						newSeed = 0;
						break;
					}
					else
					{
						newSeed = seed + 1;
						break;
					}

				case ROLE_DPS:
						++teams.m_ODivision[i].m_countDPS;
						m_division[seed].m_roleSorted = m_division[seed].m_role;
						break;
				case ROLE_TANK:
						++teams.m_ODivision[i].m_countTanks;
						m_division[seed].m_roleSorted = m_division[seed].m_role;
						break;
				case ROLE_SUPPORT:
					++teams.m_ODivision[i].m_countSupport;
					m_division[seed].m_roleSorted = m_division[seed].m_role;
					break;
				}
			}
		} while (m_division[seed].m_role == ROLE_ANY || m_division[seed].m_sorted == true);
		teams.m_ODivision[i].m_players[0] = m_division[seed];
		m_division[seed].m_sorted = true;
		if (seed == m_division.size() - 1)
			seed = 0;
		else
			++seed;
		for (int j = 1; j < teams.m_ODivision[i].m_players.size(); ++j)
		{
			if (teams.m_ODivision[i].m_countDPS < 2)
			{
				int index = findSolution((getAverageSR()*(j + 1)) - ((teams.m_ODivision[i].getAverage())*(j)), ROLE_DPS);
				if (index == -1)
				{
					fails.push_back(Index(i, j, ROLE_DPS));
				}
				else
				{
					Player result = m_division[index];
					teams.m_ODivision[i].m_players[j] = result;
				}
				teams.m_ODivision[i].m_players[j].m_roleSorted = ROLE_DPS;
				++teams.m_ODivision[i].m_countDPS;
			}
			else if ((teams.m_ODivision[i].m_countTanks < 2))
			{
				int index = findSolution((getAverageSR()*(j + 1)) - ((teams.m_ODivision[i].getAverage())*(j)), ROLE_TANK);
				if (index == -1)
				{
					fails.push_back(Index(i, j, ROLE_TANK));
				}
				else
				{
					Player result = m_division[index];
					teams.m_ODivision[i].m_players[j] = result;
				}
				teams.m_ODivision[i].m_players[j].m_roleSorted = ROLE_TANK;
				++teams.m_ODivision[i].m_countTanks;
			}
			else if ((teams.m_ODivision[i].m_countSupport < 2))
			{
				int index = findSolution((getAverageSR()*(j + 1)) - ((teams.m_ODivision[i].getAverage())*(j)), ROLE_SUPPORT);
				if (index == -1)
				{
					fails.push_back(Index(i, j, ROLE_SUPPORT));
				}
				else
				{
					Player result = m_division[index];
					teams.m_ODivision[i].m_players[j] = result;
				}
				teams.m_ODivision[i].m_players[j].m_roleSorted = ROLE_SUPPORT;
				++teams.m_ODivision[i].m_countSupport;
			}		
		}
	}
	for (int i = 0; i < fails.size(); ++i)
	{
		if (fails[i].m_sorted == false)
		{
			double difference = 5000;
			int index = 0;
			bool foundSolution = false;
			for (int k = 0; k < m_division.size(); ++k)
			{
				if (m_division[k].m_sorted == false)
				{
					if (std::abs((m_division[k].m_sr - goal)) < difference && (m_division[k].m_role2 == fails[i].m_role))
					{
						difference = std::abs((m_division[k].m_sr - goal));
						foundSolution = true;
						index = k;
					}
				}
			}
			if (foundSolution)
			{
				m_division[index].m_sorted = true;
				m_division[index].m_roleSorted = fails[i].m_role;
				teams.m_ODivision[fails[i].m_team].m_players[fails[i].m_player] = m_division[index];
				fails[i].m_sorted = true;
			}
		}
	}
	for (int i = 0; i < fails.size(); ++i)
	{
		if (fails[i].m_sorted == false)
		{
			double difference = 5000;
			int index = 0;
			bool foundSolution = false;
			for (int k = 0; k < m_division.size(); ++k)
			{
				if (m_division[k].m_sorted == false)
				{
					if (std::abs((m_division[k].m_sr - goal)) < difference && ((m_division[k].m_role == ROLE_ANY) || (m_division[k].m_role2 == ROLE_ANY)))
					{
						difference = std::abs((m_division[k].m_sr - goal));
						foundSolution = true;
						index = k;
					}
				}
			}
			if (foundSolution)
			{
				m_division[index].m_sorted = true;
				m_division[index].m_roleSorted = fails[i].m_role;
				teams.m_ODivision[fails[i].m_team].m_players[fails[i].m_player] = m_division[index];
				fails[i].m_sorted = true;
			}
		}
	}
	std::cout << m_name << " Division has been sorted.\n";
	return teams;
}
