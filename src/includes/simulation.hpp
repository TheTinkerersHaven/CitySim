#pragma once

#include "game.hpp"

#define SIM_OK 0
#define SIM_FINE_POP -1

int simulate(City &city);
void addWeek(Time &time);
