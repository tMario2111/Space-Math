#include "UFOEnemy.h"

UFOEnemy::UFOEnemy(mke::AssetManager& assets, sf::RenderWindow& win, mke::DeltaTime& dt) :
Enemy(assets, win, dt)
{
    movement_speed = win.getSize().x * win.getSize().y / 51840.f;
    radius_to_mother_ship = 275.f;
    damage = 0.75f;
    setupAnimation();
    setupSprite();
    setupShootingAbility();
}

void UFOEnemy::setupAnimation()
{
    animation.loadAtlas(assets.getTexture("ufo_enemy"), sf::Vector2u(4, 1));
    for (int i = 0; i < 4; i++)
        animation.addFrame(sf::Vector2u(i, 0), sf::seconds(0.075f));
}

void UFOEnemy::setupSprite()
{
    animation.setSpriteFrame(sf::Vector2u(0, 0));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setScale(1.625f, 1.625f);
    sprite.setPosition(100.f, 100.f);
}

void UFOEnemy::setupShootingAbility()
{
    shooting_ability.bullet_speed = 150.f;
    shooting_ability.shooting_speed = 0.5f;
    shooting_ability.rotation_speed = 720.f;
    shooting_ability.scale = sf::Vector2f(0.65f, 0.65f);
    sf::Texture& texture = assets.getTexture("star_bullet");
    shooting_ability.setTexture(texture);
    shooting_ability.setTextureRect(sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y));
}

void UFOEnemy::onSpawn()
{
    rotation = mke::utility::toDeg(atan2(win.getSize().y / 2 - sprite.getPosition().y, win.getSize().x / 2 - sprite.getPosition().x));
    sprite.setRotation(rotation + 90.f);
    shooting_ability.rotation = rotation;
}

void UFOEnemy::movement()
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

void UFOEnemy::update()
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
