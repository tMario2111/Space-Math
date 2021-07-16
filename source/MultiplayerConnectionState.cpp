#include "MultiplayerConnectionState.h"

MultiplayerConnectionState::MultiplayerConnectionState(Game& game, Background& background) :
    game(game),
    background(background),
    test(sf::Vector2f(600.f, 100.f), "Wait motherf", game.assets.getFont("font"), 50)
{
    setupButtons();
}

void MultiplayerConnectionState::setupButtons()
{
    back_.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    back_.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    back_.body.setScale(0.5f, 1.f);
    back_.setOriginsToCenter();
    back_.body.setPosition(back_.body.getGlobalBounds().width / 2 + 20.f, back_.body.getGlobalBounds().height / 2 + 20.f);
    back_.setupText(back_.text, game.assets.getFont("font"), 20, "BACK", sf::Color::White);
    back_.centerTextToBody();
}

void MultiplayerConnectionState::update()
{
    background.update(game.dt.get());
    if (game.input.isKeyReleased(sf::Keyboard::Escape) || (back_.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left)))
        game.states.pop();
    test.update(game.input.last_pressed_key, &game.win);
}

void MultiplayerConnectionState::render()
{
    game.win.draw(background);
    game.win.draw(back_);
    game.win.draw(test);
}
