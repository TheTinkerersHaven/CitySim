#include "game.hpp"
#include "savemanager.hpp"
#include <iostream>

using namespace std;

int main() {
    City citta;

    // NOTE: This uses the cmake output folder for the save file, so if you don't find the file, keep that in mind.
    // Sample data for testing:
    /*
        Roma
        2873000
        1000000
        2023
    */

    if (!loadCity("citta.txt", citta)) {
        cerr << "Impossibile caricare la citta" << endl;
        return 1;
    }

    cout << "Città: " << citta.nome << endl;
    cout << "Popolazione: " << citta.popolazione << endl;
    cout << "Budget: " << citta.buget << endl;
    cout << "Data: " << citta.data << endl;

    if (!saveCity("citta.txt", citta)) {
        cerr << "Impossibile salvare la citta" << endl;
        return 1;
    }
}
