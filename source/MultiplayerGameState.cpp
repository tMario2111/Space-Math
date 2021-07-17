#include "MultiplayerGameState.h"
#include <iostream>

MultiplayerGameState::MultiplayerGameState(Game& game, Background& background, unsigned int level) :
    game(game),
    background(background),
    level(level),
    host_ship(game.assets, game.win, game.dt),
    client_ship(game.assets, game.win, game.dt)
{
    name = "MultiplayerGame";
    enemies_render_states.texture = &game.assets.getTexture("ufo_enemy");
    bullets_render_states.texture = &game.assets.getTexture("star_bullet");
    syncRandomSeed();
    for(int i = 0; i<100 ; i++)
        std::cout<<game.random.getInt(0,100)<<"\n";
    setupShips();
    spawnClientEnemy();
    spawnHostEnemy();
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
    host_ship.sprite.setColor(sf::Color(199, 36, 36));

    client_ship.sprite.setPosition(game.win.getSize().x / 2 + client_ship.sprite.getGlobalBounds().width / 2, game.win.getSize().y / 2);
    client_ship.sprite.setColor(sf::Color(36, 36, 199));
}

void MultiplayerGameState::spawnHostEnemy()
{
    std::unique_ptr<Enemy> new_enemy = std::make_unique<UFOEnemy>(game.assets, game.win, game.dt);
    sf::Vector2f position;
    position.x = -ENEMY_SPAWN_MARGIN;
    position.y = game.random.getInt(-ENEMY_SPAWN_MARGIN, game.win.getSize().y + ENEMY_SPAWN_MARGIN);
    new_enemy.get()->sprite.setPosition(position);
    new_enemy.get()->onSpawn();
    host_enemies.push_back(std::move(new_enemy));
}

void MultiplayerGameState::spawnClientEnemy()
{
    std::unique_ptr<Enemy> new_enemy = std::make_unique<UFOEnemy>(game.assets, game.win, game.dt);
    sf::Vector2f position;
    position.x = game.win.getSize().x + ENEMY_SPAWN_MARGIN;
    position.y = game.random.getInt(-ENEMY_SPAWN_MARGIN, game.win.getSize().y + ENEMY_SPAWN_MARGIN);
    new_enemy.get()->sprite.setPosition(position);
    new_enemy.get()->onSpawn();
    host_enemies.push_back(std::move(new_enemy));
}

void MultiplayerGameState::spawnEnemies()
{
    host_enemies_spawn_clock += game.dt.get();
    if(host_enemies_spawn_clock > host_enemies_spawn_delay)
    {
        host_enemies_spawn_clock = sf::seconds(0.f);
        spawnHostEnemy();
    }

    client_enemies_spawn_clock += game.dt.get();
    if(client_enemies_spawn_clock > client_enemies_spawn_delay)
    {
        client_enemies_spawn_clock = sf::seconds(0.f);
        spawnClientEnemy();
    }
}

void MultiplayerGameState::addEnemiesToBatch()
{
    enemies_batch.clear();
    for(auto& i : host_enemies)
        if(!i.get()->going_to_die)
            enemies_batch.append(i.get()->sprite);
    for(auto& i : client_enemies)
        if(!i.get()->going_to_die)
            enemies_batch.append(i.get()->sprite);
}

void MultiplayerGameState::update()
{
    background.update(game.dt.get());
    host_ship.update();
    client_ship.update();
    spawnEnemies();
    for(auto& i : host_enemies)
        i.get()->update();
    for(auto& i : client_enemies)
        i.get()->update();
    addEnemiesToBatch();
}

void MultiplayerGameState::render()
{
    game.win.draw(background);
    game.win.draw(host_ship);
    game.win.draw(client_ship);
    game.win.draw(enemies_batch, enemies_render_states);
}
