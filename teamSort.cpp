#include "ODivision.h"
#include <vector>
#include "Player.h"
#include "Division.h"

int Division::findSolution(double goal, Role role)								//remember to sort
{
	int index = 0;
	double difference = 5000;
	for (int i = 0; i < m_division.size(); ++i)
	{
		if ((m_division[i].m_sr - goal) < difference && m_division[i].m_role == role && m_division[i].m_sorted == false)
			index = i;
	}
	m_division[index].m_sorted = true;
	return index;
}

ODivision Division::teamSort(int seed)
{
	double goal = getAverageSR();
	ODivision teams;
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
			} while (m_division[seed].m_role);
			teams.m_ODivision[i].m_players[j] = m_division[seed];
			m_division[seed].m_sorted = true;
			if (seed == m_division.size() - 1)
				seed = 0;
			else
				++seed;
		for (int j = 1; j < teams.m_ODivision[i].m_players.size(); ++j)
		{
			if (teams.m_ODivision[i].m_countDPS < 2)
				teams.m_ODivision[i].m_players[j] = m_division[findSolution(0(getAverageSR()*(j+1))-((teams.m_ODivision[i].getAverage)*(j+1)), ROLE_DPS)];
		}
	}
}
