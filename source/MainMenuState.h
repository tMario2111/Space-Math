#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"
#include <vector>
#include <string>

#include "Game.h"
#include "LevelSelectState.h"
#include "SettingsState.h"
#include "Button.h"
#include "Background.h"
#include "AchievementsState.h"
#include "MultiplayerConnectionState.h"

class Game;

class MainMenuState : public mke::State
{
public:
    MainMenuState(Game& game);
    void update();
    void render();
private:
    Game& game;
    Background background;
    sf::Text title;
    const float BUTTON_MARGIN = 40.f;
    Button start;
    Button multiplayer;
    Button achievements;
    Button settings;
    Button exit;
    sf::Text credits;
    void setupBackground();
    void setupTitle();
    void setupButtons();
    void setupCredits();
};

#endif
