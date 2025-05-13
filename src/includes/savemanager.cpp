#include "savemanager.hpp"
#include "game.hpp"
#include "utils.hpp"
#include <filesystem>
#include <iostream>

#define SAVE_DIRECTORY_NAME "saves"

#define MAX_NAME_LENGTH 50

#define GEN_POPULATION_MIN 1000
#define GEN_POPULATION_MAX 2000

#define GEN_BUDGET_MIN 50
#define GEN_BUDGET_MAX 100

using namespace std;

bool saveCity(City &city) {
    // Crea il percorso in base alla cartella in cui mettere i salvataggi, e il nome della citta
    // -> saves/<name>.txt
    ofstream file(SAVE_DIRECTORY_NAME / filesystem::path(city.name).replace_extension(".txt"));

    if (!file) return false;

    file << city.name << endl;
    file << city.population << endl;
    file << city.mood << endl;
    file << city.budget << endl;
    file << city.time.year << endl;
    file << city.time.month << endl;
    file << city.time.week << endl;

    file << city.servicesCount << endl;

    for (int i = 0; i < city.servicesCount; i++) {
        file << city.services[i]->type << endl;
        file << city.services[i]->condizione << endl;
    }

    file.close();
    return true;
}

bool loadCity(const string &path, City &city) {
    // Dichiara "file" e ci e apri il file al percorso indicato
    ifstream file(path);

    // Se il file non esiste, dai errore
    if (!file) return false;

    getline(file, city.name);
    file >> city.population;
    file >> city.mood;
    file >> city.budget;
    file >> city.time.year;
    file >> city.time.month;
    file >> city.time.week;

    for (int i = 0; i < MAX_SERVICES; i++) {
        city.services[i] = nullptr;
    }

    file >> city.servicesCount;

    for (int i = 0; i < city.servicesCount; i++) {
        city.services[i] = new Service;
        file >> city.services[i]->type;
        file >> city.services[i]->condizione;
    }

    file.close();

    return true;
}

bool deleteCity(City &city) {
    filesystem::path saveFile = SAVE_DIRECTORY_NAME / filesystem::path(city.name).replace_extension(".txt");

    return filesystem::remove(saveFile);
}

bool isValidName(const string &name) {
    size_t i = 0;
    // Richiedi un nome
    if (name.empty()) return false;
    // Controlla se il nome è troppo lungo
    if (name.length() > MAX_NAME_LENGTH) return false;

    // Controlla che ci siano solo caratteri validi (per ora solo lettere e spazi)
    while (i < name.length()) {
        if (!isalpha(name[i]) && name[i] != ' ') return false;
        i++;
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

    // Prendi la data corrente
    time_t t = time(nullptr);
    tm *now = localtime(&t);

    // Imposta la data iniziale
    city.time.week = 1;
    city.time.month = 1;
    // tm_year parte dal 1900 quindi dobbiamo aggiungerlo manualmente
    city.time.year = now->tm_year + 1900;

    city.mood = 100;

    // Genera casualmente la popolazione e il budget
    city.population = randomNumber(GEN_POPULATION_MIN, GEN_POPULATION_MAX);
    city.budget = randomNumber(GEN_BUDGET_MIN, GEN_BUDGET_MAX) * 1000;

    city.servicesCount = 0;
    for (int i = 0; i < MAX_SERVICES; i++) {
        city.services[i] = nullptr;
    }

    return city;
}

int findSaves(City saves[], int capacity) {
    // Dobbiamo creare la cartella se non esiste oppure "filesystem::directory_iterator" tira un exception
    if (!filesystem::exists(SAVE_DIRECTORY_NAME)) {
        filesystem::create_directory(SAVE_DIRECTORY_NAME);
    }

    int savesFound = 0;
    bool limiteRaggiunto = false;

    for (filesystem::directory_iterator itr(SAVE_DIRECTORY_NAME); itr != filesystem::end(itr); itr++) {
        // Controlla se abbiamo trovato un file con estensione .txt
        if (itr->is_regular_file() && itr->path().extension() == ".txt") {
            // Controlla se abbiamo gia caricato il numero massimo di salvataggi che possiamo mettere nell'array
            if (savesFound >= capacity) {
                limiteRaggiunto = true;
            }
            // Prova a caricare il salvataggio e se va a buon fine aggiungi alla dimensione logica dell'array
            else if (loadCity(itr->path().string(), saves[savesFound])) {
                savesFound++;
            }
            // Se è stato impossibile caricare il salvataggio avvisa l'utente
            else {
                cerr << "Impossibile caricare il salvataggio presente in " << itr->path() << "." << endl;
            }
        }
    }

    if (limiteRaggiunto) {
        cerr << "Sono stati trovati più salvataggi di quelli possibili. Alcuni salvataggi non sono stati presi in considerazione." << endl;
    }

    return savesFound;
}
