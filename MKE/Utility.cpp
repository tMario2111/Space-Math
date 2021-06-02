#include "Utility.h"

namespace mke
{
namespace utility
{
int toDeg(float rad)
{
    return rad * 180 / PI;
}

float toRad(int deg)
{
    return deg * PI / 180;
}
float getRotationToMouse(sf::Vector2f pos, sf::RenderWindow& win)
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(win);
    return toDeg(atan2(mouse_pos.y - pos.y, mouse_pos.x - pos.x));
}
float distance(sf::Vector2f A, sf::Vector2f B)
{
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}
void centerXAxis(sf::Text& text, float x1, float x2)
{
    sf::Vector2f position;
    position.x = (x1 + x2) / 2 - (text.getGlobalBounds().width / 2 - text.getOrigin().x * text.getScale().x) - text.getLocalBounds().left * text.getScale().x;
    position.y = text.getPosition().y;
    text.setPosition(position);
}

void centerYAxis(sf::Text& text, float y1, float y2)
{
    sf::Vector2f position;
    position.x = text.getPosition().x;
    position.y = (y1 + y2) / 2 - (text.getGlobalBounds().height / 2 - text.getOrigin().y * text.getScale().y) - text.getLocalBounds().top * text.getScale().y;
    text.setPosition(position);
}

void centerBothAxes(sf::Text& text, float x1, float x2, float y1, float y2)
{
    centerXAxis(text, x1, x2);
    centerYAxis(text, y1, y2);
}
}
}
