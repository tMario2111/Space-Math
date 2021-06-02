#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

namespace mke
{
class AssetManager
{
public:
    AssetManager(sf::RenderWindow& win);
    void loadTexture(std::string name, std::string filename);
    void loadTexture(std::string name, sf::Texture& texture);
    void unloadTexture(std::string name);
    sf::Texture& getTexture(std::string name);
    void loadFont(std::string name, std::string filename);
    void loadFont(std::string name, sf::Font& font);
    void unloadFont(std::string name);
    sf::Font& getFont(std::string name);
    void loadSound(std::string name, std::string filename);
    void unloadSound(std::string name);
    sf::Sound& getSound(std::string name);
private:
    sf::RenderWindow& win;
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    struct SoundWithBuffer
    {
        sf::Sound sound;
        sf::SoundBuffer sound_buffer;
    };
    std::unordered_map<std::string, SoundWithBuffer> sounds;
};
}

#endif
