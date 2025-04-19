#pragma once

#include "game.hpp"

#define SIM_OK 0
#define SIM_FINE_BUDGET -1
#define SIM_FINE_POP -2

int simulate(City &city);
void addWeek(Time &time);
