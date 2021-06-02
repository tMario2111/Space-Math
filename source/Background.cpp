#include "Background.h"

Background::Background(sf::RenderWindow& win) :
    verts(sf::Quads, 4)
{
    verts[0].position = sf::Vector2f(0, 0);
    verts[1].position = sf::Vector2f(win.getSize().x, 0);
    verts[2].position = sf::Vector2f(win.getSize().x, win.getSize().y);
    verts[3].position = sf::Vector2f(0, win.getSize().y);
}

void Background::setTexture(sf::Texture& texture)
{
    this->texture = &texture;
    this->texture->setRepeated(1);
    for (unsigned int i = 0; i < verts.getVertexCount(); i++)
        verts[i].texCoords = verts[i].position;
}

void Background::update(sf::Time dt)
{
    for (unsigned int i = 0; i < verts.getVertexCount(); i++)
        verts[i].texCoords = sf::Vector2f(verts[i].texCoords.x, verts[i].texCoords.y - speed * dt.asSeconds());
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.texture = texture;
    target.draw(verts, states);
}
