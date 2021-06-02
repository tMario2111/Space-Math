#include "DeltaTime.h"

namespace mke
{
void DeltaTime::update()
{
    time = clock.restart();
}
sf::Time DeltaTime::get()
{
    return time;
}
}
