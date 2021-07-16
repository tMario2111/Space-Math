#include "MultiplayerConnectionState.h"

MultiplayerConnectionState::MultiplayerConnectionState(Game& game, Background& background) :
    game(game),
    background(background),
    host_name(game.win, game.input, game.assets.getFont("font"), sf::Vector2f(400.f, 25.f), 20, "NAME: "),
    host_port(game.win, game.input, game.assets.getFont("font"), sf::Vector2f(400.f, 25.f), 20, "PORT: "),
    client_name(game.win, game.input, game.assets.getFont("font"), sf::Vector2f(400.f, 25.f), 20, "NAME: "),
    client_port(game.win, game.input, game.assets.getFont("font"), sf::Vector2f(400.f, 25.f), 20, "PORT: "),
    client_adress(game.win, game.input, game.assets.getFont("font"), sf::Vector2f(400.f, 25.f), 20, "ADRESS: ")
{
    setupTexts();
    setupTextBoxes();
    setupButtons();
}

void MultiplayerConnectionState::setupTexts()
{
    host_title.setFont(game.assets.getFont("font"));
    host_title.setCharacterSize(45);
    host_title.setString("HOST");
    host_title.setOrigin(host_title.getLocalBounds().width / 2, host_title.getLocalBounds().height / 2);
    host_title.setPosition(host_title.getPosition().x, game.win.getSize().y / 5);
    mke::utility::centerXAxis(host_title, 200.f, game.win.getSize().x / 2);

    connect_title.setFont(game.assets.getFont("font"));
    connect_title.setCharacterSize(45);
    connect_title.setString("CONNECT");
    connect_title.setOrigin(connect_title.getLocalBounds().width / 2, connect_title.getLocalBounds().height / 2);
    connect_title.setPosition(connect_title.getPosition().x, game.win.getSize().y / 5);
    mke::utility::centerXAxis(connect_title, game.win.getSize().x / 2, game.win.getSize().x - 200.f);
}

void MultiplayerConnectionState::setupTextBoxes()
{
    host_name.body.setPosition(host_title.getPosition().x,
                               host_title.getPosition().y + host_title.getGlobalBounds().height / 2 +
                               host_name.body.getGlobalBounds().height / 2 + 2 * MARGIN);
    host_port.body.setPosition(host_title.getPosition().x,
                               host_name.body.getPosition().y + host_name.body.getGlobalBounds().height / 2 +
                               host_port.body.getGlobalBounds().height / 2 + MARGIN);
    host_port.digits_only = 1;
    client_name.body.setPosition(connect_title.getPosition().x,
                                 connect_title.getPosition().y + connect_title.getGlobalBounds().height / 2 +
                                 client_name.body.getGlobalBounds().height / 2 + 2 * MARGIN);
    client_port.body.setPosition(connect_title.getPosition().x,
                                 client_name.body.getPosition().y + client_name.body.getGlobalBounds().height / 2 +
                                 client_port.body.getGlobalBounds().height / 2 + MARGIN);
    client_port.digits_only = 1;
    client_adress.body.setPosition(connect_title.getPosition().x,
                                  client_port.body.getPosition().y + client_port.body.getGlobalBounds().height / 2 +
                                  client_adress.body.getGlobalBounds().height / 2 + MARGIN);
    host_name.characters_limit = 18;
    host_port.characters_limit = 5;
    client_name.characters_limit = 18;
    client_port.characters_limit = 5;
    client_adress.characters_limit = 18;
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
    host_name.update();
    host_port.update();
    client_name.update();
    client_port.update();
    client_adress.update();
}

void MultiplayerConnectionState::render()
{
    game.win.draw(background);
    game.win.draw(back_);
    game.win.draw(host_title);
    game.win.draw(connect_title);
    game.win.draw(host_name);
    game.win.draw(host_port);
    game.win.draw(client_name);
    game.win.draw(client_port);
    game.win.draw(client_adress);
}
