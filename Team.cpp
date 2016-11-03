#include "Team.h"
#include <vector>

double Team::getAverage()
{
    double total = 0;
    int count = 0;
    for (int i = 0; i < m_players.size; ++i)
    {
        if (m_players[i])
        {
            total += m_players[i].m_sr;
            count++;
        }
    }
    if (!count)
        count = 1;
    return total/count;
}  
