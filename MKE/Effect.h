#ifndef EFFECT_H
#define EFFECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#include "AssetManager.h"

namespace mke
{
class Effect : public sf::Drawable
{
public:
    Effect(mke::AssetManager& assets);
    sf::Sprite sprite;
    void loadSpriteSheet(sf::Texture& sprite_sheet, sf::Vector2i size);
    void setSoundBufferName(std::string name);
    void setDuration(sf::Time duration);
    sf::Time getDuration();
    void run(sf::Time dt);
    bool isDone();
    bool running = 0;
    void restart();
private:
    mke::AssetManager& assets;
    sf::Texture* sprite_sheet;
    std::string sound_buffer_name;
    bool sound_played = 0;
    sf::Vector2i size;
    sf::Vector2i frame_size;
    sf::Time duration;
    sf::Time clock = sf::seconds(0.f);
    unsigned int current_frame;
    bool done = 0;
    sf::IntRect getIntRect(sf::Vector2i coords);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
}

#endif
