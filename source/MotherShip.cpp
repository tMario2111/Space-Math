#include "MotherShip.h"

MotherShip::MotherShip(mke::AssetManager& assets, sf::RenderWindow& win, mke::DeltaTime& dt) :
    assets(assets),
    win(win),
    dt(dt)
{
    setupSprite();
    setupTarget();
    setupExplosion();
}

void MotherShip::setupSprite()
{
    sprite.setTexture(assets.getTexture("mother_ship_100%"));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setScale(0.75f, 0.75f);
    sprite.setPosition(win.getSize().x / 2, win.getSize().y / 2);
    sprite.setColor(sf::Color(200, 200, 200));
}

void MotherShip::setupTarget()
{
    target.setTexture(assets.getTexture("target"));
    target.setOrigin(target.getLocalBounds().width / 2, target.getLocalBounds().height / 2);
    target.setScale(0.2f, 0.2f);
}

void MotherShip::setupExplosion()
{
    explosion.loadSpriteSheet(assets.getTexture("explosion_texture"), sf::Vector2i(4, 4));
    explosion.setDuration(sf::seconds(1.f));
    explosion.sprite.setScale(4.f, 4.f);
    explosion.loadSound(assets.getSound("explosion_sound"));
}

void MotherShip::rotate()
{
    sprite.rotate(rotation_speed * dt.get().asSeconds());
}

void MotherShip::findClosestEnemy(std::vector<std::unique_ptr<Enemy>>& enemies, Equations& equations, unsigned int& score)
{
    for (auto& i : enemies)
        if (i.get()->locked_on)
        {
            if (equations.correct_result)
            {
                i.get()->locked_on = 0;
                i.get()->going_to_die = 1;
                equations.correct_result = 0;
                score++;
            }
            else
                target.setPosition(i.get()->sprite.getPosition());
            return;
        }
    float min_distance = INT_MAX;
    unsigned int min_i = INT_MAX;
    for (unsigned int i = 0; i < enemies.size(); i++)
    {
        float distance = mke::utility::distance(enemies[i].get()->sprite.getPosition(), {(float)win.getSize().x / 2, (float)win.getSize().y / 2});
        if (distance < min_distance && !enemies[i].get()->going_to_die)
        {
            min_distance = distance;
            min_i = i;
        }
    }
    if (min_i < enemies.size())
        enemies[min_i].get()->locked_on = 1;
}

void MotherShip::updateDamageTexture()
{
    if (HP >= 75.f)
        sprite.setTexture(assets.getTexture("mother_ship_100%"));
    else if (HP <= 75.f && HP >= 50.f)
        sprite.setTexture(assets.getTexture("mother_ship_75%"));
    else if (HP <= 50.f && HP >= 25.f)
        sprite.setTexture(assets.getTexture("mother_ship_50%"));
    else
        sprite.setTexture(assets.getTexture("mother_ship_25%"));

}

void MotherShip::update()
{
    rotate();
    updateDamageTexture();
}

void MotherShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!exploding)
    {
        target.draw(sprite, states);
        target.draw(this->target, states);
    }
    target.draw(explosion, states);
}
