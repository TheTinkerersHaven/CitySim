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
