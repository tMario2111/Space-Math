#include "GameSettings.h"

GameSettings::GameSettings(std::string filename)
{
    doc.LoadFile(filename.c_str());
    doc.FirstChildElement("settings")->FirstChildElement("game_volume")->QueryIntText(&game_volume);
    doc.FirstChildElement("settings")->FirstChildElement("music_volume")->QueryIntText(&music_volume);
    doc.FirstChildElement("high_scores")->FirstChildElement("level1")->QueryIntText(&high_score_level1);
    doc.FirstChildElement("high_scores")->FirstChildElement("level2")->QueryIntText(&high_score_level2);
    doc.FirstChildElement("high_scores")->FirstChildElement("level3")->QueryIntText(&high_score_level3);
    doc.FirstChildElement("high_scores")->FirstChildElement("level4")->QueryIntText(&high_score_level4);
}

void GameSettings::saveDoc(std::string filename)
{
    doc.FirstChildElement("settings")->FirstChildElement("game_volume")->SetText(std::to_string(game_volume).c_str());
    doc.FirstChildElement("settings")->FirstChildElement("music_volume")->SetText(std::to_string(music_volume).c_str());
    doc.FirstChildElement("high_scores")->FirstChildElement("level1")->SetText(std::to_string(high_score_level1).c_str());
    doc.FirstChildElement("high_scores")->FirstChildElement("level2")->SetText(std::to_string(high_score_level2).c_str());
    doc.FirstChildElement("high_scores")->FirstChildElement("level3")->SetText(std::to_string(high_score_level3).c_str());
    doc.FirstChildElement("high_scores")->FirstChildElement("level4")->SetText(std::to_string(high_score_level4).c_str());
    doc.SaveFile(filename.c_str());
}
