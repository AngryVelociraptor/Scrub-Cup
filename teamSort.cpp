#include "ODivision.h"
#include <vector>
#include "Player.h"
#include "Division.h"
#include <cmath>
#include <iostream>

int Division::findSolution(double goal, Role role)								//remember to sort
{
	int index = 1;
	int indexAny = 1;
	double difference = 5000;													//starts out at 5000, all sr's should be closer than 5000. Therefore should never return 0.
	double differenceAny = 5000;
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
			else if (std::abs((m_division[i].m_sr - goal)) < differenceAny && (m_division[i].m_role == ROLE_ANY))
			{
				differenceAny = std::abs((m_division[i].m_sr - goal));
				foundSolution = true;
				indexAny = i;
			}
		}
	}
	if (differenceAny < difference)
	{
		if (difference - differenceAny > 1500)
		{
			index = indexAny;
			difference = differenceAny;
		}
	}
	double difference2 = 5000;
	double difference2Any = 5000;
	if (std::abs(m_division[index].m_sr - goal > 200))							//if the sr found isnt very close, this should check to see if there is a closer one with the role searched for being their second choice.
	{
		int index2 = 0;
		int index2Any = 0;
		for (int i = 0; i < m_division.size(); ++i)								
		{
			if (m_division[i].m_sorted == false)
			{
				if (std::abs((m_division[i].m_sr - goal)) < difference2 && (m_division[i].m_role2 == role))
				{
					difference2 = std::abs((m_division[i].m_sr - goal));
					foundSolution = true;
					index2 = i;
				}
				else if (std::abs((m_division[i].m_sr - goal)) < difference2Any && (m_division[i].m_role == ROLE_ANY))
				{
					difference2Any = std::abs((m_division[i].m_sr - goal));
					foundSolution = true;
					index2Any = i;
				}
			}
		}
		if (differenceAny < difference)
		{
			if (difference - differenceAny > 1000)
			{
				index2 = index2Any;
				difference2 = difference2Any;
			}
		}
		if (std::abs(m_division[index].m_sr - goal) < std::abs(m_division[index2].m_sr - goal))
		{
			index = index2;
		}
	}
	if (foundSolution == false)
	{
		for (int i = 0; i < m_division.size(); ++i)
		{
			if (m_division[i].m_sorted == false)
			{
				if (std::abs((m_division[i].m_sr - goal)) < difference)
				{
					difference = std::abs((m_division[i].m_sr - goal));
					index = i;
					m_division[i].m_sortedPoorly = true;
				}
			}
		}
	}
	m_division[index].m_sorted = true;
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
	for (int i = 0; i < teams.m_ODivision.size(); ++i)
	{
		do
			{
				if (m_division[seed].m_sorted == true)							//wouldnt check to see if sorted if first was sorted and second was
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
				++teams.m_ODivision[i].m_countTanks;
			}
			else if ((teams.m_ODivision[i].m_countSupport < 2))
			{
				Player result = m_division[findSolution((getAverageSR()*(j + 1)) - ((teams.m_ODivision[i].getAverage())*(j)), ROLE_SUPPORT)];
				teams.m_ODivision[i].m_players[j] = result;
				++teams.m_ODivision[i].m_countSupport;
			}		
		}
		std::cout << "Finished sorting team number " << i + 1 << ". " << teams.m_ODivision.size()-i-1 << " more teams to go.\n";
	}
	return teams;
}
