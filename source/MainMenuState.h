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
    sf::Text high_score;
    const float BUTTON_MARGIN = 50.f;
    Button start;
    Button settings;
    Button exit;
    void setupBackground();
    void setupTitle();
    void setupButtons();
};

#endif
