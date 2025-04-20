#include "includes/game.hpp"
#include "includes/savemanager.hpp"
#include "includes/services.hpp"
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
    int scelta = 0;
    int risultatoSimulazione = 0;
    Service *servizio = nullptr;

    do {
        cout << "1) Stampa informazioni citta'" << endl;
        cout << "2) Stampa condizioni servizi" << endl;
        cout << "3) Vai avanti di una settimana" << endl;
        cout << "4) Aggiungi un servizio" << endl;
        cout << "5) Salva i progressi e continua" << endl;
        cout << "0) Esci dal gioco senza salvare" << endl;

        do {
            cout << "Scegli un'azione: ";
            cin >> scelta;
            if (scelta < 0 || scelta > 5) cout << "Inserimento errato. Riprova." << endl;
        } while (scelta < 0 || scelta > 5);

        cout << endl << endl;

        switch (scelta) {
            case 1:
                stampaInfoCitta(citta);
                break;
            case 2:
                servizio = findService(citta.services, citta.servicesCount, SERVICE_ELECTRIC);

                cout << "Servizio Elettrico: ";
                if (servizio != nullptr) {
                    cout << "Manutenzione " << servizio->manutenzione << "%";
                } else {
                    cout << "Non presente";
                }
                cout << endl;

                servizio = findService(citta.services, citta.servicesCount, SERVICE_WATER);

                cout << "Servizio Idrico: ";
                if (servizio != nullptr) {
                    cout << "Manutenzione " << servizio->manutenzione << "%";
                } else {
                    cout << "Non presente";
                }
                cout << endl;

                servizio = findService(citta.services, citta.servicesCount, SERVICE_WASTE);

                cout << "Servizio dei Rifiuti: ";
                if (servizio != nullptr) {
                    cout << "Manutenzione " << servizio->manutenzione << "%";
                } else {
                    cout << "Non presente";
                }
                cout << endl;

                break;
            case 3:
                risultatoSimulazione = simulate(citta);

                // Stampa un messaggio se la città è fallita
                switch (risultatoSimulazione) {
                    case SIM_FINE_BUDGET:
                        cout << "Budget insufficiente. La citta' e' fallita." << endl;
                        break;
                    case SIM_FINE_POP:
                        cout << "Popolazione insufficiente. La citta' e' fallita." << endl;
                        break;
                    default:
                        break;
                }

                // Se la città è fallita, esci dal menu
                if (risultatoSimulazione < 0) {
                    return;
                }

                break;
            case 4:
                // TODO: Aggiungi un servizio

                // 1) Chiedi il tipo di servizio
                // 2) Crea il servizio nella citta ad un costo

                break;
            case 5:
                if (saveCity("citta.txt", citta)) cout << "Salvataggio effettuato." << endl;
                else cerr << "ERRORE: Salvataggio fallito. Controlla che il file sia disponibile e riprova." << endl;
                break;
            default:
                break;
        }

        cout << endl << endl;
    } while (scelta != 0);
}
