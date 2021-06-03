#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"

#include "Background.h"
#include "Game.h"
#include "Button.h"

class Game;

class SettingsState : public mke::State
{
public:
    SettingsState(Game& game, Background& background);
    void update();
    void render();
private:
    Game& game;
    Background& background;
    const float BUTTON_MARGIN = 50.f;
    sf::Text game_volume_text;
    sf::Text game_volume;
    sf::Text music_volume_text;
    sf::Text music_volume;
    sf::Text sqrt_key;
    sf::Text clear_key;
    sf::Text show_fps_key;
    Button game_volume_l, game_volume_r, music_volume_l, music_volume_r;
    void setupTexts();
    void setupButtons();
};

#endif
