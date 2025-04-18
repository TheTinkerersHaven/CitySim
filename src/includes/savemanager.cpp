#include "savemanager.hpp"
#include "game.hpp"
#include "utils.hpp"
#include <iostream>

const int MAX_NAME_LENGTH = 50;

const int GEN_POPULATION_MIN = 1000;
const int GEN_POPULATION_MAX = 2000;

const int GEN_BUDGET_MIN = 50;
const int GEN_BUDGET_MAX = 100;

bool saveCity(const string &path, City city) {
    ofstream file(path);

    if (!file) return false;

    file << city.name << endl;
    file << city.population << endl;
    file << city.mood << endl;
    file << city.budget << endl;
    file << city.time.year << endl;
    file << city.time.month << endl;
    file << city.time.week << endl;

    file.close();
    return true;
}

bool loadCity(const string &path, City &city) {
    ifstream file(path); // Dichiara "file" e ci inserisce il percorso del file

    if (!file) return false; // Se il file non esiste, dai errore

    getline(file, city.name);
    file >> city.population;
    file >> city.mood;
    file >> city.budget;
    file >> city.time.year;
    file >> city.time.month;
    file >> city.time.week;

    file.close();

    return true;
}

bool isValidName(const string &name) {
    // Controlla se il nome è troppo lungo
    if (name.length() > MAX_NAME_LENGTH) return false;

    // Controlla che ci siano solo caratteri validi (per ora solo lettere e spazi)
    for (int i = 0; i < name.length(); i++) {
        if (!isalpha(name[i]) && name[i] != ' ') return false;
    }

    return true;
}

City createNewCity() {
    City city;

    do {
        cout << "Inserisci il nome della citta': ";
        getline(cin, city.name);
        if (!isValidName(city.name)) cout << "Nome non valido. Riprova." << endl;
    } while (!isValidName(city.name));

    // Imposta la data iniziale
    city.time.week = 1;
    city.time.month = 1;
    city.time.year = 2025; // TODO: Prendere l'anno corrente (forse? può essere un'idea carina)
    city.mood = 100;

    // Genera casualmente la popolazione e il budget
    city.population = randomNumber(GEN_POPULATION_MIN, GEN_POPULATION_MAX);
    city.budget = randomNumber(GEN_BUDGET_MIN, GEN_BUDGET_MAX) * 1000;

    return city;
}
