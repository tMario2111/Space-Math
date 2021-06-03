#include "LighterEnemy.h"


LighterEnemy::LighterEnemy(mke::AssetManager& assets, sf::RenderWindow& win, mke::DeltaTime& dt) :
    Enemy(assets, win, dt)
{
    movement_speed = 25.f;
    radius_to_mother_ship = 400.f;
    damage = 4.f;
    setupAnimation();
    setupSprite();
    setupShootingAbility();
}

void LighterEnemy::setupAnimation()
{
    animation.loadAtlas(assets.getTexture("lighter_enemy"), sf::Vector2u(4, 1));
    for (int i = 0; i < 4; i++)
        animation.addFrame(sf::Vector2u(i, 0), sf::seconds(0.125f));
}

void LighterEnemy::setupSprite()
{
    animation.setSpriteFrame(sf::Vector2u(0, 0));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setScale(1.625f, 1.625f);
    sprite.setPosition(100.f, 100.f);
}

void LighterEnemy::setupShootingAbility()
{
    shooting_ability.bullet_speed = 450.f;
    shooting_ability.shooting_speed = 3.f;
    shooting_ability.scale = sf::Vector2f(0.5f, 0.5f);
    sf::Texture& texture = assets.getTexture("long_bullets");
    shooting_ability.setTexture(texture);
    shooting_ability.setTextureRect(sf::IntRect(texture.getSize().x / 4 * 2, 0, texture.getSize().x / 4, texture.getSize().y));
}

void LighterEnemy::onSpawn()
{
    rotation = mke::utility::toDeg(atan2(win.getSize().y / 2 - sprite.getPosition().y, win.getSize().x / 2 - sprite.getPosition().x));
    sprite.setRotation(rotation + 90.f);
    shooting_ability.rotation = rotation;
}

void LighterEnemy::movement()
{
    if (mke::utility::distance(sprite.getPosition(), {(float)win.getSize().x / 2, (float)win.getSize().y / 2}) > radius_to_mother_ship)
    {
        sf::Vector2f velocity = {0, 0};
        velocity.x = movement_speed * cos(mke::utility::toRad(rotation)) * dt.get().asSeconds();
        velocity.y = movement_speed * sin(mke::utility::toRad(rotation)) * dt.get().asSeconds();
        sprite.move(velocity);
        shooting_ability.update(0, sprite.getPosition());
    }
    else
        shooting_ability.update(!going_to_die, sprite.getPosition());
}

void LighterEnemy::update()
{
    if (!going_to_die)
    {
        animation.run(dt.get());
        movement();
    }
    else
    {
        explosion.sprite.setPosition(sprite.getPosition());
        explosion.run(dt.get().asMilliseconds());
        if (explosion.isDone())
            dead = 1;
    }
}
