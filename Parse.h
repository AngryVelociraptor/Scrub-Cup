#pragma once
/*
This program uses a .csv file.
First column must be names,
second must be battletags,
third must be email addresses,
fourth must be continent,
fifth must be SR,
sixth must be role.
THE MUST BE NO DATA FURTHER DOWN THAN THE PLAYERS
*/
#include <vector>
#include "player.h"
#include "Division.h"
#include <string>
void parse(Division &europe, Division &NA, int count, std::string file);