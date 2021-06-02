#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

class Background : public sf::Drawable
{
public:
    Background(sf::RenderWindow& win);
    float speed = 1;
    void setTexture(sf::Texture& texture);
    void update(sf::Time dt);
private:
    sf::VertexArray verts;
    sf::Texture* texture;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
