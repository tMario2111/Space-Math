#include "Enemy.h"

Enemy::Enemy(mke::AssetManager& assets, sf::RenderWindow& win, mke::DeltaTime& dt) :
    shooting_ability(win, dt),
    explosion(assets),
    assets(assets),
    win(win),
    dt(dt),
    animation(sprite)
{
    setupExplosion();
}

void Enemy::setupExplosion()
{
    explosion.loadSpriteSheet(assets.getTexture("explosion_texture"), sf::Vector2i(4, 4));
    explosion.setDuration(sf::seconds(0.5f));
    explosion.setSoundBufferName("explosion_sound");
}

