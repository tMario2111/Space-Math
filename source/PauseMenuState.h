#ifndef PAUSEMENUSTATE_H
#define PAUSEMENUSTATE_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"

#include "Game.h"
#include "Button.h"
#include "Background.h"
#include "SettingsState.h"

class Game;

class PauseMenuState : public mke::State
{
public:
    PauseMenuState(Game& game, sf::Image background_texture, Background& background);
    void update();
    void render();
private:
    Game& game;
    Background& background;
    sf::Texture background_texture;
    sf::Sprite background_sprite;
    const float BUTTON_MARGIN = 80.f;
    Button resume;
    Button settings;
    Button main_menu;
    void setupButtons();
};

#endif
