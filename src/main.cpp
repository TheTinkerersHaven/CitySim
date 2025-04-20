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

int main() {
    City citta;
    srand((unsigned int)time(NULL));

    // NOTA: Questo utilizza la cartella di output di cmake per il file di salvataggio
    if (!loadCity("citta.txt", citta)) {
        cerr << "ERRORE: Impossibile caricare la citta'. Generando una nuova citta'." << endl;
        citta = createNewCity();
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
        cout << "5) Salva i progressi e continua" << endl;
        cout << "0) Esci dal gioco senza salvare" << endl;

        do {
            cout << "Scegli un'azione: ";
            cin >> scelta;
            if (scelta < 0 || scelta > 5) cout << "Inserimento errato. Riprova." << endl;
        } while (scelta < 0 || scelta > 5);

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
                if (saveCity("citta.txt", citta)) cout << "Salvataggio effettuato." << endl;
                else cerr << "ERRORE: Salvataggio fallito. Controlla che il file sia disponibile e riprova." << endl;

                break;
            default:
                break;
        }

        cout << endl;
    } while (scelta != 0);
}

void stampaInfoServizi(City &citta) {
    Service *servizio = findService(citta.services, citta.servicesCount, SERVICE_ELECTRIC);

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
}

int simulaCitta(City &citta) {
    int risultatoSimulazione = simulate(citta);

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

    // Se la città è fallita, indica al menu di uscire
    if (risultatoSimulazione < 0) {
        return 1;
    }

    return 0;
}

void aggiungiServizio(City &citta) {
    int servizioScelto = 0;
    int continuare = 0;

    // 1) Chiedi il tipo di servizio
    do {
        cout << "Scegli il servizio da aggiungere (1 = Elettrico, 2 = Idrico, 3 = Rifiuti): ";
        cin >> servizioScelto;

        if (servizioScelto < SERVICE_ELECTRIC || servizioScelto > SERVICE_WASTE) cout << "Servizio non valido. Riprova." << endl;
    } while (servizioScelto < SERVICE_ELECTRIC || servizioScelto > SERVICE_WASTE);

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

    do {
        cout << "Vuoi continuare? (1 = Si, 0 = No): ";
        cin >> continuare;
        if (continuare != 1 && continuare != 0) cout << "Inserimento errato. Riprova." << endl;
    } while (continuare != 1 && continuare != 0);

    if (continuare == 0) {
        cout << "Operazione annullata." << endl;
        return;
    }

    if (citta.budget < costo) {
        cout << "Budget insufficiente. Non puoi aggiungere il servizio." << endl;
        return;
    }

    // 4) Aggiungi il servizio
    citta.budget -= costo;

    citta.services[citta.servicesCount] = new Service;
    citta.services[citta.servicesCount]->type = servizioScelto;
    citta.services[citta.servicesCount]->manutenzione = 100; // Manutenzione al 100%
    citta.servicesCount++;

    cout << "Servizio aggiunto con successo." << endl;
}
