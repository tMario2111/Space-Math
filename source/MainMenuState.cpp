#include "MainMenuState.h"

MainMenuState::MainMenuState(Game& game) :
    game(game),
    background(game.win)
{
    name = "MainMenu";
    setupBackground();
    setupTitle();
    setupButtons();
    setupCredits();
}

void MainMenuState::setupBackground()
{
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
    title.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 5);
}

void MainMenuState::setupButtons()
{
    achievements.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    achievements.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    achievements.body.setScale(1.5f, 1.5f);
    achievements.setOriginsToCenter();
    achievements.body.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2);
    achievements.setupText(achievements.text, game.assets.getFont("font"), 35, "ACHIEVEMENTS", sf::Color::White);
    achievements.centerTextToBody();

    multiplayer.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    multiplayer.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    multiplayer.body.setScale(1.5f, 1.5f);
    multiplayer.setOriginsToCenter();
    multiplayer.body.setPosition(game.win.getSize().x / 2, achievements.body.getPosition().y - achievements.body.getGlobalBounds().height - BUTTON_MARGIN);
    multiplayer.setupText(multiplayer.text, game.assets.getFont("font"), 35, "MULTIPLAYER", sf::Color::White);
    multiplayer.centerTextToBody();

    start.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    start.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    start.body.setScale(1.5f, 1.5f);
    start.setOriginsToCenter();
    start.body.setPosition(game.win.getSize().x / 2, multiplayer.body.getPosition().y - multiplayer.body.getGlobalBounds().height - BUTTON_MARGIN);
    start.setupText(start.text, game.assets.getFont("font"), 35, "START", sf::Color::White);
    start.centerTextToBody();

    settings.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    settings.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    settings.body.setScale(1.5f, 1.5f);
    settings.setOriginsToCenter();
    settings.body.setPosition(game.win.getSize().x / 2, achievements.body.getPosition().y + achievements.body.getGlobalBounds().height + BUTTON_MARGIN);
    settings.setupText(settings.text, game.assets.getFont("font"), 35, "SETTINGS", sf::Color::White);
    settings.centerTextToBody();

    exit.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    exit.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    exit.body.setScale(1.5f, 1.5f);
    exit.setOriginsToCenter();
    exit.body.setPosition(game.win.getSize().x / 2, settings.body.getPosition().y + settings.body.getGlobalBounds().height + BUTTON_MARGIN);
    exit.setupText(exit.text, game.assets.getFont("font"), 35, "EXIT", sf::Color::White);
    exit.centerTextToBody();
}

void MainMenuState::setupCredits()
{
    credits.setFont(game.assets.getFont("font"));
    credits.setCharacterSize(15);
    credits.setString(game.game_settings.doc.FirstChildElement("strings")->FirstChildElement("credits")->GetText());
    credits.setPosition(5.f - credits.getLocalBounds().left, game.win.getSize().y - credits.getGlobalBounds().height - credits.getLocalBounds().top - 5.f);
}

void MainMenuState::update()
{
    if (start.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.push(std::make_unique<LevelSelectState>(game, background));
    else if (multiplayer.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.push(std::make_unique<MultiplayerConnectionState>(game, background));
    else if (achievements.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.push(std::make_unique<AchievementsState>(game, background));
    else if (settings.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.push(std::make_unique<SettingsState>(game, background));
    else if (exit.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.win.close();
    background.update(game.dt.get());
}

void MainMenuState::render()
{
    game.win.draw(background);
    game.win.draw(title);
    game.win.draw(start);
    game.win.draw(multiplayer);
    game.win.draw(achievements);
    game.win.draw(settings);
    game.win.draw(exit);
    game.win.draw(credits);
}
