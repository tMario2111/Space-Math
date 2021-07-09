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

void AssetManager::loadSoundBuffer(std::string name, std::string filename)
{
    if (sound_buffers.count(name) != 0)
        return;
    if (!sound_buffers[name].loadFromFile(filename))
        win.close();
}

void AssetManager::unloadSoundBuffer(std::string name)
{
    sound_buffers.erase(name);
}

sf::Sound* AssetManager::playSound(std::string buffer_name)
{
    sf::Sound* sound = new sf::Sound;
    sound->setBuffer(sound_buffers[buffer_name]);
    sound->setVolume(sound_volume);
    sound->play();
    sounds.push_back(sound);
    return sound;
}

void AssetManager::update()
{
    for (int i = 0; i < (int)sounds.size(); i++)
        if (sounds[i]->getStatus() == sf::Sound::Stopped)
        {
            delete sounds[i];
            sounds.erase(sounds.begin() + i--);
        }
}
}
