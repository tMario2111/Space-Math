#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <ctime>

namespace mke
{
class Random
{
public:
    Random();
    Random(unsigned long long seed);
    unsigned long long getSeed();
    int getInt(int a, int b);
    float getFloat(float a, float b);
private:
    std::default_random_engine random_engine;
    unsigned long long seed;
};
}

#endif
