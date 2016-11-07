#pragma once
#include <string>
#include "Role.h"
class Player
{
public:
	std::string m_name;
	std::string m_battletag;
	std::string m_email;
	int m_sr;
	Role m_role;				//No bool for europe or NA, I plan to sort them as they are created.
	Role m_role2;
	bool m_sorted = false;
	bool m_sortedPoorly = false;
};
