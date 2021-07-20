#include "ProgressBar.h"

ProgressBar::ProgressBar(sf::Font& font)
{
    text.setFont(font);
    text.setCharacterSize(22);
}

void ProgressBar::setTextures(sf::Texture& t_empty, sf::Texture& t_fill)
{
    empty_bar.setTexture(t_empty);
    filled_bar.setTexture(t_fill);
    filled_bar.setTextureRect(sf::IntRect(0, 0, 0, t_fill.getSize().y));
}

void ProgressBar::setPosition(sf::Vector2f position)
{
    empty_bar.setPosition(position.x - empty_bar.getGlobalBounds().width / 2, position.y - empty_bar.getGlobalBounds().height / 2);
    filled_bar.setPosition(empty_bar.getPosition());
}

void ProgressBar::setProgress(float percentage)
{
    percentage -= 0.00001f; /// FEATURE
    if (percentage < 0.f)
        percentage = 0.f;
    if ((percentage == 100.f && !reversed) || (percentage == 0.f && reversed))
        filled = 1;
    else
        filled = 0;
    sf::Vector2u size = filled_bar.getTexture()->getSize();
    filled_bar.setTextureRect(sf::IntRect(0, 0, 116 + percentage / 100.f * (size.x - 135), size.y));

    text.setString(std::to_string((int)std::ceil(percentage)) + "%");
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    sf::Vector2f margin;
    margin.x = empty_bar.getGlobalBounds().left;
    margin.y = empty_bar.getGlobalBounds().top;
    mke::utility::centerBothAxes(text, margin.x + 12, margin.x + 96, margin.y + 12, margin.y + 93);
}

sf::Vector2f ProgressBar::getSize()
{
    return sf::Vector2f(empty_bar.getGlobalBounds().width, empty_bar.getGlobalBounds().height);
}

void ProgressBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!filled)
    {
        target.draw(empty_bar, states);
        target.draw(filled_bar, states);
        target.draw(text, states);
    }
}
