#include "game.hpp"
#include "utils.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

int randomNumber(int min, int max) {
    // Genera un numero casuale compreso tra min e max (inclusi)
    return min + rand() % (max - min + 1);
}

void stampaInfo(City citta){
    cout << "SETTIMANA " << citta.time.week << " - MESE " << citta.time.month << " - ANNO " << citta.time.year << endl;
    cout << "Citta': " << citta.name << endl;
    cout << "Popolazione: " << citta.population << endl;
    cout << "Felicita': " << citta.mood << endl;
    cout << "Budget: " << citta.budget << endl;
}