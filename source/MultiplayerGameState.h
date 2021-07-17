#ifndef MULTIPLAYERGAMESTATE_H
#define MULTIPLAYERGAMESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "../MKE/MKE.h"

#include "Game.h"
#include "Networking.h"
#include "Background.h"
#include "MotherShip.h"

class Game;

class MultiplayerGameState : public mke::State
{
public:
    MultiplayerGameState(Game& game, Background& background, unsigned int level);
    void update();
    void render();
private:
    Game& game;
    Background& background;
    unsigned int level;
    MotherShip host_ship;
    MotherShip client_ship;
    void syncRandomSeed();
    void setupShips();
};

#endif
