#include "game.hpp"
#include "savemanager.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
    City citta;

    srand((unsigned int)time(NULL));

    // NOTE: This uses the cmake output folder for the save file, so if you don't find the file, keep that in mind.

    if (!loadCity("citta.txt", citta)) {
        cerr << "Impossibile caricare la citta. Generando una nuova citta." << endl;
        citta = createNewCity();
    }

    cout << "Città: " << citta.name << endl;
    cout << "Popolazione: " << citta.population << endl;
    cout << "Budget: " << citta.budget << endl;
    cout << "Data: " << citta.time.week << " settimana del mese " << citta.time.month << " dell'anno " << citta.time.year << endl;

    if (!saveCity("citta.txt", citta)) {
        cerr << "Impossibile salvare la citta" << endl;
        return 1;
    }

    return 0;
}
