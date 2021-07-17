#include "MultiplayerGameState.h"

MultiplayerGameState::MultiplayerGameState(Game& game, Background& background, unsigned int level) :
    game(game),
    background(background),
    level(level),
    host_ship(game.assets, game.win, game.dt),
    client_ship(game.assets, game.win, game.dt)
{
    name = "MultiplayerGame";
    syncRandomSeed();
    setupShips();
}

void MultiplayerGameState::syncRandomSeed()
{
    if (game.networking.user_type == Networking::UserType::Host)
    {
        unsigned int seed = game.random.setUniqueSeed();
        sf::Packet packet;
        packet << seed;
        game.networking.socket.send(packet);
    }
    else
    {
        unsigned int seed;
        sf::Packet packet;
        game.networking.socket.receive(packet);
        packet >> seed;
    }
}

void MultiplayerGameState::setupShips()
{
    host_ship.sprite.setPosition(game.win.getSize().x / 2 - host_ship.sprite.getGlobalBounds().width / 2, game.win.getSize().y / 2);
    host_ship.sprite.setColor(sf::Color(255, 0, 0));

    client_ship.sprite.setPosition(game.win.getSize().x / 2 + client_ship.sprite.getGlobalBounds().width / 2, game.win.getSize().y / 2);
    client_ship.sprite.setColor(sf::Color(0, 0, 255));
}

void MultiplayerGameState::update()
{
    background.update(game.dt.get());
    host_ship.update();
    client_ship.update();
}

void MultiplayerGameState::render()
{
    game.win.draw(background);
    game.win.draw(host_ship);
    game.win.draw(client_ship);
}
