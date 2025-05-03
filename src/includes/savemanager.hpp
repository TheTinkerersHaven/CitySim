#pragma once

#include "game.hpp"
#include <fstream>

#define MAX_SAVES 9

bool saveCity(City city);
bool loadCity(const string &path, City &city);

City createNewCity();

int findSaves(City saves[], int capacity);
