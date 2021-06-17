#ifndef LEVELSELECTSTATE_H
#define LEVELSELECTSTATE_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"

#include "Game.h"
#include "GameState.h"
#include "Background.h"
#include "Button.h"

class Game;

class LevelSelectState : public mke::State
{
public:
    LevelSelectState(Game& game, Background& background);
    void update();
    void render();
private:
    Game& game;
    Background& background;
    const float BUTTON_MARGIN = 50.f;
    sf::Text title;
    sf::Text high_score_level1;
    sf::Text high_score_level2;
    sf::Text high_score_level3;
    sf::Text high_score_level4;
    sf::Text instructions;
    Button level1;
    Button level2;
    Button level3;
    Button level4;
    void setupTitle();
    void setupHighScores();
    void setupInstructions();
    void setupButtons();
};

#endif
