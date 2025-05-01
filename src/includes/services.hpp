#pragma once

#include <string>

using namespace std;

#define SERVICE_ELECTRIC 1
#define SERVICE_WATER 2
#define SERVICE_WASTE 3
#define SERVICE_POST 4

struct Service {
    // 1 = Elettrico, 2 = Idrico, 3 = Rifiuti, 4 = Poste
    int type;
    // Valore da 0 a 100
    int condizione;
};

Service *findService(Service *services[], int dim, int type);
void removeService(Service *services[], int dim, int type);

int serviceCost(int type);
string nomeServizio(int servizio);
