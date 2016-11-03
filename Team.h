#pragma once
#include <vector>
#include "Player.h"
#include <string>
class Team
{
public:
	std::vector<Player> m_players = { 0, 0, 0, 0, 0, 0 };
	std::string m_name;
};