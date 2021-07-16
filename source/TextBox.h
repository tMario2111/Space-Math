#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"
#include <string>

class TextBox : public sf::Drawable
{
public:
    TextBox(sf::Vector2f size, std::string message, sf::Font& font, int character_size);
    sf::RectangleShape body;
    sf::Text message;
    int getContentsAsInt();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update(char text_key, sf::RenderWindow* win);
private:
    const char BACKSPACE = 8;
    sf::Text contents_T;
    std::string contents_str;
};

#endif
