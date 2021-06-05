#ifndef UFOENEMY_H
#define UFOENEMY_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"
#include <cmath>

#include "Enemy.h"
#include "ShootingAbility.h"

class UFOEnemy : public Enemy
{
public:
    UFOEnemy(mke::AssetManager& assets, sf::RenderWindow& win, mke::DeltaTime& dt);
    void onSpawn();
    void update();
private:
    void setupAnimation();
    void setupSprite();
    void setupShootingAbility();
    void movement();
};

#endif
