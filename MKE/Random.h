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
    unsigned int getSeed();
    unsigned int setUniqueSeed();
    void setCustomSeed(unsigned int seed);
    int getInt(int a, int b);
    float getFloat(float a, float b);
private:
    std::default_random_engine random_engine;
    unsigned int seed;
};
}

#endif
