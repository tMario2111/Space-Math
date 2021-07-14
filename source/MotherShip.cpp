#include "MotherShip.h"

MotherShip::MotherShip(mke::AssetManager& assets, sf::RenderWindow& win, mke::DeltaTime& dt) :
    explosion(assets),
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
    explosion.setSoundBufferName("explosion_sound");
}

void MotherShip::rotate()
{
    sprite.rotate(rotation_speed * dt.get().asSeconds());
}

void MotherShip::updateTargeting(std::vector<std::unique_ptr<Enemy>>& enemies, Equations& equations, unsigned int& score)
{
    bool ok = 0;
    if (equations.correct_result)
    {
        ok = 1;
        score++;
        equations.correct_result = 0;
    }
    for (auto& i : enemies)
        if (i.get()->locked_on)
        {
            if (ok)
            {
                i.get()->locked_on = 0;
                i.get()->going_to_die = 1;
            }
            else
                target.setPosition(i.get()->sprite.getPosition());
            return;
        }
    ok = 0;
    for (auto& i : enemies)
    {
        if (!i.get()->going_to_die)
        {
            i.get()->locked_on = 1;
            ok = 1;
            break;
        }
    }
    if (!ok)
        target.setPosition(-10000.f, -10000.f);
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
