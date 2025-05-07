#include "services.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void shiftServizi(Service *services[], int dim, int index);

Service *findService(Service *services[], int dim, int type) {
    int i = 0;

    while (i < dim) {
        if (services[i]->type == type) {
            return services[i];
        }
        i++;
    }

    return nullptr;
}

void removeService(Service *services[], int dim, int type) {
    int i = 0;

    while (i < dim) {
        if (services[i]->type == type) {
            // Dealloca la memoria del servizio
            delete services[i];
            services[i] = nullptr;

            // Sposta gli altri servizi a sinistra
            shiftServizi(services, dim, i);

            return;
        }

        i++;
    }
}

int serviceCost(int type) {
    switch (type) {
        case SERVICE_ELECTRIC:
            return 20'000;
        case SERVICE_WATER:
            return 20'000;
        case SERVICE_WASTE:
            return 15'000;
        case SERVICE_POST:
            return 25'000;
        default:
            throw logic_error("Servizio non valido");
    }
}

string nomeServizio(int servizio) {
    switch (servizio) {
        case SERVICE_ELECTRIC:
            return "elettrico";
        case SERVICE_WATER:
            return "idrico";
        case SERVICE_WASTE:
            return "fognario";
        case SERVICE_POST:
            return "postale";
        default:
            throw logic_error("Servizio non valido");
    };
}

int chiediServizio(const string &messaggio) {
    int servizioScelto = 0;
    do {
        cout << "Scegli il servizio " << messaggio << " (1 = Elettrico, 2 = Idrico, 3 = Rifiuti, 4 = Poste): ";
        cin >> servizioScelto;
        if (servizioScelto < SERVICE_ELECTRIC || servizioScelto > SERVICE_POST) cout << "Servizio non valido. Riprova." << endl;
    } while (servizioScelto < SERVICE_ELECTRIC || servizioScelto > SERVICE_POST);

    return servizioScelto;
}

void shiftServizi(Service *services[], int dim, int index) {
    // Controlla se siamo alla fine dell'array
    if (index == dim) return;

    // Se siamo all'ultima posizione dell'array non abbiamo nulla da shiftare quindi mettiamo nullptr
    if (index == dim - 1) {
        services[index] = nullptr;
    }
    // Shifta verso sinistra l'elemento
    else {
        services[index] = services[index + 1];
    }

    // Chiamata ricorsiva con l'incremento dell'index
    shiftServizi(services, dim, index + 1);
}
