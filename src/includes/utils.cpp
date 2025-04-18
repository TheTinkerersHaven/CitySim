#include "game.hpp"
#include "utils.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

// Genera un numero casuale compreso tra min e max (inclusi)
int randomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Stampa le informazioni sulla citta'
void stampaInfo(City citta){
    cout << "SETTIMANA " << citta.time.week << " - MESE " << citta.time.month << " - ANNO " << citta.time.year << endl;
    cout << "Citta': " << citta.name << endl;
    cout << "Popolazione: " << citta.population << endl;
    cout << "Felicita': " << citta.mood << endl;
    cout << "Budget: " << citta.budget << endl;
}

// Calcola la progressione dei mesi e degli anni e restituisce la settimana dell'anno corrente 
int calcolaTempo(City citta){
    if(citta.time.week>4){
        citta.time.week=1;
        citta.time.month++;
    }
    if(citta.time.month>12){
        citta.time.month=1;
        citta.time.year++;
    }
    return (citta.time.month)*4 + citta.time.week;
}