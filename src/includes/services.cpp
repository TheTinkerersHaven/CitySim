#include "services.hpp"
#include <stdexcept>
#include <string>

using namespace std;

void shift(Service *services[], int dim, int index);

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

void removeService(Service *services[], int dim, int type) {
    int i = 0;

    while (i < dim) {
        if (services[i]->type == type) {
            // Dealloca la memoria del servizio
            delete services[i];
            services[i] = nullptr;

            // Sposta gli altri servizi a sinistra
            shift(services, dim, i);

            return;
        }

        i++;
    }
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

string nomeServizio(int servizio) {
    switch (servizio) {
        case SERVICE_ELECTRIC:
            return "elettrico";
        case SERVICE_WATER:
            return "idrico";
        case SERVICE_WASTE:
            return "fognario";
        case SERVICE_POST:
            return "postale";
        default:
            throw logic_error("Servizio non valido");
    };
}

void shift(Service *services[], int dim, int index) {
    for (int i = index; i < dim - 1; i++) {
        services[i] = services[i + 1];
    }
}
