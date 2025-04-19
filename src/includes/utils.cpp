#include "utils.hpp"
#include "game.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

// Genera un numero casuale compreso tra min e max (inclusi)
int randomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Stampa le informazioni sulla citta'
void stampaInfoCitta(City citta) {
    cout << "SETTIMANA " << citta.time.week << " - MESE " << citta.time.month << " - ANNO " << citta.time.year << endl;
    cout << "Citta': " << citta.name << endl;
    cout << "Popolazione: " << citta.population << endl;
    cout << "Felicita': " << citta.mood << endl;
    cout << "Budget: " << citta.budget << endl;
}
