#pragma once
#include <vector>
#include "Player.h"
#include <string>
class Team
{
public:
	std::vector<Player> m_players;
	std::string m_name;
	int m_countTanks = 0;
	int m_countDPS = 0;
	int m_countSupport = 0;
	Team()
	{
		m_players.resize(5);
	}
	double getAverage();
};
