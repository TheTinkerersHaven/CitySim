#include "savemanager.hpp"
#include <iostream>

bool saveCity(const string &path, City city) {
    ofstream file(path);

    if (!file) {
        return false;
    }

    file << city.nome << endl;
    file << city.popolazione << endl;
    file << city.buget << endl;
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
    file >> city.buget;
    file >> city.data;

    file.close();

    return true;
}
