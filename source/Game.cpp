#include "Game.h"

Game::Game() :
    win(sf::VideoMode(1920, 1080), "Space Math", sf::Style::Fullscreen),
    assets(win),
    random(time(0)),
    game_settings("data/data.dat")
{
    win.setFramerateLimit(60);
    loadAssets();
    setupFpsCounter();
    states.push(std::make_unique<MainMenuState>(*this));
}

void Game::loadAssets()
{
    assets.loadFont("font", "assets/fonts/nulshock bd.ttf");

    assets.loadTexture("background1", "assets/backgrounds/purple_nebula.png");
    assets.loadTexture("background2", "assets/backgrounds/blue_nebula.png");
    assets.loadTexture("background3", "assets/backgrounds/pink_nebula.png");
    assets.loadTexture("background4", "assets/backgrounds/white_nebula.png");

    assets.loadTexture("button_pressed", "assets/buttons/button_pressed.png");
    assets.loadTexture("button_released", "assets/buttons/button_released.png");

    assets.loadTexture("explosion_texture", "assets/effects/explosion.png");
    assets.loadSound("explosion_sound", "assets/sounds/explosion.wav");

    assets.loadTexture("health_bar_empty", "assets/progress_bars/progress_fill_blue.png");
    assets.loadTexture("health_bar_fill", "assets/progress_bars/progress_fill_lightblue.png");

    assets.loadTexture("dove_enemy", "assets/spaceships/Dove.png");
    assets.loadTexture("long_bullets", "assets/bullets/long_bullets.png");
}

void Game::setupFpsCounter()
{
    fps_counter.setFont(assets.getFont("font"));
    fps_counter.setCharacterSize(20);
    fps_counter.setPosition(win.getSize().x - fps_counter.getGlobalBounds().width - 50.f, 10.f);
}

void Game::winEvents()
{
    sf::Event event;
    while (win.pollEvent(event))
        switch (event.type)
        {
        case sf::Event::Closed:
            win.close();
            break;
        case sf::Event::KeyPressed:
            input.addPressedKey(event.key.code);
            break;
        case sf::Event::KeyReleased:
            input.addReleasedKey(event.key.code);
            break;
        case sf::Event::MouseButtonPressed:
            input.addPressedButton(event.mouseButton.button);
            break;
        case sf::Event::MouseButtonReleased:
            input.addReleasedButton(event.mouseButton.button);
            break;
        default:
            break;
        }
    if (input.isKeyReleased(sf::Keyboard::F))
        showing_fps = showing_fps ? 0 : 1;
}

void Game::run()
{
    while (win.isOpen())
    {
        input.update();
        dt.update();
        fps_counter.setString(std::to_string((int)(1.f / dt.get().asSeconds())));
        winEvents();
        states.top().update();
        if (states.states_just_changed)
        {
            states.states_just_changed = 0;
            continue;
        }
        win.clear();
        states.top().render();
        if (showing_fps)
            win.draw(fps_counter);
        win.display();
    }
}
