#ifndef ACHIEVEMENTSSTATE_H
#define ACHIEVEMENTSSTATE_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"
#include "../tinyxml2.h"
#include <string>
#include <vector>

#include "Game.h"
#include "Background.h"

class AchievementsState : public mke::State
{
public:
    AchievementsState(Game& game, Background& background);
    void update();
    void render();
private:
    Game& game;
    Background& background;
    std::vector<std::pair<sf::Text, sf::Text>> achievements;
    void setupAchievements();
};

#endif
