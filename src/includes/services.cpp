#include "services.hpp"

Service *findService(Service *services[], int dim, int type) {
    int i = 0;

    while (i < dim) {
        if (services[i]->type == type) {
            return services[i];
        }
        i++;
    }

    return nullptr;
}

int serviceCost(int type) {
    switch (type) {
        case SERVICE_ELECTRIC:
            return 20'000;
        case SERVICE_WATER:
            return 20'000;
        case SERVICE_WASTE:
            return 15'000;
        case SERVICE_POST:
            return 25'000;
        default:
            return 0;
    }
}
