#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include "../tinyxml2.h"
#include <string>

class GameSettings
{
public:
    GameSettings(std::string filename);
    tinyxml2::XMLDocument doc;
    int game_volume;
    int music_volume;
    int high_score;
    void saveDoc(std::string filename);
};

#endif
