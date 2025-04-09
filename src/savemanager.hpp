#pragma once

#include "game.hpp"
#include <fstream>

bool saveCity(const string &path, City city);
bool loadCity(const string &path, City &city);
