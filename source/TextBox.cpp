#include "TextBox.h"

TextBox::TextBox(sf::Vector2f size, std::string message, sf::Font& font, int character_size) :
    body(size)
{
    this->message.setString(message);
    this->message.setFont(font);
    this->message.setCharacterSize(character_size);
    this->contents_T.setFont(font);
    this->contents_T.setCharacterSize(character_size);
    this->contents_T.setFillColor(sf::Color(0, 0, 0));
}

int TextBox::getContentsAsInt()
{
    if (contents_str.size())
    {
        if (!(contents_str.size() == 1 && contents_str[0] == '-'))
            return std::stoi(contents_str);
    }
    else
        return -1000;
}

void TextBox::update(char text_key, sf::RenderWindow* win)
{
    sf::Vector2i m_local_pos = sf::Mouse::getPosition(*win);
    sf::Vector2f m_global_pos = win->mapPixelToCoords(m_local_pos);
    sf::FloatRect mouse_cursor (m_global_pos.x, m_global_pos.y, 1, 1);
    if (mouse_cursor.intersects(body.getGlobalBounds()))
    {
        body.setFillColor(sf::Color(100, 100, 100));
        if (text_key != 0)
            if (text_key == BACKSPACE && contents_str.size())
                contents_str.pop_back();
            else if ((isdigit(text_key) || (text_key == '-' && contents_str.size() == 0)) && contents_str.size() < 3)
                contents_str += text_key;
    }
    else
        body.setFillColor(sf::Color(255, 255, 255));
    message.setPosition(body.getPosition().x - message.getGlobalBounds().width - 10.f, message.getPosition().y);
    mke::utility::centerYAxis(message, body.getPosition().y, body.getPosition().y + body.getSize().y);
    contents_T.setString(contents_str);
    mke::utility::centerBothAxes(contents_T, body.getPosition().x, body.getPosition().x + body.getSize().x,
                   body.getPosition().y, body.getPosition().y + body.getSize().y);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(body, states);
    target.draw(message, states);
    target.draw(contents_T, states);
}
