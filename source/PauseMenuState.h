#ifndef PAUSEMENUSTATE_H
#define PAUSEMENUSTATE_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"

#include "Game.h"
#include "Button.h"

class Game;

class PauseMenuState : public mke::State
{
public:
    PauseMenuState(Game& game, sf::Image background_texture);
    void update();
    void render();
private:
    Game& game;
    sf::Texture background_texture;
    sf::Sprite background_sprite;
    const float BUTTON_MARGIN = 50.f;
    Button resume;
    Button main_menu;
    void setupButtons();
};

#endif
