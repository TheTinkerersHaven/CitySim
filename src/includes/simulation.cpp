#include "simulation.hpp"
#include "utils.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

double probabilitaRischio(int condizione);
string nomeServizio(int servizio);

int simulate(City &city) {
    for (int i = 0; i < MAX_SERVICES; i++) {
        if (city.services[i] == nullptr) {
            // Se il servizio non è presente, riduci la felicità
            city.mood -= 2;
        } else {
            if (city.services[i]->condizione < 40) {
                // Se il servizio ha condizione minore del 40%, riduci leggermente la felicità
                city.mood -= 1;
            } else {
                // Se il servizio è presente, invece, aumenta leggermente la felicità
                city.mood += 1;
            }

            // Riduci la condizione del servizio
            city.services[i]->condizione -= randomNumber(1, 5);
            city.services[i]->condizione = clamp(city.services[i]->condizione, 0, 100);

            // Possibili disastri dei servizi
            double poss = probabilitaRischio(city.services[i]->condizione);
            int randN = randomNumber(1, 100); 
            if (randN < poss) {
                cout << "Il servizio " << nomeServizio(city.services[i]->type) << " e' stato distrutto a causa di una catastrofe!" << endl;
                // TODO: rimuovi servizio
            }
        }
    }

    // Imedisci alla felicita di andare sotto lo 0% e sopra il 100%
    city.mood = clamp(city.mood, 0, 100);

    if (city.mood >= 75) {
        // Se la felicità è alta, aumenta la popolazione
        city.population += randomNumber(10, 50);
    } else if (city.mood <= 50) {
        // Se la felicità è bassa, diminuisci la popolazione
        city.population -= randomNumber(10, 50);
    }

    // Condizione di fine
    if (city.population <= 0) {
        return SIM_FINE_POP;
    }

    // Ogni cittadino paga .20$ alla settimana
    city.budget += int(city.population * 0.20);

    // Incrementa il tempo
    addWeek(city.time);

    return SIM_OK;
}

void addWeek(Time &time) {
    // Aumenta di uno le settimane
    time.week += 1;

    // Dopo 4 settimane, aumenta di uno il mese
    if (time.week > 4) {
        time.week = 1;
        time.month += 1;
    }

    // Dopo 12 mesi, aumenta di uno l'anno
    if (time.month > 12) {
        time.month = 1;
        time.year += 1;
    }
}

double probabilitaRischio(int condizione) {
    return 50 * pow(double(1 - double(condizione) / 100), 2);
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
