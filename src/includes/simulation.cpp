#include "simulation.hpp"
#include "utils.hpp"
#include <algorithm>

int simulate(City &city) {
    for (int i = 0; i < MAX_SERVICES; i++) {
        if (city.services[i] == nullptr) {
            // Se il servizio non è presente, riduci la felicità
            city.mood -= 2;
        }
        else{
            if(city.services[i]->condizione<40){
                // Se il servizio ha condizione minore del 40%, riduci leggermente la felicità
                city.mood -= 1;
            }
            else{
                // Se il servizio è presente, invece, aumenta leggermente la felicità
                city.mood += 1;
            }

            // Riduci la condizione del servizio
            city.services[i]->condizione -= randomNumber(1, 5);
            city.services[i]->condizione = clamp(city.services[i]->condizione, 0, 100);

            // TODO: Rischio
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

    // Condizione di fine (:D)
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
