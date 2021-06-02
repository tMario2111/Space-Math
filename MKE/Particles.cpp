#include "Particles.h"

namespace mke
{
Particles::Particles() :
    batch(sf::Points, 0)
{
    random.seed(time(0));
}

void Particles::addColor(sf::Color color)
{
    colors.push_back(color);
}

void Particles::clearColors()
{
    colors.clear();
}

void Particles::setLifetimeRange(sf::Time a, sf::Time b)
{
    lifetime_range = std::make_pair(a, b);
}

void Particles::setPositionOffsetRange(float offset1, float offset2)
{
    position_offset = std::make_pair(offset1, offset2);
}

void Particles::setParticlesPerSecondRange(unsigned int n1, unsigned int n2)
{
    particles_per_second = std::make_pair(n1, n2);
}

void Particles::setDirectionOffsetRange(float a1, float a2)
{
    direction_offset = std::make_pair(a1, a2);
}

void Particles::checkLifetime(sf::Time dt)
{
    for (unsigned int i = 0; i < particles_vec.size(); i++)
    {
        Particle& particle = particles_vec[i];
        particle.lifetime_clock += dt;
        if (particle.lifetime_clock >= particle.lifetime_time)
            particles_vec.erase(particles_vec.begin() + i--);
    }
}

void Particles::create(sf::Time dt, sf::Vector2f position, float speed1, float speed2, float direction)
{
    unsigned int p_count = std::uniform_int_distribution<unsigned int>(particles_per_second.first, particles_per_second.second)(random);
    p_count *= dt.asSeconds();
    for (unsigned int i = 0; i < p_count; i++)
    {
        Particle particle;
        particle.lifetime_time = sf::seconds
                                 (std::uniform_real_distribution<float>(lifetime_range.first.asSeconds(), lifetime_range.second.asSeconds())(random));
        particle.position = position + sf::Vector2f(std::uniform_real_distribution<float>(position_offset.first, position_offset.second)(random),
                            std::uniform_real_distribution<float>(position_offset.first, position_offset.second)(random));
        particle.color = colors.size() == 0 ? sf::Color::White : colors[std::uniform_int_distribution<unsigned int>(0, colors.size() - 1)(random)];
        direction += std::uniform_real_distribution<float>(direction_offset.first, direction_offset.second)(random);
        float speed = std::uniform_real_distribution<float>(speed1, speed2)(random);
        particle.velocity.x = speed * cos(mke::utility::toRad(direction));
        particle.velocity.y = speed * sin(mke::utility::toRad(direction));
        particles_vec.push_back(particle);;
    }
}

void Particles::movement(sf::Time dt)
{
    for (Particle& i : particles_vec)
        i.position += sf::Vector2f(i.velocity.x * dt.asSeconds(), i.velocity.y * dt.asSeconds());
}

void Particles::updateBatch()
{
    batch.clear();
    for (Particle i : particles_vec)
        batch.append(sf::Vertex(i.position, i.color));
}

void Particles::update(sf::Time dt)
{
    checkLifetime(dt);
    movement(dt);
    updateBatch();
}

void Particles::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(batch, states);
}
}
