#pragma once

#include "game.hpp"

bool saveMenu(City &citta);
bool creaCitta(int cittaSalvate, City &citta, int &retFlag);
void ordinaCitta(int cittaSalvate, City cities[9], int &retFlag);
void cancellaCitta(int &cittaSalvate, City cities[9], int &retFlag);
void gameMenu(City &citta);
