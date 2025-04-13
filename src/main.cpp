#include "includes/game.hpp" // Non sarebbe necessario (già incluso in savemanager.hpp) ma lo mettiamo per chiarezza
#include "includes/savemanager.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

void stampaInfo(City citta);

int main() {
    City citta;
    srand((unsigned int)time(NULL));

    // NOTA: Questo utilizza la cartella di output di cmake per il file di salvataggio
    if (!loadCity("citta.txt", citta)) {
        cerr << "ERRORE: Impossibile caricare la citta'. Generando una nuova citta'." << endl;
        citta = createNewCity();
    }

    // DEBUG - DA SOSTITUIRE CON MENU
    stampaInfo(citta);

    if (!saveCity("citta.txt", citta)) {
        cerr << "ERRORE: Impossibile salvare la citta'." << endl;
        return 1;
    }

    return 0;
}