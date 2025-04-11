#include "savemanager.hpp"
#include "utils.hpp"
#include <iostream>

const int MAX_NAME_LENGTH = 50;

const int GEN_POPULATION_MIN = 1000;
const int GEN_POPULATION_MAX = 2000;

const int GEN_BUDGET_MIN = 50;
const int GEN_BUDGET_MAX = 100;

bool saveCity(const string &path, City city) {
    ofstream file(path);

    if (!file) {
        return false;
    }

    file << city.name << endl;
    file << city.population << endl;
    file << city.budget << endl;
    file << city.time.year << endl;
    file << city.time.month << endl;
    file << city.time.week << endl;

    file.close();
    return true;
}

bool loadCity(const string &path, City &city) {
    ifstream file(path);

    if (!file) {
        return false;
    }

    getline(file, city.name);
    file >> city.population;
    file >> city.budget;
    file >> city.time.year;
    file >> city.time.month;
    file >> city.time.week;

    file.close();

    return true;
}

bool isValidName(const string &name) {
    // Check to see if the name is too long
    if (name.length() > MAX_NAME_LENGTH) {
        return false;
    }

    // Check if there are invalid characters found (we only want letters and spaces for now)
    for (int i = 0; i < name.length(); i++) {
        char c = name[i];

        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }

    return true;
}

City createNewCity() {
    City city;

    do {
        cout << "Inserisci il nome della città: ";
        getline(cin, city.name);

        // Check if the name is valid
        if (!isValidName(city.name)) {
            cout << "Nome non valido. Riprova." << endl;
        }
    } while (!isValidName(city.name));

    city.time.week = 0;
    city.time.month = 0;
    // TODO: Get current year?
    city.time.year = 2025;

    city.population = randomNumber(GEN_POPULATION_MIN, GEN_POPULATION_MAX);
    city.budget = randomNumber(GEN_BUDGET_MIN, GEN_BUDGET_MAX) * 1000;

    return city;
}
