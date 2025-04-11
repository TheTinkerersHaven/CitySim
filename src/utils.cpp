#include "utils.hpp"
#include <cstdlib>

int randomNumber(int min, int max) {
    // Generate a random number between min and max (inclusive)
    return min + rand() % (max - min + 1);
}
