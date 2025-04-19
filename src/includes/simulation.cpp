#include "simulation.hpp"

int simulate(City &city) {
    // TODO: Simula i servizi della citta
    //  - Controllo se sono presenti
    //    - Controllo manutenzione
    //    - Controllo rischio

    // TODO: Simula la popolazione della citta
    //  - Controllo crescita

    if (city.population <= 0) {
        return SIM_FINE_POP;
    }

    // Ogni cittadino paga .20$ alla settimana
    city.budget += int(city.population * 0.20);

    if (city.budget < 0) {
        return SIM_FINE_BUDGET;
    }

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
