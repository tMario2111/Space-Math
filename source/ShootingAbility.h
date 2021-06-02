#ifndef SHOOTINGABILITY_H
#define SHOOTINGABILITY_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"
#include <vector>
#include <cmath>

class ShootingAbility
{
public:
    ShootingAbility(sf::RenderWindow& win, mke::DeltaTime& dt);
    float bullet_speed;
    unsigned int shooting_speed;
    float rotation;
    sf::Vector2f scale;
    std::vector<sf::Sprite> bullets;
    void setTexture(sf::Texture& texture);
    void setTextureRect(sf::IntRect texture_rect);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(bool is_shooting, sf::Vector2f position);
private:
    const float DESTROY_MARGIN = 100.f;
    sf::RenderWindow& win;
    mke::DeltaTime& dt;
    float shooting_clock = 0;
    sf::IntRect texture_rect;
    sf::Texture* texture;
    void createBullet(sf::Vector2f position);
    void destroyBullets();
    void movement();
};

#endif
