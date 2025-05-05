#include "includes/game.hpp"
#include "includes/menus.hpp"
#include "includes/utils.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
    srand((unsigned int)time(NULL));

    City citta;

    if (!saveMenu(citta)) {
        return 0;
    }

    cout << endl;
    stampaInfoCitta(citta);

    gameMenu(citta);

    return 0;
}
