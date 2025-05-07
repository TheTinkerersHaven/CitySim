#include "utils.hpp"
#include "game.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

// Genera un numero casuale compreso tra min e max (inclusi)
int randomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Stampa le informazioni correnti sulla citta'
void stampaInfoCitta(City citta) {
    cout << "SETTIMANA " << citta.time.week << " - MESE " << citta.time.month << " - ANNO " << citta.time.year << endl;
    cout << "Citta': " << citta.name << endl;
    cout << "Popolazione: " << citta.population << endl;
    cout << "Felicita': " << citta.mood << "%" << endl;
    cout << "Budget: " << citta.budget << "$" << endl;

    cout << endl;
}

// Chiede conferma per l'azione che si vuole effettuare (1 = Si, 0 = No) --> (1 = true, 0 = false)
bool chiediConferma() {
    int continuare = 0;

    do {
        cout << "Vuoi continuare? (1 = Si, 0 = No): ";
        cin >> continuare;
        if (continuare != 1 && continuare != 0) cout << "Inserimento errato. Riprova." << endl;
    } while (continuare != 1 && continuare != 0);

    return continuare == 1;
}
