#include "TextBox.h"

TextBox::TextBox(sf::RenderWindow& win, mke::Input& input, sf::Font& font, sf::Vector2f size, unsigned int character_size, std::string hint_string) :
    body(size),
    win(win),
    input(input)
{
    contents.setFont(font);
    contents.setCharacterSize(character_size);
    contents.setFillColor(sf::Color(225, 225, 225));
    hint.setFont(font);
    hint.setCharacterSize(character_size);
    hint.setFillColor(sf::Color::White);
    hint.setString(hint_string);
    body.setOrigin(body.getLocalBounds().width / 2, body.getLocalBounds().height / 2);
    body.setFillColor(sf::Color(0, 0, 0, 100));
    body.setOutlineThickness(5.f);
    body.setOutlineColor(sf::Color(0, 0, 0, 200));
}

std::string TextBox::getContents()
{
    return contents.getString();
}

void TextBox::update()
{
    if (input.isButtonPressed(sf::Mouse::Left))
    {
        if (body.getGlobalBounds().contains(win.mapPixelToCoords(sf::Mouse::getPosition(win))))
        {
            selected = 1;
            body.setFillColor(sf::Color(100, 100, 100, 100));
        }
        else
        {
            selected = 0;
            body.setFillColor(sf::Color(0, 0, 0, 100));
        }
    }
    std::string contents_string = contents.getString();
    if (input.text_character != 0 && selected)
    {
        if (input.text_character == BACKSPACE)
        {
            if (contents_string.size() > 0)
                contents_string.pop_back();
        }
        else if (digits_only && contents_string.size() < characters_limit)
        {
            if (input.text_character >= '0' && input.text_character <= '9')
                contents_string.push_back(input.text_character);
        }
        else if (contents_string.size() < characters_limit)
            contents_string.push_back(input.text_character);
    }
    contents.setString(contents_string);
    mke::utility::centerBothAxes(hint, body.getGlobalBounds().left - hint.getGlobalBounds().width - HINT_MARGIN, body.getGlobalBounds().left,
                                 body.getGlobalBounds().top, body.getGlobalBounds().top + body.getGlobalBounds().height);
    mke::utility::centerBothAxes(contents, body.getGlobalBounds().left, body.getGlobalBounds().left + body.getGlobalBounds().width,
                                 body.getGlobalBounds().top, body.getGlobalBounds().top + body.getGlobalBounds().height);

}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(body, states);
    target.draw(hint, states);
    target.draw(contents, states);
}
