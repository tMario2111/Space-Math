#ifndef DELTATIME_H
#define DELTATIME_H

#include <SFML/Graphics.hpp>

namespace mke
{
class DeltaTime
{
public:
    void update();
    sf::Time get();
private:
    sf::Clock clock;
    sf::Time time;
};
}

#endif
