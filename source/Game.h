#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"
#include <ctime>
#include "GameSettings.h"

#include "MainMenuState.h"

class Game
{
public:
    Game();
    sf::RenderWindow win;
    mke::Input input;
    mke::AssetManager assets;
    mke::DeltaTime dt;
    mke::StateMachine states;
    mke::Random random;
    sf::Text fps_counter;
    GameSettings game_settings;
    bool showing_fps = 0;
    void run();
private:
    void setupWin();
    void loadAssets();
    void setupFpsCounter();
    void winEvents();
};

#endif
