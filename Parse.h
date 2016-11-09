#pragma once
/*
This program uses a .csv file.
One row per person
First column must be names,
second must be battletags,
third must be email addresses,
fourth must be the division,
fifth must be SR.
sixth must be role.
seventh must be the second choice of role.
for both roles, "I am ok with any role" must be changed to "any" (case sensitive)
THE MUST BE NO DATA FURTHER DOWN THAN THE PLAYERS
*/
#include <vector>
#include "Player.h"
#include "Division.h"
#include <string>
void parse(Division &europe, Division &NA, int count, std::string file);
