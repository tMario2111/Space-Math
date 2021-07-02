#ifndef FIREBARRIERABILITY_H
#define FIREBARRIERABILITY_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"


class FireBarrierAbility : public sf::Drawable
{
public:
    FireBarrierAbility(sf::RenderWindow& win, mke::AssetManager& assets, mke::DeltaTime& dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void setActive();
    bool getActive();
    float HP = 25.f;
    sf::Sprite sprite;
    void update();
private:
    sf::RenderWindow& win;
    mke::AssetManager& assets;
    mke::DeltaTime& dt;
    mke::Animation animation;
    bool active = 0;
    const float default_HP = 25.f;
    void setupAnimation();
    void setupSprite();
};

#endif
