#ifndef PARTICLES_H
#define PARTICLES_H

#include <SFML/Graphics.hpp>
#include "Utility.h"
#include <random>
#include <ctime>
#include <cmath>
#include <vector>
#include <utility>

namespace mke
{
class Particles : public sf::Drawable
{
public:
    Particles();
    void addColor(sf::Color color);
    void clearColors();
    void setLifetimeRange(sf::Time a, sf::Time b);
    void setPositionOffsetRange(float offset1, float offset2);
    void setParticlesPerSecondRange(unsigned int n1, unsigned int n2);
    void setDirectionOffsetRange(float a1, float a2);
    void create(sf::Time dt, sf::Vector2f position, float speed1, float speed2, float direction);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(sf::Time dt);
private:
    struct Particle
    {
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Time lifetime_clock;
        sf::Time lifetime_time;
        sf::Color color;
    };
    std::vector<Particle> particles_vec;
    std::default_random_engine random;
    sf::VertexArray batch;
    std::vector<sf::Color> colors;
    std::pair<sf::Time, sf::Time> lifetime_range;
    std::pair<float, float> position_offset;
    std::pair<unsigned int, unsigned int> particles_per_second;
    std::pair<float, float> direction_offset;
    void checkLifetime(sf::Time dt);
    void movement(sf::Time dt);
    void updateBatch();
};
}

#endif
