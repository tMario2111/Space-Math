#include "AssetManager.h"

namespace mke
{
AssetManager::AssetManager(sf::RenderWindow& win) :
    win(win)
{

}

void AssetManager::loadTexture(std::string name, std::string filename)
{
    if (textures.count(name) != 0)
        return;
    sf::Texture texture;
    if (!texture.loadFromFile(filename))
        win.close();
    textures[name] = texture;
}

void AssetManager::loadTexture(std::string name, sf::Texture& texture)
{
    if (textures.count(name) != 0)
        return;
    textures[name] = texture;
}

void AssetManager::unloadTexture(std::string name)
{
    textures.erase(name);
}

sf::Texture& AssetManager::getTexture(std::string name)
{
    return textures[name];
}

void AssetManager::loadFont(std::string name, std::string filename)
{
    if (fonts.count(name) != 0)
        return;
    sf::Font font;
    if (!font.loadFromFile(filename))
        win.close();
    fonts[name] = font;
}

void AssetManager::loadFont(std::string name, sf::Font& font)
{
    if (fonts.count(name) != 0)
        return;
    fonts[name] = font;
}

void AssetManager::unloadFont(std::string name)
{
    fonts.erase(name);
}

sf::Font& AssetManager::getFont(std::string name)
{
    return fonts[name];
}

void AssetManager::loadSound(std::string name, std::string filename)
{
    if (sounds.count(name) != 0)
        return;
    if (!sounds[name].sound_buffer.loadFromFile(filename))
        win.close();
    sounds[name].sound.setBuffer(sounds[name].sound_buffer);
}

void AssetManager::unloadSound(std::string name)
{
    sounds.erase(name);
}

sf::Sound& AssetManager::getSound(std::string name)
{
    return sounds[name].sound;
}
}
