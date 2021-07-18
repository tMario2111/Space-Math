#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"

#include "ShootingAbility.h"

class Enemy
{
public:
    Enemy(mke::AssetManager& assets, sf::RenderWindow& win, mke::DeltaTime& dt);
    sf::Sprite sprite;
    ShootingAbility shooting_ability;
    mke::Effect explosion;
    float damage;
    bool locked_on = 0;
    bool going_to_die = 0;
    bool dead = 0;
    sf::Vector2f target = sf::Vector2f(0, 0);
    virtual void onSpawn() = 0;
    virtual void update() = 0;
protected:
    mke::AssetManager& assets;
    sf::RenderWindow& win;
    mke::DeltaTime& dt;
    mke::Animation animation;
    float rotation;
    float movement_speed;
    float radius_to_mother_ship;
    void setupExplosion();
    virtual void setupAnimation() = 0;
    virtual void setupSprite() = 0;
    virtual void movement() = 0;
};

#endif
