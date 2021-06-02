#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <SFML/Graphics.hpp>

class ProgressBar : public sf::Drawable
{
public:
    ProgressBar();
    bool filled = 0;
    void setTextures(sf::Texture& t_empty, sf::Texture& t_fill);
    void setPosition(sf::Vector2f position);
    void setProgress(float percentage);
    bool reversed = 0;
private:
    sf::Sprite empty_bar;
    sf::Sprite filled_bar;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
