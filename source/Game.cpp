#include "Game.h"

Game::Game() :
    win(sf::VideoMode(1920, 1080), "Space Math", sf::Style::Fullscreen),
    assets(win),
    random(time(0)),
    game_settings("data/data.dat")
{
    win.setFramerateLimit(60);
    assets.loadFont("font", "assets/fonts/nulshock bd.ttf");
    setupFpsCounter();
    states.push(std::make_unique<MainMenuState>(*this));
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
