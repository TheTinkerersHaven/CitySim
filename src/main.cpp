#include "includes/game.hpp"
#include "includes/savemanager.hpp"
#include "includes/services.hpp"
#include "includes/simulation.hpp"
#include "includes/utils.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

void menu(City citta);
void stampaInfoServizi(City &citta);
int simulaCitta(City &citta);
void aggiungiServizio(City &citta);
void riparaServizio(City &citta);
bool loadSave(City &citta);

int main() {
    srand((unsigned int)time(NULL));

    City citta;

    if (!loadSave(citta)) {
        cerr << "ERRORE: Caricamento citta' fallito." << endl;
        return 1;
    }

    cout << endl;
    stampaInfoCitta(citta);

    menu(citta);

    return 0;
}

void menu(City citta) {
    int scelta = 0;

    do {
        cout << "1) Stampa informazioni citta'" << endl;
        cout << "2) Stampa condizioni servizi" << endl;
        cout << "3) Vai avanti di una settimana" << endl;
        cout << "4) Aggiungi un servizio" << endl;
        cout << "5) Ripara un servizio" << endl;
        cout << "6) Salva i progressi e continua" << endl;
        cout << "0) Esci dal gioco senza salvare" << endl;

        do {
            cout << "Scegli un'azione: ";
            cin >> scelta;
            if (scelta < 0 || scelta > 6) cout << "Inserimento errato. Riprova." << endl;
        } while (scelta < 0 || scelta > 6);

        cout << endl;

        switch (scelta) {
            case 1:
                stampaInfoCitta(citta);
                break;
            case 2:
                stampaInfoServizi(citta);
                break;
            case 3: {
                int flag = simulaCitta(citta);

                // simulaCitta restituisce 1 se la citta' e' fallita, quindi esci dal menu
                if (flag == 1) return;

                break;
            }
            case 4:
                aggiungiServizio(citta);
                break;
            case 5:
                riparaServizio(citta);
                break;
            case 6:
                if (saveCity(citta)) cout << "Salvataggio effettuato." << endl;
                else cerr << "ERRORE: Salvataggio fallito. Controlla che il file sia disponibile e riprova." << endl;
                break;
            default:
                break;
        }

        cout << endl;
    } while (scelta != 0);
}

void stampaInfoServizi(City &citta) {
    Service *servizio = nullptr;

    // Il primo servizio ha tipo 1 e l'ultimo tipo 4 (Lo stesso delle poste, quindi usiamo il define delle poste per farci riferimento)
    for (int i = 1; i <= SERVICE_POST; i++) {
        servizio = findService(citta.services, citta.servicesCount, i);

        cout << "Servizio " << nomeServizio(i) << ": ";
        if (servizio == nullptr) {
            cout << "Non presente" << endl;
        } else {
            cout << "Condizione " << servizio->condizione << "%" << endl;
        }
    }
}

int simulaCitta(City &citta) {
    int risultatoSimulazione = simulate(citta);

    // Stampa un messaggio se la città è fallita
    if (risultatoSimulazione == SIM_FINE_POP) {
        cout << "Popolazione insufficiente. La citta' e' fallita." << endl;
    }

    // Se la città è fallita, indica al menu di uscire
    if (risultatoSimulazione < 0) {
        return 1;
    }

    return 0;
}

void aggiungiServizio(City &citta) {
    // 1) Chiedi il tipo di servizio
    int servizioScelto = chiediServizio("da aggiungere");

    // 2) Controlla se il servizio è già presente
    Service *servizio = findService(citta.services, citta.servicesCount, servizioScelto);
    if (servizio != nullptr) {
        cout << "Servizio gia' presente. Non puoi aggiungere il servizio." << endl;
        return;
    }

    // 3) Controlla il budget
    int costo = serviceCost(servizioScelto);

    cout << "Questo servizio costa " << costo << "$." << endl;
    cout << "Il tuo budget attuale e' " << citta.budget << "$." << endl;

    if (citta.budget < costo) {
        cout << "Budget insufficiente! Non puoi aggiungere il servizio." << endl;
        return;
    }

    bool conferma = chiediConferma();

    if (!conferma) {
        cout << "Operazione annullata." << endl;
        return;
    }

    // 4) Aggiungi il servizio
    citta.budget -= costo;

    citta.services[citta.servicesCount] = new Service;
    citta.services[citta.servicesCount]->type = servizioScelto;
    // Imposta condizione al 100%
    citta.services[citta.servicesCount]->condizione = 100;
    citta.servicesCount++;

    cout << "Servizio aggiunto con successo!" << endl;
}

void riparaServizio(City &citta) {
    // 1) Chiedi il tipo di servizio
    int servizioScelto = chiediServizio("da riparare");

    // 2) Controlla se il servizio è già presente
    Service *servizio = findService(citta.services, citta.servicesCount, servizioScelto);
    if (servizio == nullptr) {
        cout << "Servizio non presente." << endl;
        return;
    }

    // 3) Controlla il budget
    int costo = serviceCost(servizioScelto) / 2;

    cout << "Riparare questo servizio costa " << costo << "$." << endl;
    cout << "Il tuo budget attuale e' " << citta.budget << "$." << endl;

    if (citta.budget < costo) {
        cout << "Budget insufficiente! Non puoi riparare il servizio." << endl;
        return;
    }

    bool conferma = chiediConferma();

    if (!conferma) {
        cout << "Operazione annullata." << endl;
        return;
    }

    // 4) Ripara il servizio
    citta.budget -= costo;
    servizio->condizione = 100;

    cout << "Servizio riparato con successo!" << endl;
}

bool loadSave(City &citta) {
    cout << "Carica o crea una nuova citta':" << endl << endl;

    City cities[MAX_SAVES];
    int cittaSalvate = findSaves(cities, MAX_SAVES);

    for (int i = 0; i < cittaSalvate; i++) {
        cout << i + 1 << ") " << cities[i].name << "\tSettimana " << cities[i].time.week << " Mese " << cities[i].time.month << " Anno " << cities[i].time.year << " - Popolazione "
             << cities[i].population << ", Budget " << cities[i].budget << "$" << endl;
    }

    if (cittaSalvate == 0) {
        cout << "Non ci sono citta salvate, creane una per iniziare a giocare. " << endl;
    }

    cout << endl;
    cout << "c) Crea una nuova citta'" << endl;
    cout << "d) Cancella una citta'" << endl;
    cout << "o) Ordina per ..." << endl;
    cout << "q) Esci" << endl;
    cout << endl;

    int scelta = 0;

    // TODO: Dato che poi ci sono anche opzioni come crea e ordina, usiamo sempre numeri oppure usiamo lettere? (citta coi numeri e opzioni con le lettere)
    do {
        cout << "Scegli un'azione: ";
        cin >> scelta;
        if (scelta < 0 || scelta > cittaSalvate) cout << "Inserimento errato. Riprova." << endl;
    } while (scelta < 0 || scelta > cittaSalvate);

    if (scelta == 0) {
        cout << "Creazione citta'..." << endl;

        citta = createNewCity();
        saveCity(citta);

        return true;
    }

    citta = cities[scelta - 1];

    cout << "Citta' caricata con successo!" << endl;
    return true;
}
