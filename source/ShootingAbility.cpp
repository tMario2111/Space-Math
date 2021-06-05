#include "ShootingAbility.h"

ShootingAbility::ShootingAbility(sf::RenderWindow& win, mke::DeltaTime& dt) :
    win(win),
    dt(dt)
{

}

void ShootingAbility::setTexture(sf::Texture& texture)
{
    this->texture = &texture;
    texture_rect = sf::IntRect(0, 0, texture.getSize().x, texture.getSize().y);
}

void ShootingAbility::setTextureRect(sf::IntRect texture_rect)
{
    this->texture_rect = texture_rect;
}

void ShootingAbility::createBullet(sf::Vector2f position)
{
    sf::Sprite new_bullet;
    new_bullet.setTexture(*texture);
    new_bullet.setTextureRect(texture_rect);
    new_bullet.setPosition(position);
    new_bullet.setRotation(rotation + 90.f);
    new_bullet.setScale(scale);
    new_bullet.setOrigin(new_bullet.getLocalBounds().width / 2, new_bullet.getLocalBounds().height / 2);
    bullets.push_back(new_bullet);
}

void ShootingAbility::destroyBullets()
{
    for (unsigned int i = 0; i < bullets.size(); i++)
        if (bullets[i].getPosition().x <= -DESTROY_MARGIN || bullets[i].getPosition().x >= win.getSize().x + DESTROY_MARGIN ||
            bullets[i].getPosition().y <= -DESTROY_MARGIN || bullets[i].getPosition().y >= win.getSize().y + DESTROY_MARGIN)
            bullets.erase(bullets.begin() + i);
}

void ShootingAbility::movement()
{
    for (sf::Sprite& i : bullets)
    {
        sf::Vector2f velocity = {0, 0};
        velocity.x = bullet_speed * cos(mke::utility::toRad(rotation)) * dt.get().asSeconds();
        velocity.y = bullet_speed * sin(mke::utility::toRad(rotation)) * dt.get().asSeconds();
        i.move(velocity);
        i.rotate(rotation_speed * dt.get().asSeconds());
    }
}

void ShootingAbility::update(bool is_shooting, sf::Vector2f position)
{
    shooting_clock += dt.get().asSeconds();
    if (is_shooting && shooting_clock >= shooting_speed)
    {
        createBullet(position);
        shooting_clock = 0;
    }
    destroyBullets();
    movement();
}

void ShootingAbility::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}
