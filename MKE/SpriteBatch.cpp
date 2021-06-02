#include "SpriteBatch.h"

namespace mke
{
SpriteBatch::SpriteBatch() :
    batch(sf::Quads, 0)
{

}

void SpriteBatch::clear()
{
    batch.clear();
}

void SpriteBatch::append(sf::Sprite& sprite)
{
    sf::FloatRect texture_rect = static_cast<sf::FloatRect>(sprite.getTextureRect());
    this->sprite = &sprite;
    sf::Vertex verts[4];
    verts[0].texCoords = {texture_rect.left, texture_rect.top};
    verts[1].texCoords = {texture_rect.left + texture_rect.width, texture_rect.top};
    verts[2].texCoords = {texture_rect.left + texture_rect.width, texture_rect.top + texture_rect.height};
    verts[3].texCoords = {texture_rect.left, texture_rect.top + texture_rect.height};
    verts[0].position = sprite.getTransform().transformPoint(0, 0);
    verts[1].position = sprite.getTransform().transformPoint(texture_rect.width, 0);
    verts[2].position = sprite.getTransform().transformPoint(texture_rect.width, texture_rect.height);
    verts[3].position = sprite.getTransform().transformPoint(0, texture_rect.height);
    for (int i = 0; i < 4; i++)
        batch.append(verts[i]);
}

void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(batch, states);
}
}
