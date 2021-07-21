#ifndef MULTIPLAYERGAMEOVERSTATE_H
#define MULTIPLAYERGAMEOVERSTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "../MKE/MKE.h"
#include <thread>
#include <string>

#include "Background.h"
#include "Game.h"
#include "Button.h"
#include "GameState.h"
#include "Networking.h"
#include "MultiplayerGameState.h"

class Game;

class MultiplayerGameOverState : public mke::State
{
public:
    MultiplayerGameOverState(Game& game, Background& background, Networking::UserType winner, sf::Image background_texture);
    void update();
    void render();
private:
    Game& game;
    Background& background;
    Networking::UserType winner;
    sf::Texture background_texture;
    sf::Sprite background_sprite;
    sf::Text game_over_text;
    const float BUTTON_MARGIN = 50.f;
    Button main_menu;
    Button reset;
    sf::Sprite loader;
    mke::Animation loader_animation;
    bool waiting_reset_confirmation = 0;
    bool reset_confirmed = 0;
    std::thread reset_thread;
    void setupText();
    void setupButtons();
    void setupLoader();
    void checkReset();
};

#endif
