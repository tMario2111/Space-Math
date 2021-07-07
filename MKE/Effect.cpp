#include "Effect.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace mke
{
Effect::Effect()
{

}

sf::IntRect Effect::getIntRect(sf::Vector2i coords)
{
    sf::IntRect rect;
    rect.left = coords.x * frame_size.x;
    rect.top = coords.y * frame_size.y;
    rect.width = frame_size.x;
    rect.height = frame_size.y;
    return rect;
}

void Effect::loadSpriteSheet(sf::Texture& sprite_sheet, sf::Vector2i size)
{
    current_frame = 0;
    this->sprite_sheet = &sprite_sheet;
    this->size = size;
    frame_size.x = sprite_sheet.getSize().x / size.x;
    frame_size.y = sprite_sheet.getSize().y / size.y;
    sprite.setTexture(sprite_sheet);
    sprite.setTextureRect(getIntRect(sf::Vector2i(current_frame % size.x, current_frame / size.x)));
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(-1000, -1000);
}

void Effect::loadSound(sf::Sound& sound)
{
    this->sound = &sound;
}

void Effect::setDuration(sf::Time duration)
{
    this->duration = duration;
}

bool Effect::isDone()
{
    return done;
}

void Effect::restart()
{
    done = 0;
    current_frame = 0;
    sound_played = 0;
}

void Effect::run(sf::Time dt)
{
    running = 1;
    clock += dt;
    if (!sound_played)
    {
        sound->play();
        sound_played = 1;
    }
    if (!done && clock >= sf::seconds(duration.asSeconds() / (size.x * size.y)))
    {
        if (current_frame == size.x * size.y - 1)
        {
            running = 0;
            done = 1;
            sound->stop();
            return;
        }
        current_frame++;
        sprite.setTextureRect(getIntRect(sf::Vector2i(current_frame % size.x, current_frame / size.x)));
        clock = sf::seconds(0.f);
    }
}

void Effect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite, states);
}
}
