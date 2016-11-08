#pragma once
#include <string>
#include "Role.h"
class Player
{
public:
	std::string m_name = "0";
	std::string m_battletag = "0";
	std::string m_email = "0";
	int m_sr = 0;
	Role m_role = ROLE_ANY;				//No bool for europe or NA, I plan to sort them as they are created.
	Role m_role2 = ROLE_ANY;
	Role m_roleSorted = ROLE_ANY;
	bool m_sorted = false;
	bool m_sortedPoorly = false;
};
