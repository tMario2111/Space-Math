#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"
#include "../tinyxml2.h"

#include "Background.h"
#include "Game.h"
#include "Button.h"
#include "GameState.h"

class Game;

class GameOverState : public mke::State
{
public:
    GameOverState(Game& game, sf::Image background_texture, int score, unsigned int level, Background& background);
    void update();
    void render();
private:
    Game& game;
    Background& background;
    int score;
    unsigned int level;
    sf::Texture background_texture;
    sf::Sprite background_sprite;
    sf::Text game_over_text;
    sf::Text high_score;
    const float BUTTON_MARGIN = 50.f;
    Button main_menu;
    Button reset;
    void checkAchievements();
    void setupText();
    void setupButtons();
};

#endif
