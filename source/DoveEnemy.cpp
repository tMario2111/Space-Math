#include "DoveEnemy.h"

DoveEnemy::DoveEnemy(mke::AssetManager& assets, sf::RenderWindow& win, mke::DeltaTime& dt) :
    Enemy(assets, win, dt)
{
    movement_speed = 50.f;
    radius_to_mother_ship = 250.f;
    damage = 2.5f;
    setupAnimation();
    setupSprite();
    setupShootingAbility();
}

void DoveEnemy::setupAnimation()
{
    animation.loadAtlas(assets.getTexture("dove_enemy"), sf::Vector2u(4, 1));
    for (int i = 0; i < 4; i++)
        animation.addFrame(sf::Vector2u(i, 0), sf::seconds(0.125f));
}

void DoveEnemy::setupSprite()
{
    animation.setSpriteFrame(sf::Vector2u(0, 0));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setScale(1.625f, 1.625f);
    sprite.setPosition(100.f, 100.f);
}

void DoveEnemy::setupShootingAbility()
{
    shooting_ability.bullet_speed = 250.f;
    shooting_ability.shooting_speed = 1.f;
    shooting_ability.scale = sf::Vector2f(0.5f, 0.5f);
    sf::Texture& texture = assets.getTexture("long_bullets");
    shooting_ability.setTexture(texture);
    shooting_ability.setTextureRect(sf::IntRect(texture.getSize().x / 4 * 3, 0, texture.getSize().x / 4, texture.getSize().y));
}

void DoveEnemy::onSpawn()
{
    rotation = mke::utility::toDeg(atan2(win.getSize().y / 2 - sprite.getPosition().y, win.getSize().x / 2 - sprite.getPosition().x));
    sprite.setRotation(rotation + 90.f);
    shooting_ability.rotation = rotation;
}

void DoveEnemy::movement()
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

void DoveEnemy::update()
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
