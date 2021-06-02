#include "MainMenuState.h"

MainMenuState::MainMenuState(Game& game) :
    game(game),
    background(game.win)
{
    name = "MainMenu";
    setupBackground();
    setupTitle();
    setupButtons();
}

void MainMenuState::setupBackground()
{
    game.assets.loadTexture("background1", "assets/backgrounds/purple_nebula.png");
    game.assets.loadTexture("background2", "assets/backgrounds/blue_nebula.png");
    game.assets.loadTexture("background3", "assets/backgrounds/pink_nebula.png");
    game.assets.loadTexture("background4", "assets/backgrounds/white_nebula.png");
    std::vector<std::string> numbers = {"1", "2", "3", "4"};
    std::random_shuffle(numbers.begin(), numbers.end());
    background.setTexture(game.assets.getTexture("background" + numbers[0]));
    background.speed = 25.f;
}

void MainMenuState::setupTitle()
{
    title.setFont(game.assets.getFont("font"));
    title.setCharacterSize(60);
    title.setString("SPACE MATH");
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 4);

    high_score.setFont(game.assets.getFont("font"));
    high_score.setCharacterSize(30);
    high_score.setString("HIGH SCORE: " + std::to_string(game.game_settings.high_score));
    high_score.setOrigin(high_score.getLocalBounds().width / 2, high_score.getLocalBounds().height / 2);
    high_score.setPosition(game.win.getSize().x / 2 + title.getGlobalBounds().width / 2, game.win.getSize().y / 4 + BUTTON_MARGIN);
}

void MainMenuState::setupButtons()
{
    game.assets.loadTexture("button_pressed", "assets/buttons/button_pressed.png");
    game.assets.loadTexture("button_released", "assets/buttons/button_released.png");

    start.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    start.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    start.body.setScale(1.5f, 1.5f);
    start.setOriginsToCenter();
    start.body.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2 - start.body.getGlobalBounds().height - BUTTON_MARGIN);
    start.setupText(start.text, game.assets.getFont("font"), 40, "START", sf::Color::White);
    start.centerTextToBody();

    settings.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    settings.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    settings.body.setScale(1.5f, 1.5f);
    settings.setOriginsToCenter();
    settings.body.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2);
    settings.setupText(settings.text, game.assets.getFont("font"), 40, "SETTINGS", sf::Color::White);
    settings.centerTextToBody();

    exit.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    exit.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    exit.body.setScale(1.5f, 1.5f);
    exit.setOriginsToCenter();
    exit.body.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2 + exit.body.getGlobalBounds().height + BUTTON_MARGIN);
    exit.setupText(exit.text, game.assets.getFont("font"), 40, "EXIT", sf::Color::White);
    exit.centerTextToBody();
}

void MainMenuState::update()
{
    high_score.setString("HIGH SCORE: " + std::to_string(game.game_settings.high_score));
    if (start.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.push(std::make_unique<LevelSelectState>(game, background));
    if (settings.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.push(std::make_unique<SettingsState>(game, background));
    if (exit.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.win.close();
    background.update(game.dt.get());
}

void MainMenuState::render()
{
    game.win.draw(background);
    game.win.draw(title);
    game.win.draw(high_score);
    game.win.draw(start);
    game.win.draw(settings);
    game.win.draw(exit);
}
