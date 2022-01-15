#include "Random.h"

random_device Random::randomDevice;
uniform_int_distribution<short> Random::boolDistro = uniform_int_distribution<short>(0, 1);
uniform_real_distribution<float> Random::floatDistro = uniform_real_distribution<float>(0, 1);

bool Random::getBool() {
    return boolDistro(randomDevice);
}

float Random::getFloat() {
    return floatDistro(randomDevice);
}
