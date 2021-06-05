#ifndef PARANOIDENEMY_H
#define PARANOIDENEMY_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"
#include <cmath>

#include "Enemy.h"
#include "ShootingAbility.h"

class ParanoidEnemy : public Enemy
{
public:
    ParanoidEnemy(mke::AssetManager& assets, sf::RenderWindow& win, mke::DeltaTime& dt);
    void onSpawn();
    void update();
private:
    void setupAnimation();
    void setupSprite();
    void setupShootingAbility();
    void movement();
};
#endif
