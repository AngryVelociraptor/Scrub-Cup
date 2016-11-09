#pragma once
//organized division, into teams.
#include "Team.h"
#include <vector>
#include <string>

class ODivision
{
public:
	std::string name;
	std::vector<Team> m_ODivision;
	double getStandardDeviation();
	double getFirstChoicePCent();
	double getSecondChoicePcent();
	double getPoorlySortedPcent();
};
