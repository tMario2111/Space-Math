#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"
#include <cmath>

class ProgressBar : public sf::Drawable
{
public:
    ProgressBar(sf::Font& font);
    bool filled = 0;
    void setTextures(sf::Texture& t_empty, sf::Texture& t_fill);
    void setPosition(sf::Vector2f position);
    void setProgress(float percentage);
    bool reversed = 0;
private:
    sf::Sprite empty_bar;
    sf::Sprite filled_bar;
    sf::Text text;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
