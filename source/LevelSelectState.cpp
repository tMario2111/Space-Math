#include "LevelSelectState.h"

LevelSelectState::LevelSelectState(Game& game, Background& background) :
    game(game),
    background(background)
{
    name = "LevelSelect";
    setupTitle();
    setupButtons();
}

void LevelSelectState::setupTitle()
{
    title.setFont(game.assets.getFont("font"));
    title.setCharacterSize(45);
    title.setString("SELECT LEVEL");
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 5);
}

void LevelSelectState::setupButtons()
{
    level2.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    level2.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    level2.body.setScale(1.5f, 1.5f);
    level2.setOriginsToCenter();
    level2.body.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2 - level2.body.getGlobalBounds().height / 2 - BUTTON_MARGIN / 2);
    level2.setupText(level2.text, game.assets.getFont("font"), 35, "EQUATIONS", sf::Color::White);
    level2.centerTextToBody();

    level1.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    level1.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    level1.body.setScale(1.5f, 1.5f);
    level1.setOriginsToCenter();
    level1.body.setPosition(game.win.getSize().x / 2, level2.body.getPosition().y - level1.body.getGlobalBounds().height - BUTTON_MARGIN);
    level1.setupText(level1.text, game.assets.getFont("font"), 35, "BASIC MATH", sf::Color::White);
    level1.centerTextToBody();

    level3.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    level3.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    level3.body.setScale(1.5f, 1.5f);
    level3.setOriginsToCenter();
    level3.body.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2 + level3.body.getGlobalBounds().height / 2 + BUTTON_MARGIN / 2);
    level3.setupText(level3.text, game.assets.getFont("font"), 35, "TRIGONOMETRY", sf::Color::White);
    level3.centerTextToBody();

    level4.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    level4.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    level4.body.setScale(1.5f, 1.5f);
    level4.setOriginsToCenter();
    level4.body.setPosition(game.win.getSize().x / 2, level3.body.getPosition().y + level4.body.getGlobalBounds().height + BUTTON_MARGIN);
    level4.setupText(level4.text, game.assets.getFont("font"), 35, "EVERYTHING", sf::Color::White);
    level4.centerTextToBody();

}

void LevelSelectState::update()
{
    background.update(game.dt.get());
    if (game.input.isKeyReleased(sf::Keyboard::Escape))
        game.states.pop();
    if (level1.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.push(std::make_unique<GameState>(game, background, 1));
    else if (level2.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.push(std::make_unique<GameState>(game, background, 2));
    else if (level3.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.push(std::make_unique<GameState>(game, background, 3));
    else if (level4.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.push(std::make_unique<GameState>(game, background, 4));

}

void LevelSelectState::render()
{
    game.win.draw(background);
    game.win.draw(title);
    game.win.draw(level1);
    game.win.draw(level2);
    game.win.draw(level3);
    game.win.draw(level4);
}
