#include "MultiplayerGameState.h"

MultiplayerGameState::MultiplayerGameState(Game& game, Background& background, unsigned int level) :
    game(game),
    background(background),
    level(level),
    equations(game.assets, game.win, questions_random, game.input, game.dt, 4),
    host_ship(game.assets, game.win, game.dt),
    client_ship(game.assets, game.win, game.dt),
    host_fire_barrier(game.win, game.assets, game.dt),
    client_fire_barrier(game.win, game.assets, game.dt),
    host_health_bar(game.assets.getFont("font")),
    client_health_bar(game.assets.getFont("font")),
    damage_effect(static_cast<sf::Vector2f>(game.win.getSize()))
{
    name = "MultiplayerGame";
    syncRandomSeed();
    syncNames();
    setupMusic();
    setupShips();
    setupTexts();
    setupHealthBars();
    setupDamageEffect();
    spawnClientEnemy();
    spawnHostEnemy();
    enemies_render_states.texture = &game.assets.getTexture("ufo_enemy");
    bullets_render_states.texture = &game.assets.getTexture("star_bullet");
    receive_thread = std::thread(MultiplayerGameState::receiveUpdates, this);
}

void MultiplayerGameState::syncRandomSeed()
{
    if (game.networking.user_type == Networking::UserType::Host)
    {
        unsigned int seed = host_enemies_random.setUniqueSeed();
        client_enemies_random.setCustomSeed(seed);
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
        host_enemies_random.setCustomSeed(seed);
        client_enemies_random.setCustomSeed(seed);
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

void MultiplayerGameState::setupMusic()
{
    game.assets.sound_volume = game.game_settings.game_volume;
    music.setLoop(1);
    music.setVolume(game.game_settings.music_volume);
    music.openFromFile("assets/music/game_music.wav");
    music.play();
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
    const float Y_MARGIN = 100.f;
    mke::utility::centerXAxis(host_name_text, host_ship_bounds.left, host_ship_bounds.left + host_ship_bounds.width);
    mke::utility::centerYAxis(host_name_text, host_ship_bounds.top, host_ship_bounds.top - Y_MARGIN);
    mke::utility::centerXAxis(client_name_text, client_ship_bounds.left, client_ship_bounds.left + client_ship_bounds.width);
    mke::utility::centerYAxis(client_name_text, client_ship_bounds.top, client_ship_bounds.top - Y_MARGIN);
    host_fire_barrier.sprite.setPosition(host_ship.sprite.getPosition());
    client_fire_barrier.sprite.setPosition(client_ship.sprite.getPosition());
}

void MultiplayerGameState::setupHealthBars()
{
    host_health_bar.setTextures(game.assets.getTexture("health_bar_empty"), game.assets.getTexture("health_bar_fill"));
    host_health_bar.setPosition(sf::Vector2f(host_ship.sprite.getPosition().x - host_health_bar.getSize().x / 2, 55.f));
    client_health_bar.setTextures(game.assets.getTexture("health_bar_empty"), game.assets.getTexture("health_bar_fill"));
    client_health_bar.setPosition(sf::Vector2f(client_ship.sprite.getPosition().x + client_health_bar.getSize().x / 2, 55.f));
}

void MultiplayerGameState::setupDamageEffect()
{
    damage_effect.setFillColor(sf::Color(255, 0, 0, 0));
    damage_effect.setPosition(0.f, 0.f);
}

void MultiplayerGameState::spawnHostEnemy()
{
    std::unique_ptr<Enemy> new_enemy = std::make_unique<UFOEnemy>(game.assets, game.win, game.dt);
    sf::Vector2f position;
    position.x = -ENEMY_SPAWN_MARGIN;
    position.y = host_enemies_random.getInt(-ENEMY_SPAWN_MARGIN, game.win.getSize().y + ENEMY_SPAWN_MARGIN);;
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
    position.y = client_enemies_random.getInt(-ENEMY_SPAWN_MARGIN, game.win.getSize().y + ENEMY_SPAWN_MARGIN);
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

void MultiplayerGameState::receiveUpdates()
{
    while (1)
    {
        sf::Packet packet;
        if (game.networking.socket.receive(packet) == sf::Socket::Done)
        {
            std::string str;
            packet >> str;
            if (str.compare("HIT!") == 0)
            {
                if (game.networking.user_type == Networking::UserType::Host)
                {
                    client_enemies[0].get()->locked_on = 0;
                    client_enemies[0].get()->going_to_die = 1;
                }
                else
                {
                    host_enemies[0].get()->locked_on = 0;
                    host_enemies[0].get()->going_to_die = 1;
                }
            }
            else if (str.compare("FIRE BARRIER!") == 0)
            {
                if (game.networking.user_type == Networking::UserType::Host)
                    client_fire_barrier.setActive();
                else
                    host_fire_barrier.setActive();
            }
        }
    }
}

void MultiplayerGameState::sendUpdates()
{
    if (!equations.correct_result)
        return;
    sf::Packet packet;
    packet << "HIT!";
    game.networking.socket.send(packet);
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
                if (game.networking.user_type == Networking::UserType::Host)
                    damage_effect.setFillColor(sf::Color(255, 0, 0, 80));
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
                if (game.networking.user_type == Networking::UserType::Client)
                    damage_effect.setFillColor(sf::Color(255, 0, 0, 80));
            }
}

void MultiplayerGameState::collisionHostBulletsFireBarrier()
{
    if (host_fire_barrier.getActive() == 0)
        return;
    for (unsigned int i = 0; i < host_enemies.size(); i++)
        for (unsigned int j = 0; j < host_enemies[i].get()->shooting_ability.bullets.size(); j++)
            if (Collision::PixelPerfectTest(host_fire_barrier.sprite, host_enemies[i].get()->shooting_ability.bullets[j], 1))
            {
                host_enemies[i].get()->shooting_ability.bullets.erase(host_enemies[i].get()->shooting_ability.bullets.begin() + j--);
                host_fire_barrier.HP -= host_enemies[i].get()->damage;
            }
}

void MultiplayerGameState::collisionClientBulletsFireBarrier()
{
    if (client_fire_barrier.getActive() == 0)
        return;
    for (unsigned int i = 0; i < client_enemies.size(); i++)
        for (unsigned int j = 0; j < client_enemies[i].get()->shooting_ability.bullets.size(); j++)
            if (Collision::PixelPerfectTest(client_fire_barrier.sprite, client_enemies[i].get()->shooting_ability.bullets[j], 1))
            {
                client_enemies[i].get()->shooting_ability.bullets.erase(client_enemies[i].get()->shooting_ability.bullets.begin() + j--);
                client_fire_barrier.HP -= client_enemies[i].get()->damage;
            }
}

void MultiplayerGameState::deleteEnemies()
{
    for (unsigned int i = 0; i < host_enemies.size(); i++)
        if (host_enemies[i].get()->dead)
        {
            if (host_enemies.size() == 1)
            {
                host_enemies.erase(host_enemies.begin() + i);
                break; /// !?
            }
            else
                host_enemies.erase(host_enemies.begin() + i--);
        }
    for (unsigned int i = 0; i < client_enemies.size(); i++)
        if (client_enemies[i].get()->dead)
        {
            if (client_enemies.size() == 1)
            {
                client_enemies.erase(client_enemies.begin() + i);
                break; /// !?
            }
            else
                client_enemies.erase(client_enemies.begin() + i--);
        }
}

void MultiplayerGameState::updateDamageEffect()
{
    int opacity = damage_effect.getFillColor().a;
    if (opacity == 0)
        return;
    const unsigned int DECREMENT = 160.f;
    opacity -= DECREMENT * game.dt.get().asSeconds();
    opacity = opacity < 0 ? 0 : opacity;
    damage_effect.setFillColor(sf::Color(damage_effect.getFillColor().r, damage_effect.getFillColor().g, damage_effect.getFillColor().b,
                                         opacity));
}

void MultiplayerGameState::update()
{
    background.update(game.dt.get());
    equations.update();
    sendUpdates();
    host_ship.update();
    client_ship.update();
    spawnEnemies();
    for(auto& i : host_enemies)
        i.get()->update();
    for(auto& i : client_enemies)
        i.get()->update();
    if (game.networking.user_type == Networking::UserType::Host)
    {
        host_ship.updateTargeting(host_enemies, equations, host_score);
        client_ship.updateTargeting(client_enemies, equations, client_score);
    }
    else
    {
        client_ship.updateTargeting(client_enemies, equations, client_score);
        host_ship.updateTargeting(host_enemies, equations, host_score);
    }
    host_fire_barrier.update();
    client_fire_barrier.update();
    if (equations.star_questions_count == equations.star_questions_target)
    {
        if (game.networking.user_type == Networking::UserType::Host)
            host_fire_barrier.setActive();
        else
            client_fire_barrier.setActive();
        equations.star_questions_count = 0;
        sf::Packet packet;
        packet << "FIRE BARRIER!";
        game.networking.socket.send(packet);
    }
    host_health_bar.setProgress(host_ship.HP);
    client_health_bar.setProgress(client_ship.HP);
    collisionHostBulletsMothership();
    collisionClientBulletsMothership();
    collisionHostBulletsFireBarrier();
    collisionClientBulletsFireBarrier();
    deleteEnemies();
    updateDamageEffect();
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
    game.win.draw(host_fire_barrier);
    game.win.draw(client_fire_barrier);
    for (auto& i : host_enemies)
        game.win.draw(i.get()->explosion);
    for (auto& i : client_enemies)
        game.win.draw(i.get()->explosion);
    game.win.draw(damage_effect);
    game.win.draw(equations);
    game.win.draw(host_name_text);
    game.win.draw(client_name_text);
    game.win.draw(host_health_bar);
    game.win.draw(client_health_bar);
}
