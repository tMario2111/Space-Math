#include "PauseMenuState.h"

PauseMenuState::PauseMenuState(Game& game, sf::Image background_texture) :
    game(game)
{
    name = "PauseMenu";
    this->background_texture.loadFromImage(background_texture);
    background_sprite.setTexture(this->background_texture);
    background_sprite.setColor(sf::Color(100, 100, 100));
    setupButtons();
}

void PauseMenuState::setupButtons()
{
    resume.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    resume.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    resume.body.setScale(1.5f, 1.5f);
    resume.setOriginsToCenter();
    resume.body.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2 - resume.body.getGlobalBounds().height / 2 - BUTTON_MARGIN / 2);
    resume.setupText(resume.text, game.assets.getFont("font"), 40, "RESUME", sf::Color::White);
    resume.centerTextToBody();

    main_menu.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    main_menu.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    main_menu.body.setScale(1.5f, 1.5f);
    main_menu.setOriginsToCenter();
    main_menu.body.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2 + main_menu.body.getGlobalBounds().height / 2 + BUTTON_MARGIN / 2);
    main_menu.setupText(main_menu.text, game.assets.getFont("font"), 40, "MAIN MENU", sf::Color::White);
    main_menu.centerTextToBody();
}

void PauseMenuState::update()
{
    if (game.input.isKeyReleased(sf::Keyboard::Escape))
        game.states.pop();
    if (resume.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.pop();
    if (main_menu.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.popStatesUntil("MainMenu");
}

void PauseMenuState::render()
{
    game.win.draw(background_sprite);
    game.win.draw(resume);
    game.win.draw(main_menu);
}
