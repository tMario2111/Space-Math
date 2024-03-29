#include "GameOverState.h"

GameOverState::GameOverState(Game& game, sf::Image background_texture, int score, unsigned int level, Background& background) :
    game(game),
    background(background),
    level(level)
{
    name = "GameOver";
    this->score = score;
    this->background_texture.loadFromImage(background_texture);
    background_sprite.setTexture(this->background_texture);
    background_sprite.setColor(sf::Color(100, 100, 100));
    checkAchievements();
    setupText();
    setupButtons();

    switch (level)
    {
    case 1:
        if(score > game.game_settings.high_score_level1)
        {
            game.game_settings.high_score_level1 = score;
            game.game_settings.saveDoc("data/data.dat");
        }
        break;
    case 2:
        if(score > game.game_settings.high_score_level2)
        {
            game.game_settings.high_score_level2 = score;
            game.game_settings.saveDoc("data/data.dat");
        }
        break;
    case 3:
        if(score > game.game_settings.high_score_level3)
        {
            game.game_settings.high_score_level3 = score;
            game.game_settings.saveDoc("data/data.dat");
        }
        break;
    case 4:
        if(score > game.game_settings.high_score_level4)
        {
            game.game_settings.high_score_level4 = score;
            game.game_settings.saveDoc("data/data.dat");
        }
        break;
    default:
        break;
    }
}

void GameOverState::checkAchievements()
{
    tinyxml2::XMLElement* root = game.game_settings.doc.FirstChildElement("achievements");
    for (tinyxml2::XMLElement* i = root->FirstChildElement("achievement"); i != 0; i = i->NextSiblingElement("achievement"))
    {
        unsigned int score;
        i->FirstChildElement("score")->QueryUnsignedText(&score);
        if ((unsigned int)this->score >= score)
            i->FirstChildElement("done")->SetText(1);
    }
}

void GameOverState::setupText()
{
    game_over_text.setFont(game.assets.getFont("font"));
    game_over_text.setCharacterSize(50);
    game_over_text.setString("GAME OVER");
    game_over_text.setOrigin(game_over_text.getLocalBounds().width / 2, game_over_text.getLocalBounds().height / 2);
    game_over_text.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 4);

    high_score.setFont(game.assets.getFont("font"));
    high_score.setCharacterSize(30);
    high_score.setString("SCORE: " + std::to_string(score));
    high_score.setOrigin(high_score.getLocalBounds().width / 2, high_score.getLocalBounds().height / 2);
    high_score.setPosition(game.win.getSize().x / 2 + game_over_text.getGlobalBounds().width / 2, game.win.getSize().y / 4 + BUTTON_MARGIN);
}

void GameOverState::setupButtons()
{
    reset.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    reset.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    reset.body.setScale(1.5f, 1.5f);
    reset.setOriginsToCenter();
    reset.body.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2 - reset.body.getGlobalBounds().height / 2 - BUTTON_MARGIN / 2);
    reset.setupText(reset.text, game.assets.getFont("font"), 40, "TRY AGAIN", sf::Color::White);
    reset.centerTextToBody();

    main_menu.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    main_menu.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    main_menu.body.setScale(1.5f, 1.5f);
    main_menu.setOriginsToCenter();
    main_menu.body.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2 + main_menu.body.getGlobalBounds().height / 2 + BUTTON_MARGIN / 2);
    main_menu.setupText(main_menu.text, game.assets.getFont("font"), 40, "MAIN MENU", sf::Color::White);
    main_menu.centerTextToBody();
}

void GameOverState::update()
{
    if (main_menu.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.popStatesUntil("MainMenu");
    else if (reset.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.popStatesUntilAndPush("LevelSelect", std::make_unique<GameState>(game, background, level));
}

void GameOverState::render()
{
    game.win.draw(background_sprite);
    game.win.draw(game_over_text);
    game.win.draw(high_score);
    game.win.draw(main_menu);
    game.win.draw(reset);
}
