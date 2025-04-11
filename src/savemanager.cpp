#include "savemanager.hpp"
#include "utils.hpp"
#include <iostream>

const int MAX_NAME_LENGTH = 50;

const int GEN_POPULATION_MIN = 1000;
const int GEN_POPULATION_MAX = 2000;

// The ' is only syntax, it doesn't do anything beside making this a bit easier to read
const int GEN_BUDGETN_MIN = 50'000;
const int GEN_BUDGETN_MAX = 100'000;

bool saveCity(const string &path, City city) {
    ofstream file(path);

    if (!file) {
        return false;
    }

    file << city.nome << endl;
    file << city.popolazione << endl;
    file << city.budget << endl;
    file << city.data << endl;

    file.close();
    return true;
}

bool loadCity(const string &path, City &city) {
    ifstream file(path);

    if (!file) {
        return false;
    }

    getline(file, city.nome);
    file >> city.popolazione;
    file >> city.budget;
    file >> city.data;

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
        getline(cin, city.nome);

        // Check if the name is valid
        if (!isValidName(city.nome)) {
            cout << "Nome non valido. Riprova." << endl;
        }
    } while (!isValidName(city.nome));

    // TODO: This will need to change as the time will need to work in weeks, however for now it stores years
    city.data = 2025;

    city.popolazione = randomNumber(GEN_POPULATION_MIN, GEN_POPULATION_MAX);
    city.budget = randomNumber(GEN_BUDGETN_MIN, GEN_BUDGETN_MAX);

    return city;
}
