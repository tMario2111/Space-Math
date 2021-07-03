#include "FireBarrierAbility.h"

FireBarrierAbility::FireBarrierAbility(sf::RenderWindow& win, mke::AssetManager& assets, mke::DeltaTime& dt) :
    win(win),
    assets(assets),
    dt(dt),
    animation(sprite)

{
    setupAnimation();
    setupSprite();
}

void FireBarrierAbility::setupAnimation()
{
    animation.loadAtlas(assets.getTexture("fire_circle"), sf::Vector2u(8, 8));
    for(int i = 0; i < 7; i++)
        for(int j = 0; j < 8; j++)
            animation.addFrame(sf::Vector2u(j, i), sf::seconds(0.0001f));
    for(int j = 0; j < 5; j++)
        animation.addFrame(sf::Vector2u(j, 7), sf::seconds(0.0001f));
}

void FireBarrierAbility::setupSprite()
{
    animation.setSpriteFrame(sf::Vector2u(0, 0));
    sprite.setScale(3.f, 3.f);
    sprite.setOrigin(sprite.getLocalBounds().width / 4.05f, sprite.getLocalBounds().height / 4.225f);
    sprite.setPosition(win.getSize().x / 2, win.getSize().y / 2);
}

void FireBarrierAbility::setActive()
{
    active = 1;
    HP = default_HP;
}

bool FireBarrierAbility::getActive()
{
    return active;
}

void FireBarrierAbility::update()
{
    if(HP <= 0)
        active = 0;
    animation.run(dt.get());
}

void FireBarrierAbility::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(active)
        win.draw(sprite);
}
