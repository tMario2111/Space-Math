#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"
#include <string>

class TextBox : public sf::Drawable
{
public:
    TextBox(sf::RenderWindow& win, mke::Input& input, sf::Font& font, sf::Vector2f size, unsigned int character_size, std::string hint_string);
    sf::RectangleShape body;
    bool digits_only = 0;
    unsigned int characters_limit = INT_MAX;
    std::string getContents();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update();
private:
    sf::RenderWindow& win;
    mke::Input& input;
    sf::Text contents;
    sf::Text hint;
    const char BACKSPACE = 8;
    const float HINT_MARGIN = 10.f;
};

#endif
