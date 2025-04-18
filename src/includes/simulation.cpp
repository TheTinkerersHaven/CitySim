#include "simulation.hpp"

void simulate(City &city) {
    // TODO: Simula i servizi della citta

    // TODO: Simula la popolazione della citta

    // TODO: Simula il budget della citta

    // Incrementa il tempo
    addWeek(city.time);
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
