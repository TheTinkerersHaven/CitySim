#include "game.hpp" // Non sarebbe necessario, dato che è già incluso in savemanager.hpp, ma lo mettiamo per chiarezza
#include "savemanager.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

void stampaInfo(City citta);

int main() {
    City citta;
    srand((unsigned int)time(NULL));

    // NOTE: This uses the cmake output folder for the save file, so if you don't find the file, keep that in mind.
    if (!loadCity("citta.txt", citta)) {
        cerr << "ERRORE: Impossibile caricare la citta'. Generando una nuova citta'." << endl;
        citta = createNewCity();
    }

    // DEBUG
    stampaInfo(citta);

    if (!saveCity("citta.txt", citta)) {
        cerr << "ERRORE: Impossibile salvare la citta'." << endl;
        return 1;
    }

    return 0;
}

void stampaInfo(City citta){
    cout << "SETTIMANA " << citta.time.week << " - MESE " << citta.time.month << " - ANNO " << citta.time.year << endl;
    cout << "Citta': " << citta.name << endl;
    cout << "Popolazione: " << citta.population << endl;
    cout << "Felicita': " << citta.mood << endl;
    cout << "Budget: " << citta.budget << endl;
}