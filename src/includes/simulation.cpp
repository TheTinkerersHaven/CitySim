#include "simulation.hpp"
#include "services.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

double probabilitaRischio(int condizione);

int simulate(City &city) {
    for (int i = 0; i < MAX_SERVICES; i++) {
        Service *servizio = city.services[i];

        if (servizio == nullptr) {
            // Se il servizio non è presente, riduci la felicità
            city.mood -= 2;
        } else {
            if (servizio->condizione < 40) {
                // Se il servizio ha condizione minore del 40%, riduci leggermente la felicità
                city.mood -= 1;
            } else {
                // Se il servizio è presente, invece, aumenta leggermente la felicità
                city.mood += 1;
            }

            // Riduci la condizione del servizio
            servizio->condizione -= randomNumber(1, 5);
            servizio->condizione = clamp(servizio->condizione, 0, 100);

            // Possibili disastri dei servizi
            double possibilita = probabilitaRischio(servizio->condizione);
            int chance = randomNumber(1, 100);

            if (chance < possibilita) {
                cout << "Il servizio " << nomeServizio(servizio->type) << " e' stato distrutto a causa di una catastrofe!" << endl;

                // Se il servizio è distrutto, riduci la felicità
                city.mood -= 10;

                // Rimuovi il servizio
                removeService(city.services, city.servicesCount, servizio->type);
                city.servicesCount--;

                // Riduci l'index del loop per processare il prossimo servizio che dopo la rimozione del corrente é ora allo stesso index
                i--;
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

// https://www.desmos.com/calculator/5tbf21rzf2
double probabilitaRischio(int condizione) {
    return 50 * pow(double(1 - double(condizione) / 100), 2);
}
