#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace mke
{
class Animation
{
public:
    Animation(sf::Sprite& sprite);
    void loadAtlas(sf::Texture& atlas, sf::Vector2u size);
    void addFrame(sf::Vector2u coordinates, sf::Time duration);
    void setSpriteFrame(sf::Vector2u coordinates);
    void reset();
    void run(sf::Time dt);
private:
    sf::Sprite& sprite;
    sf::Texture* atlas;
    sf::Vector2u frame_size;
    sf::Time clock;
    unsigned int index = 0;
    struct Frame
    {
        sf::Vector2u coordinates;
        sf::Time duration;
    };
    std::vector<Frame> frames;
    sf::IntRect getIntRect(sf::Vector2u coordinates);
};
}

#endif
