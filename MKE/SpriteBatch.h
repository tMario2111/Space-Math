#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include <SFML/Graphics.hpp>

namespace mke
{
class SpriteBatch : public sf::Drawable
{
public:
    SpriteBatch();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void append(sf::Sprite& sprite);
    void clear();
private:
    sf::VertexArray batch;
    sf::Sprite* sprite;
};
}

#endif
