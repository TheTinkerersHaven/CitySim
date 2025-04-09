#include "game.hpp"
#include <iostream>

using namespace std;

int main() {
    Citta citta;
    citta.nome = "Roma";
    citta.popolazione = 2873000;
    citta.buget = 1000000;
    citta.data = 2023;

    cout << "Città: " << citta.nome << endl;
    cout << "Popolazione: " << citta.popolazione << endl;
    cout << "Budget: " << citta.buget << endl;
    cout << "Data: " << citta.data << endl;
}
