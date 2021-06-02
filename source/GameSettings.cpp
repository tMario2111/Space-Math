#include "GameSettings.h"

GameSettings::GameSettings(std::string filename)
{
    doc.LoadFile(filename.c_str());
    doc.FirstChildElement("settings")->FirstChildElement("game_volume")->QueryIntText(&game_volume);
    doc.FirstChildElement("settings")->FirstChildElement("music_volume")->QueryIntText(&music_volume);
    doc.FirstChildElement("high_score")->QueryIntText(&high_score);
}

void GameSettings::saveDoc(std::string filename)
{
    doc.FirstChildElement("settings")->FirstChildElement("game_volume")->SetText(std::to_string(game_volume).c_str());
    doc.FirstChildElement("settings")->FirstChildElement("music_volume")->SetText(std::to_string(music_volume).c_str());
    doc.FirstChildElement("high_score")->SetText(std::to_string(high_score).c_str());
    doc.SaveFile(filename.c_str());
}
