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
    int high_score_level1;
    int high_score_level2;
    int high_score_level3;
    int high_score_level4;
    void saveDoc(std::string filename);
};

#endif
