#include "ODivision.h"
#include <vector>
#include "Player.h"
#include "Division.h"
#include <cmath>
#include <iostream>

int Division::findSolution(double goal, Role role)								//remember to sort
{
	int index = 0;
	double difference = 5000;													//starts out at 5000, all sr's should be closer than 5000. Therefore should never return 0.
	for (int i = 0; i < m_division.size(); ++i)									//its returning 0 a ton. I dont understand why. If you could look into that, Im done for tonight,
	{
		if (m_division[i].m_sorted == false)									//whether it is already in a team, so no dublicates
		{
			if (std::abs((m_division[i].m_sr - goal)) < difference && (m_division[i].m_role == role || m_division[i].m_role == ROLE_ANY))
			{																	//if the distance beween the that sr and the target is less than the best one found so far, this new one replaces the old one.
				difference = std::abs((m_division[i].m_sr - goal));				//Must have correct role or "any" role.
				index = i;
			}
		}
	}
	double difference2 = 5000;
	if (std::abs(m_division[index].m_sr - goal > 200))							//if the sr found isnt very close, this should check to see if there is a closer one with the role searched for being their second choice.
	{
		int index2 = 0;
		for (int i = 0; i < m_division.size(); ++i)								
		{
			if (m_division[i].m_sorted == false)
			{
				if (std::abs((m_division[i].m_sr - goal)) < difference2 && (m_division[i].m_role2 == role || m_division[i].m_role2 == ROLE_ANY) && m_division[i].m_sorted == false)
				{
					difference2 = std::abs((m_division[i].m_sr - goal));
					index2 = i;
				}
			}
		}
		if (std::abs(m_division[index].m_sr - goal) < std::abs(m_division[index2].m_sr - goal))
		{
			index = index2;
		}
	}
	m_division[index].m_role = role;
	m_division[index].m_sorted = true;
	return index;
}

ODivision Division::teamSort(int seed)
{
	double goal = getAverageSR();
	ODivision teams;
	teams.name = m_name;
	int teamCount = (m_division.size() / 6);									// Teams of six, therfore players divided by 6 is number of teams.
	if (!(m_division.size() % 6))
		teamCount++;
	teams.m_ODivision.resize(teamCount);
	for (int i = 0; i < teams.m_ODivision.size(); ++i)
	{
		do
			{
				if (m_division[seed].m_sorted)
					seed++;
				else
				{
					switch (m_division[seed].m_role)
					{
					case ROLE_ANY:
						if (seed == m_division.size()-1)
						{
							seed = 0;
							break;
						}
						else
						{
							seed++;
							break;
						}

					case ROLE_DPS:
						++teams.m_ODivision[i].m_countDPS;
						break;
					case ROLE_TANK:
						++teams.m_ODivision[i].m_countTanks;
						break;
					case ROLE_SUPPORT:
						++teams.m_ODivision[i].m_countSupport;
						break;
					}
				}
			} while (m_division[seed].m_role == ROLE_ANY);
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
				Player result = m_division[findSolution((getAverageSR()*(j + 1))-((teams.m_ODivision[i].getAverage())*(j)), ROLE_DPS)];
				teams.m_ODivision[i].m_players[j] = result;
				++teams.m_ODivision[i].m_countDPS;
			}
			else if ((teams.m_ODivision[i].m_countTanks < 2))
			{
				Player result = m_division[findSolution((getAverageSR()*(j + 1)) - ((teams.m_ODivision[i].getAverage())*(j)), ROLE_TANK)];
				teams.m_ODivision[i].m_players[j] = result;
				++teams.m_ODivision[i].m_countDPS;
			}
			else if ((teams.m_ODivision[i].m_countSupport < 2))
			{
				Player result = m_division[findSolution((getAverageSR()*(j + 1)) - ((teams.m_ODivision[i].getAverage())*(j)), ROLE_TANK)];
				teams.m_ODivision[i].m_players[j] = result;
				++teams.m_ODivision[i].m_countDPS;
			}		
		}
		std::cout << "Finished sorting team number " << i + 1 << ". " << teams.m_ODivision.size()-i-1 << " more teams to go.\n";
	}
	return teams;
}
