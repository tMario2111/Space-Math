#ifndef EFFECT_H
#define EFFECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace mke
{
class Effect : public sf::Drawable
{
public:
    Effect();
    sf::Sprite sprite;
    void loadSpriteSheet(sf::Texture& sprite_sheet, sf::Vector2i size);
    void loadSound(sf::Sound& sound);
    void setDuration(float duration);
    void run(float dt);
    bool isDone();
    void restart();
private:
    sf::Texture* sprite_sheet;
    sf::Sound* sound;
    bool sound_played = 0;
    sf::Vector2i size;
    sf::Vector2i frame_size;
    float duration;
    float clock = 0;
    unsigned int current_frame;
    bool done = 0;
    sf::IntRect getIntRect(sf::Vector2i coords);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
}

#endif
