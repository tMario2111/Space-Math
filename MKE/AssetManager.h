#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <vector>

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
    void loadSoundBuffer(std::string name, std::string filename);
    void unloadSoundBuffer(std::string name);
    sf::Sound* playSound(std::string buffer_name);
    float sound_volume = 100.f;
    void update();
private:
    sf::RenderWindow& win;
    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;
    std::unordered_map<std::string, sf::SoundBuffer> sound_buffers;
    std::vector<sf::Sound*> sounds;
};
}

#endif
