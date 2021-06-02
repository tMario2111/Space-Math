#include "LevelSelectState.h"

LevelSelectState::LevelSelectState(Game& game, Background& background) :
    game(game),
    background(background)
{
    name = "LevelSelect";
    setupTitle();
    setupButtons();
    setupHighScores();
}

void LevelSelectState::setupTitle()
{
    title.setFont(game.assets.getFont("font"));
    title.setCharacterSize(45);
    title.setString("SELECT LEVEL");
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 5);
}

void LevelSelectState::setupHighScores()
{
    high_score_level1.setFont(game.assets.getFont("font"));
    high_score_level1.setCharacterSize(35);
    high_score_level1.setString("BEST: " + std::to_string(game.game_settings.high_score_level1));
    high_score_level1.setOrigin(0, high_score_level1.getLocalBounds().height / 2);
    high_score_level1.setPosition(level1.body.getPosition().x + level1.body.getGlobalBounds().width / 2 + 50.f, 0.f);
    mke::utility::centerYAxis(high_score_level1, level1.body.getGlobalBounds().top, level1.body.getGlobalBounds().top + level1.body.getGlobalBounds().height);

    high_score_level2.setFont(game.assets.getFont("font"));
    high_score_level2.setCharacterSize(35);
    high_score_level2.setString("BEST: " + std::to_string(game.game_settings.high_score_level2));
    high_score_level2.setOrigin(0, high_score_level2.getLocalBounds().height / 2);
    high_score_level2.setPosition(level2.body.getPosition().x + level2.body.getGlobalBounds().width / 2 + 50.f, 0.f);
    mke::utility::centerYAxis(high_score_level2, level2.body.getGlobalBounds().top, level2.body.getGlobalBounds().top + level2.body.getGlobalBounds().height);

    high_score_level3.setFont(game.assets.getFont("font"));
    high_score_level3.setCharacterSize(35);
    high_score_level3.setString("BEST: " + std::to_string(game.game_settings.high_score_level3));
    high_score_level3.setOrigin(0, high_score_level3.getLocalBounds().height / 2);
    high_score_level3.setPosition(level3.body.getPosition().x + level3 .body.getGlobalBounds().width / 2 + 50.f, 0.f);
    mke::utility::centerYAxis(high_score_level3, level3.body.getGlobalBounds().top, level3.body.getGlobalBounds().top + level3.body.getGlobalBounds().height);

    high_score_level4.setFont(game.assets.getFont("font"));
    high_score_level4.setCharacterSize(35);
    high_score_level4.setString("BEST: " + std::to_string(game.game_settings.high_score_level4));
    high_score_level4.setOrigin(0, high_score_level4.getLocalBounds().height / 2);
    high_score_level4.setPosition(level4.body.getPosition().x + level4.body.getGlobalBounds().width / 2 + 50.f, 0.f);
    mke::utility::centerYAxis(high_score_level4, level4.body.getGlobalBounds().top, level4.body.getGlobalBounds().top + level4.body.getGlobalBounds().height);
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
    game.win.draw(high_score_level1);
    game.win.draw(level2);
    game.win.draw(high_score_level2);
    game.win.draw(level3);
    game.win.draw(high_score_level3);
    game.win.draw(level4);
    game.win.draw(high_score_level4);
}
