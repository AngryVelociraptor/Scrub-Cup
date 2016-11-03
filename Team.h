#pragma once
#include <vector>
#include "Player.h"
#include <string>
class Team
{
public:
	std::vector<Player> m_players;
	std::string m_name;
	Team()
	{
		m_players.resize(5);
	}
};