#include "Game.h"

Game::Game() :
    win(sf::VideoMode::getDesktopMode(), "Space Math", sf::Style::Fullscreen),
    assets(win),
    random(time(0)),
    game_settings("data/data.dat")
{
    setupWin();
    assets.loadFont("font", "assets/fonts/nulshock bd.ttf");
    setupLoadingText();
    setupFpsCounter();
    assets_thread = std::thread(&Game::loadAssets, this);
}

void Game::setupWin()
{
    win.setFramerateLimit(60);
    win.setVerticalSyncEnabled(1);
    sf::Image icon;
    icon.loadFromFile("assets/icons/SpaceMathIcon.png");
    win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Game::setupLoadingText()
{
    loading_text.setFont(assets.getFont("font"));
    loading_text.setCharacterSize(60);
    loading_text.setString("LOADING");
    mke::utility::centerBothAxes(loading_text, 0, win.getSize().x, 0, win.getSize().y);
}

void Game::loadAssets()
{
    sf::Context context;

    assets.loadTexture("background1", "assets/backgrounds/purple_nebula.png");
    assets.loadTexture("background2", "assets/backgrounds/blue_nebula.png");
    assets.loadTexture("background3", "assets/backgrounds/pink_nebula.png");
    assets.loadTexture("background4", "assets/backgrounds/white_nebula.png");

    assets.loadTexture("button_pressed", "assets/buttons/button_pressed.png");
    assets.loadTexture("button_released", "assets/buttons/button_released.png");

    assets.loadTexture("explosion_texture", "assets/effects/explosion.png");
    assets.loadSoundBuffer("explosion_sound", "assets/sounds/explosion.wav");
    assets.loadTexture("fire_circle","assets/effects/fire_circle.png");
    assets.getTexture("fire_circle").setSmooth(true);

    assets.loadTexture("health_bar_empty", "assets/progress_bars/progress_empty.png");
    assets.loadTexture("health_bar_fill", "assets/progress_bars/progress_fill.png");

    assets.loadTexture("mother_ship_100%", "assets/spaceships/mother_ship_100.png");
    assets.loadTexture("mother_ship_75%", "assets/spaceships/mother_ship_75.png");
    assets.loadTexture("mother_ship_50%", "assets/spaceships/mother_ship_50.png");
    assets.loadTexture("mother_ship_25%", "assets/spaceships/mother_ship_25.png");
    assets.loadTexture("target", "assets/misc/target.png");

    assets.loadTexture("dove_enemy", "assets/spaceships/Dove.png");
    assets.loadTexture("long_bullets", "assets/bullets/long_bullets.png");
    assets.loadTexture("lighter_enemy", "assets/spaceships/Ligher.png");
    assets.loadTexture("paranoid_enemy", "assets/spaceships/Paranoid.png");
    assets.loadTexture("rocket_bullet", "assets/bullets/rocket_green.png");
    assets.loadTexture("ufo_enemy", "assets/spaceships/UFO.png");
    assets.loadTexture("star_bullet", "assets/bullets/star.png");

    assets.loadTexture("panel", "assets/misc/panel.png");
    assets.loadTexture("star", "assets/misc/star.png");

    assets_loaded = 1;
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

void Game::updateLoadingText()
{
    loading_text_dots += 10 * dt.get().asSeconds();
    loading_text_dots = loading_text_dots > 4.f ? 0.f : loading_text_dots;
    std::string str = "LOADING";
    for (int i = 0; i < (int)loading_text_dots; i++)
        str.push_back('.');
    loading_text.setString(str);
}

void Game::run()
{
    while (win.isOpen())
    {
        if (states.size() == 0 && assets_loaded)
        {
            assets_thread.detach();
            states.push(std::make_unique<MainMenuState>(*this));
        }

        input.update();
        dt.update();
        assets.update();
        fps_counter.setString(std::to_string((int)(1.f / dt.get().asSeconds())));

        winEvents();

        if (!assets_loaded)
            updateLoadingText();

        if (states.size() > 0)
            states.top().update();

        if (states.states_just_changed)
        {
            states.states_just_changed = 0;
            continue;
        }

        win.clear();
        if (states.size() > 0)
            states.top().render();
        if (showing_fps)
            win.draw(fps_counter);
        if (!assets_loaded)
            win.draw(loading_text);
        win.display();
    }
}
