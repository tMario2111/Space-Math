#ifndef MOTHERSHIP_H
#define MOTHERSHIP_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"
#include <memory>
#include <vector>

#include "Enemy.h"
#include "Equations.h"

class MotherShip : public sf::Drawable
{
public:
    MotherShip(mke::AssetManager& assets, sf::RenderWindow& win, mke::DeltaTime& dt);
    sf::Sprite sprite;
    mke::Effect explosion;
    bool exploding = 0;
    float HP = 100.f;
    void findClosestEnemy(std::vector<std::unique_ptr<Enemy>>& enemies, Equations& equations, unsigned int& score);
    void update();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    mke::AssetManager& assets;
    sf::RenderWindow& win;
    mke::DeltaTime& dt;
    sf::Sprite target;
    float rotation_speed = -5.f;
    void setupSprite();
    void setupTarget();
    void setupExplosion();
    void rotate();
    void updateDamageTexture();
};

#endif
