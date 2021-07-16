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
    Game& game;
    Background& background;
    TextBox test;
    Button back_;
    void setupButtons();


};

#endif
