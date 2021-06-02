#include "Random.h"

namespace mke
{
Random::Random()
{
    seed = time(0);
    random_engine.seed(seed);
}

Random::Random(unsigned long long seed)
{
    random_engine.seed(seed);
    this->seed = seed;
}

unsigned long long Random::getSeed()
{
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
