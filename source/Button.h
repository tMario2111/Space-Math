#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"

class Button : public sf::Drawable
{
public:
    Button();
    sf::Sprite body;
    sf::Text text;
    void setTextures(sf::Texture& base_texture, sf::Texture& selected_texture);
    void setFonts(sf::Font& base_font, sf::Font& selected_font);
    bool selected(sf::RenderWindow& win);
    void centerTextToBody();
    void setOriginsToCenter();
    void setupText(sf::Text& text, sf::Font& font, unsigned int character_size, std::string str, sf::Color color);
private:
    sf::Texture* base_texture;
    sf::Texture* selected_texture;
    sf::Font* base_font;
    sf::Font* selected_font;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
