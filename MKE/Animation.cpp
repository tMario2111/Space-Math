#include "Animation.h"

namespace mke
{
Animation::Animation(sf::Sprite& sprite) :
    sprite(sprite)
{

}

sf::IntRect Animation::getIntRect(sf::Vector2u coordinates)
{
    sf::IntRect rect;
    rect.left = coordinates.x * frame_size.x;
    rect.top = coordinates.y * frame_size.y;
    rect.width = frame_size.x;
    rect.height = frame_size.y;
    return rect;
}

void Animation::loadAtlas(sf::Texture& atlas, sf::Vector2u size)
{
    this->atlas = &atlas;
    frame_size.x = atlas.getSize().x / size.x;
    frame_size.y = atlas.getSize().y / size.y;
    sprite.setTexture(atlas);
}

void Animation::addFrame(sf::Vector2u coordinates, sf::Time duration)
{
    frames.push_back({coordinates, duration});
}

void Animation::setSpriteFrame(sf::Vector2u coordinates)
{
    sprite.setTextureRect(getIntRect(coordinates));
}

void Animation::run(sf::Time dt)
{
    clock += dt;
    if (clock >= frames[index].duration)
    {
        index++;
        if (index == frames.size())
            index = 0;
        clock = sf::seconds(0);
    }
    sprite.setTextureRect(getIntRect(frames[index].coordinates));
}
}
