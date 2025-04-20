#pragma once

#define SERVICE_ELECTRIC 1
#define SERVICE_WATER 2
#define SERVICE_WASTE 3

struct Service {
    // 1 = Elettrico, 2 = Idrico, 3 = Rifiuti
    int type;
    // Valore da 0 a 100
    int manutenzione;
};

Service *findService(Service *services[], int dim, int type);
int serviceCost(int type);
