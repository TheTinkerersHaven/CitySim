#include "includes/game.hpp" // Non sarebbe necessario (già incluso in savemanager.hpp) ma lo mettiamo per chiarezza
#include "includes/savemanager.hpp"
#include "includes/simulation.hpp"
#include "includes/utils.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

void menu(City citta);

int main() {
    City citta;
    srand((unsigned int)time(NULL));

    // NOTA: Questo utilizza la cartella di output di cmake per il file di salvataggio
    if (!loadCity("citta.txt", citta)) {
        cerr << "ERRORE: Impossibile caricare la citta'. Generando una nuova citta'." << endl;
        citta = createNewCity();
    }

    cout << citta.name << " - SETTIMANA " << citta.time.week << " - MESE " << citta.time.month << " - ANNO " << citta.time.year << endl;
    menu(citta);

    return 0;
}

void menu(City citta) {
    int scelta = 0, salva = 0;
    do {
        cout << "1) Stampa informazioni citta'" << endl;
        cout << "2) Stampa condizioni servizi" << endl;
        cout << "3) Vai avanti di una settimana" << endl;
        cout << "4) Salva i progressi e continua" << endl;
        cout << "0) Esci dal gioco senza salvare" << endl;

        do {
            cout << "Scegli un'azione: ";
            cin >> scelta;
            if (scelta < 0 || scelta > 5) cout << "Inserimento errato. Riprova.";
        } while (scelta < 0 || scelta > 5);

        switch (scelta) {
            case 1:
                stampaInfo(citta);
                break;
            case 2:
                break; // TODO
            case 3:
                addWeek(citta.time);
                break;
            case 4:
                if (saveCity("citta.txt", citta)) cout << "Salvataggio effettuato." << endl;
                else cerr << "ERRORE: Salvataggio fallito. Controlla che il file sia disponibile e riprova." << endl;
                break;
            default:
                break;
        }
    } while (scelta != 0);
}
