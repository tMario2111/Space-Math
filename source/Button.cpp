#include "Button.h"

Button::Button()
{

}

void Button::setupText(sf::Text& text, sf::Font& font, unsigned int character_size, std::string str, sf::Color color)
{
    text.setFont(font);
    text.setCharacterSize(character_size);
    text.setString(str);
    text.setFillColor(color);
}

void Button::setTextures(sf::Texture& base_texture, sf::Texture& selected_texture)
{
    this->base_texture = &base_texture;
    this->selected_texture = &selected_texture;
    body.setTexture(*this->base_texture);
}

void Button::setFonts(sf::Font& base_font, sf::Font& selected_font)
{
    this->base_font = &base_font;
    this->selected_font = &selected_font;
    text.setFont(base_font);
}

bool Button::selected(sf::RenderWindow& win)
{
    sf::FloatRect cursor;
    cursor.left = sf::Mouse::getPosition(win).x;
    cursor.top = sf::Mouse::getPosition(win).y;
    cursor.width = 1;
    cursor.height = 1;
    if (cursor.intersects(body.getGlobalBounds()))
    {
        body.setTexture(*selected_texture);
        text.setFont(*selected_font);
        centerTextToBody();
        text.setFillColor(sf::Color(199, 207, 221));
        text.move(0.f, 3.f);
        return 1;
    }
    text.setFillColor(sf::Color(255, 255, 255));
    text.move(0.f, -3.f);
    body.setTexture(*base_texture);
    text.setFont(*base_font);
    centerTextToBody();
    return 0;
}

void Button::centerTextToBody()
{
    sf::FloatRect rect = body.getGlobalBounds();
    mke::utility::centerXAxis(text, rect.left, rect.left + rect.width);
    mke::utility::centerYAxis(text, rect.top, rect.top + rect.height);
    mke::utility::centerBothAxes(text, rect.left, rect.left + rect.width, rect.top, rect.top + rect.height);
}

void Button::setOriginsToCenter()
{
    body.setOrigin(body.getLocalBounds().width / 2, body.getLocalBounds().height / 2);
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(body, states);
    target.draw(text, states);
}
