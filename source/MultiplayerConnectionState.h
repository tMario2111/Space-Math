#ifndef MULTIPLAYERCONNECTIONSTATE_H
#define MULTIPLAYERCONNECTIONSTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "../MKE/MKE.h"
#include "Background.h"
#include "Button.h"
#include "Game.h"
#include "TextBox.h"

class Game;

class MultiplayerConnectionState : public mke::State
{
public:
    MultiplayerConnectionState(Game& game, Background& background);
    void update();
    void render();
private:
    const float MARGIN = 50.f;
    Game& game;
    Background& background;
    Button back_;
    sf::Text host_title;
    sf::Text connect_title;
    TextBox host_name;
    TextBox host_port;
    TextBox client_name;
    TextBox client_port;
    TextBox client_adress;
    Button connect_host;
    Button connect_client;
    bool waiting_host_connection = 0;
    bool waiting_client_connection = 0;
    sf::Sprite loader;
    mke::Animation loader_animation;
    void setupTexts();
    void setupTextBoxes();
    void setupButtons();
    void setupLoader();
};

#endif
