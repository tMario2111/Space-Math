#ifndef ACHIEVEMENTSSTATE_H
#define ACHIEVEMENTSSTATE_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"

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
};

#endif
