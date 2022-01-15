#pragma once
#include <random>

using namespace std;

class Random {
private:
    static random_device randomDevice;
    static uniform_int_distribution<short> boolDistro;
    static uniform_real_distribution<float> floatDistro;
    Random() = default;

public:
    static bool getBool();
    static float getFloat();
};