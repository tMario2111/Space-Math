#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"
#include <thread>
#include <string>
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
    bool assets_loaded = 0;
    std::thread assets_thread;
    sf::Text loading_text;
    float loading_text_dots = 0.f;
    void setupWin();
    void setupLoadingText();
    void loadAssets();
    void setupFpsCounter();
    void winEvents();
    void updateLoadingText();
};

#endif
