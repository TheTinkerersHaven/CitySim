// Includi questo file solo una volta
#pragma once

#include "services.hpp"
#include <string>

using namespace std;

#define MAX_SERVICES 3

struct Time {
    int week;
    int month;
    int year;
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
