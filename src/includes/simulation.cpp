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

        // CONTROLLO PRESENZA E CONDIZIONE SERVIZI
        // Se il servizio non è presente, riduci (-2) la felicità
        if (servizio == nullptr) {
            city.mood -= 2;
        }
        else {
            // Se il servizio ha condizione minore del 40%, riduci leggermente (-1) la felicità
            if (servizio->condizione < 40) {
                city.mood -= 1;
            }
            // Se il servizio è presente, invece, aumenta leggermente (+1) la felicità
            else {
                city.mood += 1;
            }

            // POSSIBILI DISASTRI DEI SERVIZI
            // Calcolo prima per evitare situazioni in cui un impianto al 100% venga immediatamente distrutto
            double possibilita = probabilitaRischio(servizio->condizione);

            // rand() / RAND_MAX genera un numero tra 0 e 1, moltiplicato per 100 per avere una percentuale
            double chance = (double(rand()) / RAND_MAX) * 100;

            if (chance < possibilita) {
                cout << "Il servizio " << nomeServizio(servizio->type) << " e' stato distrutto a causa di una catastrofe!" << endl;

                // Se il servizio è distrutto, riduci drasticamente (-10) la felicità
                city.mood -= 10;
                // Inoltre, fai scappare il 5% della popolazione
                city.population -= (city.population / 100) * 5;

                // Rimuovi il servizio
                removeService(city.services, city.servicesCount, servizio->type);
                city.servicesCount--;

                // Riduci l'index del loop per processare il prossimo servizio che, dopo la rimozione del corrente, è ora allo stesso index
                i--;
            }
            else {
                // Riduci la condizione del servizio, sempre evitando che vada fuori dal range 0-100%
                servizio->condizione -= randomNumber(1, 5);
                servizio->condizione = clamp(servizio->condizione, 0, 100);
            }
        }
    }

    // Imedisci alla felicita di andare fuori dal range 0-100%
    city.mood = clamp(city.mood, 0, 100);

    if (city.mood >= 75) {
        // Se la felicità è alta, aumenta la popolazione
        city.population += randomNumber(10, 50);
    }
    else if (city.mood <= 50) {
        // Se la felicità è bassa, diminuisci la popolazione
        city.population -= randomNumber(10, 50);
    }

    // Condizione di fine (non c'è più nessuno nella città)
    if (city.population <= 0) {
        return SIM_FINE_POP;
    }

    // Ogni cittadino paga .70$ alla settimana
    city.budget += int(city.population * 0.70);

    // Incrementa il tempo
    addWeek(city.time);

    return SIM_OK;
}

// Aumenta di una settimana il tempo e gestisce la progressione di mesi e anni
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

// (Funzione interna) Restituisce il fattore di rischio: https://www.desmos.com/calculator/5tbf21rzf2
double probabilitaRischio(int condizione) {
    // Casting a double per evitare che la divisione sia fatta tra interi
    return 50 * pow(1 - double(condizione) / 100, 2);
}
