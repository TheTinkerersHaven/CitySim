// Includi questo file solo una volta
#pragma once

#include <string>

using namespace std;

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
};
