#include "Odivision.h"
#include <vector>
#include <cmath>

double ODivision::getStandardDeviation()
{
	double sum = 0;
	double mean; 
	double standardDeviation = 0;
	for (int i = 0; i < m_ODivision.size(); ++i)
	{
		sum += m_ODivision[i].getAverage();
	}
	mean = sum / m_ODivision.size();
	for (int i = 0; i < m_ODivision.size(); ++i)
	{
		standardDeviation += std::pow(m_ODivision[i].getAverage() - mean, 2);
	}
	return std::sqrt(standardDeviation / m_ODivision.size());
}

double ODivision::getFirstChoicePCent()
{
	double totalCorrect = 0;
	double total = 0;
	for (int i = 0; i < m_ODivision.size(); ++i)
	{
		for (int j = 0; j < m_ODivision[i].m_players.size(); ++j)
		{
			if ((m_ODivision[i].m_players[j].m_roleSorted == m_ODivision[i].m_players[j].m_role) || (m_ODivision[i].m_players[j].m_role == ROLE_ANY))
				++totalCorrect;
			++total;
		}
	}
	return  (totalCorrect / total) * 100;
}

double ODivision::getSecondChoicePcent()
{
	double totalCorrect = 0;
	double total = 0;
	for (int i = 0; i < m_ODivision.size(); ++i)
	{
		for (int j = 0; j < m_ODivision[i].m_players.size(); ++j)
		{
			if (((m_ODivision[i].m_players[j].m_roleSorted == m_ODivision[i].m_players[j].m_role2) || (m_ODivision[i].m_players[j].m_role2 == ROLE_ANY))
				&& (m_ODivision[i].m_players[j].m_role2 != m_ODivision[i].m_players[j].m_role) && m_ODivision[i].m_players[j].m_role == ROLE_ANY)
				++totalCorrect;
			++total;
		}
	}
	return  (totalCorrect / total) * 100;
}
double ODivision::getPoorlySortedPcent()
{
	int totalWrong = 0;
	double total = 0;
	for (int i = 0; i < m_ODivision.size(); ++i)
	{
		for (int j = 0; j < m_ODivision[i].m_players.size(); ++j)
		{
			if ((m_ODivision[i].m_players[j].m_roleSorted != m_ODivision[i].m_players[j].m_role2) 
				&& (m_ODivision[i].m_players[j].m_role2 != ROLE_ANY) 
				&& m_ODivision[i].m_players[j].m_roleSorted != m_ODivision[i].m_players[j].m_role 
				&& (m_ODivision[i].m_players[j].m_role != ROLE_ANY))
				++totalWrong;
			++total;
		}
	}
	return  (totalWrong / total) * 100;
}