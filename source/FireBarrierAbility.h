#ifndef FIREBARRIERABILITY_H
#define FIREBARRIERABILITY_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"


class FireBarrierAbility : public sf::Drawable
{
public:
    FireBarrierAbility(sf::RenderWindow& win, mke::AssetManager& assets, mke::DeltaTime& dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Sprite sprite;
    void update();
private:
    sf::RenderWindow& win;
    mke::AssetManager& assets;
    mke::DeltaTime& dt;
    mke::Animation animation;
    bool active = 1;
    void setupAnimation();
    void setupSprite();
};

#endif
