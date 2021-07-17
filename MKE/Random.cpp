#include "Random.h"

namespace mke
{
Random::Random()
{
    seed = time(0);
    random_engine.seed(seed);
}

unsigned int Random::getSeed()
{
    return seed;
}

unsigned int Random::setUniqueSeed()
{
    seed = time(0);
    random_engine.seed(seed);
    return seed;
}

int Random::getInt(int a, int b)
{
    return std::uniform_int_distribution<int>(a, b)(random_engine);
}

float Random::getFloat(float a, float b)
{
    return std::uniform_real_distribution<float>(a, b)(random_engine);
}
}
