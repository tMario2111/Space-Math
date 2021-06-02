#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/Graphics.hpp>
#include <cmath>

namespace mke
{
namespace utility
{
const double PI = 3.14159;

int toDeg(float rad);

float toRad(int deg);

float getRotationToMouse(sf::Vector2f pos, sf::RenderWindow& win);

float distance(sf::Vector2f A, sf::Vector2f B);

void centerXAxis(sf::Text& text, float x1, float x2);
void centerYAxis(sf::Text& text, float y1, float y2);
void centerBothAxes(sf::Text& text, float x1, float x2, float y1, float y2);
}
}

#endif
