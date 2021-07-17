#include "MultiplayerConnectionState.h"

MultiplayerConnectionState::MultiplayerConnectionState(Game& game, Background& background) :
    game(game),
    background(background),
    host_name(game.win, game.input, game.assets.getFont("font"), sf::Vector2f(400.f, 25.f), 20, "NAME: "),
    host_port(game.win, game.input, game.assets.getFont("font"), sf::Vector2f(400.f, 25.f), 20, "PORT: "),
    client_name(game.win, game.input, game.assets.getFont("font"), sf::Vector2f(400.f, 25.f), 20, "NAME: "),
    client_port(game.win, game.input, game.assets.getFont("font"), sf::Vector2f(400.f, 25.f), 20, "PORT: "),
    client_adress(game.win, game.input, game.assets.getFont("font"), sf::Vector2f(400.f, 25.f), 20, "ADRESS: "),
    loader_animation(loader)
{
    name = "MultiplayerConnection";
    setupTexts();
    setupTextBoxes();
    setupButtons();
    setupLoader();
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
    connect_host.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    connect_host.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    connect_host.body.setScale(1.f, 1.f);
    connect_host.setOriginsToCenter();
    connect_host.body.setPosition(host_title.getPosition().x,
                                  client_adress.body.getPosition().y + client_adress.body.getGlobalBounds().height / 2 +
                                  connect_host.body.getGlobalBounds().height / 2 + MARGIN);
    connect_host.setupText(connect_host.text, game.assets.getFont("font"), 30, "HOST", sf::Color::White);
    connect_client.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    connect_client.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    connect_client.body.setScale(1.f, 1.f);
    connect_client.setOriginsToCenter();
    connect_client.body.setPosition(connect_title.getPosition().x, connect_host.body.getPosition().y);
    connect_client.setupText(connect_client.text, game.assets.getFont("font"), 30, "CONNECT", sf::Color::White);
}

void MultiplayerConnectionState::setupLoader()
{
    loader_animation.loadAtlas(game.assets.getTexture("loader"), sf::Vector2u(6, 5));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 6; j++)
            loader_animation.addFrame(sf::Vector2u(j, i), sf::seconds(0.05f));
    for (int j = 0; j < 5; j++)
        loader_animation.addFrame(sf::Vector2u(j, 4), sf::seconds(0.05f));
    loader_animation.setSpriteFrame(sf::Vector2u(0, 0));
    loader.setOrigin(loader.getLocalBounds().width / 2, loader.getLocalBounds().height / 2);
    loader.setPosition((connect_host.body.getPosition().x + connect_client.body.getPosition().x) / 2,
                       connect_host.body.getPosition().y);
    loader.setScale(0.25f, 0.25f);
    loader.setColor(sf::Color(100, 100, 100));
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
    if (waiting_host_connection || waiting_client_connection)
        loader_animation.run(game.dt.get());
    if (waiting_host_connection)
        connect_host.text.setString("CANCEL");
    else
        connect_host.text.setString("HOST");
    if (waiting_client_connection)
        connect_client.text.setString("CANCEL");
    else
        connect_client.text.setString("CONNECT");
    if (connect_host.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left) && !waiting_client_connection &&
        host_port.getContents().size() > 0)
    {
        waiting_host_connection = 1 - waiting_host_connection;
        if (waiting_host_connection)
            connection_thread = std::thread(&Networking::connectHost, &game.networking, host_name.getContents(),
                                            (unsigned short)(std::stoi(host_port.getContents())));
        else
            connection_thread.detach();
    }
    else if (connect_client.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left) && !waiting_host_connection &&
             client_port.getContents().size() > 0 && client_adress.getContents().size() > 0)
    {
        waiting_client_connection = 1 - waiting_client_connection;
        if (waiting_client_connection)
        {
            sf::IpAddress adress;
            if (client_adress.getContents().compare("LOCALHOST") == 0 || client_adress.getContents().compare("localhost") == 0)
                adress = sf::IpAddress::getLocalAddress();
            else
                adress = client_adress.getContents();
            connection_thread = std::thread(&Networking::connectClient, &game.networking, client_name.getContents(),
                                            (unsigned short)(std::stoi(client_port.getContents())), adress);
        }
        else
            connection_thread.detach();
    }
    if (waiting_host_connection)
    {
        if (game.networking.connected)
        {
            connection_thread.detach();
            game.states.push(std::make_unique<MultiplayerGameState>(game, background, 4));
        }
        loader.setPosition(connect_host.body.getGlobalBounds().left + connect_host.body.getGlobalBounds().width + 50.f,
        loader.getPosition().y);
    }
    else if (waiting_client_connection)
    {
        if (game.networking.connected)
        {
            connection_thread.detach();
            game.states.push(std::make_unique<MultiplayerGameState>(game, background, 4));
        }
        loader.setPosition(connect_client.body.getGlobalBounds().left + connect_client.body.getGlobalBounds().width + 50.f,
        loader.getPosition().y);
    }
    else
        loader_animation.reset();

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
    game.win.draw(connect_host);
    game.win.draw(connect_client);
    if (waiting_client_connection || waiting_host_connection)
        game.win.draw(loader);
}
