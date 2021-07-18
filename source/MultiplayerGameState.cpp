#include "MultiplayerGameState.h"

MultiplayerGameState::MultiplayerGameState(Game& game, Background& background, unsigned int level) :
    game(game),
    background(background),
    level(level),
    equations(game.assets, game.win, questions_random, game.input, game.dt, 4),
    host_ship(game.assets, game.win, game.dt),
    client_ship(game.assets, game.win, game.dt)
{
    name = "MultiplayerGame";
    syncRandomSeed();
    syncNames();
    setupShips();
    setupTexts();
    spawnClientEnemy();
    spawnHostEnemy();
    enemies_render_states.texture = &game.assets.getTexture("ufo_enemy");
    bullets_render_states.texture = &game.assets.getTexture("star_bullet");
}

void MultiplayerGameState::syncRandomSeed()
{
    if (game.networking.user_type == Networking::UserType::Host)
    {
        unsigned int seed = enemies_random.setUniqueSeed();
        questions_random.setCustomSeed(seed);
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
        enemies_random.setCustomSeed(seed);
        questions_random.setCustomSeed(seed);
    }
}

void MultiplayerGameState::syncNames()
{
    sf::Packet packet;
    packet << game.networking.local_name;
    game.networking.socket.send(packet);
    packet.clear();
    game.networking.socket.receive(packet);
    packet >> game.networking.remote_name;
}

void MultiplayerGameState::setupShips()
{
    host_ship.sprite.setPosition(game.win.getSize().x / 2 - host_ship.sprite.getGlobalBounds().width / 2, game.win.getSize().y / 2);
    host_ship.sprite.setColor(sf::Color(199, 36, 36));

    client_ship.sprite.setPosition(game.win.getSize().x / 2 + client_ship.sprite.getGlobalBounds().width / 2, game.win.getSize().y / 2);
    client_ship.sprite.setColor(sf::Color(36, 36, 199));
}

void MultiplayerGameState::setupTexts()
{
    host_name_text.setFont(game.assets.getFont("font"));
    host_name_text.setCharacterSize(25);
    client_name_text.setFont(game.assets.getFont("font"));
    client_name_text.setCharacterSize(25);
    if (game.networking.user_type == Networking::UserType::Host)
    {
        host_name_text.setString(game.networking.local_name);
        client_name_text.setString(game.networking.remote_name);
    }
    else
    {
        host_name_text.setString(game.networking.remote_name);
        client_name_text.setString(game.networking.local_name);
    }
    host_name_text.setOrigin(host_name_text.getLocalBounds().width / 2, host_name_text.getLocalBounds().height / 2);
    client_name_text.setOrigin(client_name_text.getLocalBounds().width / 2, client_name_text.getLocalBounds().height / 2);
    sf::FloatRect host_ship_bounds = host_ship.sprite.getGlobalBounds();
    sf::FloatRect client_ship_bounds = client_ship.sprite.getGlobalBounds();
    const float Y_MARGIN = 200.f;
    mke::utility::centerXAxis(host_name_text, host_ship_bounds.left, host_ship_bounds.left + host_ship_bounds.width);
    mke::utility::centerYAxis(host_name_text, host_ship_bounds.top, host_ship_bounds.top - Y_MARGIN);
    mke::utility::centerXAxis(client_name_text, client_ship_bounds.left, client_ship_bounds.left + client_ship_bounds.width);
    mke::utility::centerYAxis(client_name_text, client_ship_bounds.top, client_ship_bounds.top - Y_MARGIN);
}

void MultiplayerGameState::spawnHostEnemy()
{
    std::unique_ptr<Enemy> new_enemy = std::make_unique<UFOEnemy>(game.assets, game.win, game.dt);
    sf::Vector2f position;
    position.x = -ENEMY_SPAWN_MARGIN;
    position.y = enemies_random.getInt(-ENEMY_SPAWN_MARGIN, game.win.getSize().y + ENEMY_SPAWN_MARGIN);
    new_enemy.get()->sprite.setPosition(position);
    new_enemy.get()->target = host_ship.sprite.getPosition();
    new_enemy.get()->onSpawn();
    host_enemies.push_back(std::move(new_enemy));
}

void MultiplayerGameState::spawnClientEnemy()
{
    std::unique_ptr<Enemy> new_enemy = std::make_unique<UFOEnemy>(game.assets, game.win, game.dt);
    sf::Vector2f position;
    position.x = game.win.getSize().x + ENEMY_SPAWN_MARGIN;
    position.y = enemies_random.getInt(-ENEMY_SPAWN_MARGIN, game.win.getSize().y + ENEMY_SPAWN_MARGIN);
    new_enemy.get()->sprite.setPosition(position);
    new_enemy.get()->target = client_ship.sprite.getPosition();
    new_enemy.get()->onSpawn();
    client_enemies.push_back(std::move(new_enemy));
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

void MultiplayerGameState::addBulletsToBatch()
{
    bullets_batch.clear();
    for (auto& i : host_enemies)
        for (auto& j : i.get()->shooting_ability.bullets)
            bullets_batch.append(j);
    for (auto& i : client_enemies)
        for (auto& j : i.get()->shooting_ability.bullets)
            bullets_batch.append(j);
}

void MultiplayerGameState::collisionHostBulletsMothership()
{
    for (unsigned int i = 0; i < host_enemies.size(); i++)
        for (unsigned int j = 0; j < host_enemies[i].get()->shooting_ability.bullets.size(); j++)
            if (Collision::PixelPerfectTest(host_ship.sprite, host_enemies[i].get()->shooting_ability.bullets[j], 1))
            {
                host_enemies[i].get()->shooting_ability.bullets.erase(host_enemies[i].get()->shooting_ability.bullets.begin() + j--);
                host_ship.HP -= host_enemies[i].get()->damage;
            }
}

void MultiplayerGameState::collisionClientBulletsMothership()
{
    for (unsigned int i = 0; i < client_enemies.size(); i++)
        for (unsigned int j = 0; j < client_enemies[i].get()->shooting_ability.bullets.size(); j++)
            if (Collision::PixelPerfectTest(client_ship.sprite, client_enemies[i].get()->shooting_ability.bullets[j], 1))
            {
                client_enemies[i].get()->shooting_ability.bullets.erase(client_enemies[i].get()->shooting_ability.bullets.begin() + j--);
                client_ship.HP -= client_enemies[i].get()->damage;
            }
}

void MultiplayerGameState::update()
{
    background.update(game.dt.get());
    equations.update();
    host_ship.update();
    client_ship.update();
    spawnEnemies();
    for(auto& i : host_enemies)
        i.get()->update();
    for(auto& i : client_enemies)
        i.get()->update();
    host_ship.updateTargeting(host_enemies, equations, host_score);
    client_ship.updateTargeting(client_enemies, equations, client_score);
    collisionHostBulletsMothership();
    collisionClientBulletsMothership();
    addEnemiesToBatch();
    addBulletsToBatch();
}

void MultiplayerGameState::render()
{
    game.win.draw(background);
    game.win.draw(bullets_batch, bullets_render_states);
    game.win.draw(enemies_batch, enemies_render_states);
    game.win.draw(host_ship);
    game.win.draw(client_ship);
    game.win.draw(equations);
    game.win.draw(host_name_text);
    game.win.draw(client_name_text);
}
