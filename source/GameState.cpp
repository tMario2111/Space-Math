#include "GameState.h"

GameState::GameState(Game& game, Background& background, unsigned int level) :
    game(game),
    background(background),
    level(level),
    mother_ship(game.assets, game.win, game.dt),
    equations(game.assets, game.win, game.random, game.input, game.dt, level)
{
    name = "Game";
    setupBackground();
    setupMusic();
    setupHealthBar();
    spawnEnemy();
    setupScore();
}

void GameState::setupBackground()
{
    switch (level)
    {
    case 1:
        background.setTexture(game.assets.getTexture("background1"));
        break;
    case 2:
        background.setTexture(game.assets.getTexture("background2"));
        break;
    case 3:
        background.setTexture(game.assets.getTexture("background3"));
        break;
    case 4:
        background.setTexture(game.assets.getTexture("background4"));
        break;
    }
}

void GameState::setupMusic()
{
    game.assets.loadTexture("explosion_texture", "assets/effects/explosion.png");
    game.assets.loadSound("explosion_sound", "assets/sounds/explosion.wav");
    game.assets.getSound("explosion_sound").setVolume(game.game_settings.game_volume);
    music.setLoop(1);
    music.setVolume(game.game_settings.music_volume);
    music.openFromFile("assets/music/game_music.wav");
    music.play();
}

void GameState::setupHealthBar()
{
    game.assets.loadTexture("health_bar_empty", "assets/progress_bars/progress_fill_blue.png");
    game.assets.loadTexture("health_bar_fill", "assets/progress_bars/progress_fill_lightblue.png");
    health_bar.setTextures(game.assets.getTexture("health_bar_empty"), game.assets.getTexture("health_bar_fill"));
    health_bar.setPosition(sf::Vector2f(game.win.getSize().x / 2, 25.f));
}

void GameState::setupScore()
{
    score_text.setFont(game.assets.getFont("font"));
    score_text.setCharacterSize(40);
    score_text.setPosition(10.f, 10.f);
}

void GameState::spawnEnemy()
{
    auto new_enemy = std::make_unique<DoveEnemy>(game.assets, game.win, game.dt);
    sf::Vector2f position;
    position.x = game.random.getInt(0, 1) ? 0.f : game.win.getSize().x;
    position.y = game.random.getInt(-ENEMY_SPAWN_MARGIN, game.win.getSize().y + ENEMY_SPAWN_MARGIN);
    new_enemy.get()->sprite.setPosition(position);
    new_enemy.get()->onSpawn();
    enemies.push_back(std::move(new_enemy));
}

void GameState::pauseMenuEvent()
{
    if (game.input.isKeyReleased(sf::Keyboard::Escape))
    {
        sf::Texture texture;
        texture.create(game.win.getSize().x, game.win.getSize().y);
        texture.update(game.win);
        game.states.states_just_changed = 1;
        music_timestamp = music.getPlayingOffset();
        music.stop();
        game.states.push(std::make_unique<PauseMenuState>(game, texture.copyToImage()));
    }
}

void GameState::gameOverEvent()
{
    if (mother_ship.HP <= 0.f)
    {
        sf::Texture texture;
        texture.create(game.win.getSize().x, game.win.getSize().y);
        texture.update(game.win);
        game.states.states_just_changed = 1;
        music_timestamp = music.getPlayingOffset();
        music.stop();
        game.states.push(std::make_unique<GameOverState>(game, texture.copyToImage(), (int)score, level));
    }
}

void GameState::addBulletsToBatch()
{
    bullets_batch.clear();
    for (auto& i : enemies)
        for (auto& j : i.get()->shooting_ability.bullets)
            bullets_batch.append(j);
}

void GameState::collisionBulletsMothership()
{
    for (unsigned int i = 0; i < enemies.size(); i++)
        for (unsigned int j = 0; j < enemies[i].get()->shooting_ability.bullets.size(); j++)
            if (Collision::PixelPerfectTest(mother_ship.sprite, enemies[i].get()->shooting_ability.bullets[j], 1))
            {
                enemies[i].get()->shooting_ability.bullets.erase(enemies[i].get()->shooting_ability.bullets.begin() + j--);
                mother_ship.HP -= enemies[i].get()->damage;
            }
}

void GameState::spawnEnemies()
{
    enemies_spawn_clock += game.dt.get().asSeconds();
    if (enemies_spawn_clock > enemy_spawn_delay)
    {
        enemies_spawn_clock = 0;
        spawnEnemy();
    }
}

void GameState::deleteEnemies()
{
    for (unsigned int i = 0; i < enemies.size(); i++)
        if (enemies[i].get()->dead)
        {
            if (enemies.size() == 1)
            {
                enemies.erase(enemies.begin() + i);
                return;
            }
            else
                enemies.erase(enemies.begin() + i--);
        }
}

void GameState::update()
{
    if (music.getStatus() == sf::Music::Stopped)
    {
        music.setPlayingOffset(music_timestamp);
        music.play();
    }
    pauseMenuEvent();
    if (game.states.states_just_changed)
        return;
    background.update(game.dt.get());
    equations.update();
    mother_ship.update();
    health_bar.setProgress(mother_ship.HP);
    spawnEnemies();
    for (auto& i : enemies)
        i.get()->update();
    mother_ship.findClosestEnemy(enemies, equations, score);
    collisionBulletsMothership();
    deleteEnemies();
    score_text.setString("score: " + std::to_string(score));
    enemy_spawn_delay = 5.f - (score / 25.f);
    gameOverEvent();
    dove_enemies_batch.clear();
    for (auto& i : enemies)
        if (!i.get()->going_to_die)
            dove_enemies_batch.append(i.get()->sprite);
    addBulletsToBatch();
}

void GameState::render()
{
    game.win.draw(background);
    game.win.draw(dove_enemies_batch, sf::RenderStates(&game.assets.getTexture("dove_enemy")));
    game.win.draw(mother_ship);
    game.win.draw(bullets_batch, sf::RenderStates(&game.assets.getTexture("long_bullets")));
    for (auto& i : enemies)
        game.win.draw(i.get()->explosion);
    game.win.draw(health_bar);
    game.win.draw(equations);
    game.win.draw(score_text);
}
