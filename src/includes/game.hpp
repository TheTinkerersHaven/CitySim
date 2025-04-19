// Includi questo file solo una volta
#pragma once

#include <string>

using namespace std;

#define MAX_SERVICES 3
#define SERVICE_ELECTRIC 1
#define SERVICE_WATER 2
#define SERVICE_WASTE 3

struct Time {
    int week;
    int month;
    int year;
};

struct Service {
    // 1 = Elettrico, 2 = Idrico, 3 = Rifiuti
    int type;
    // Valore da 0 a 1
    double manutenzione;
};

struct City {
    string name;
    int population;
    int mood;
    int budget;
    Time time;

    // Dimensione logica per services
    int servicesCount;
    Service *services[MAX_SERVICES];
};
