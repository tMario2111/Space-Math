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
    setupEnemiesRenderStates();
    setupBulletsRenderStates();
    setupMusic();
    setupHealthBar();
    spawnEnemy();
    setupScore();
}

void GameState::setupBackground()
{
    background.setTexture(game.assets.getTexture("background" + std::to_string(level)));
}

void GameState::setupEnemiesRenderStates()
{
    switch(level)
    {
    case 1:
        enemies_render_states.texture = &game.assets.getTexture("dove_enemy");
        break;
    case 2:
        enemies_render_states.texture = &game.assets.getTexture("lighter_enemy");
        break;
    case 3:
        enemies_render_states.texture = &game.assets.getTexture("paranoid_enemy");
        break;
    case 4:
        enemies_render_states.texture = &game.assets.getTexture("ufo_enemy");
        break;
    default:
        break;
    }
}

void GameState::setupBulletsRenderStates()
{
    switch(level)
    {
    case 1:
        bullets_render_states.texture = &game.assets.getTexture("long_bullets");
        break;
    case 2:
        bullets_render_states.texture = &game.assets.getTexture("long_bullets");
        break;
    case 3:
        bullets_render_states.texture = &game.assets.getTexture("rocket_bullet");
        break;
    case 4:
        bullets_render_states.texture = &game.assets.getTexture("star_bullet");
        break;
    default:
        break;
    }
}

void GameState::setupMusic()
{
    game.assets.getSound("explosion_sound").setVolume(game.game_settings.game_volume);
    music.setLoop(1);
    music.setVolume(game.game_settings.music_volume);
    music.openFromFile("assets/music/game_music.wav");
    music.play();
}

void GameState::setupHealthBar()
{
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
    std::unique_ptr<Enemy> new_enemy;
    switch (level)
    {
    case 1:
        new_enemy = std::make_unique<DoveEnemy>(game.assets, game.win, game.dt);
        break;
    case 2:
        new_enemy = std::make_unique<LighterEnemy>(game.assets, game.win, game.dt);
        break;
    case 3:
        new_enemy = std::make_unique<ParanoidEnemy>(game.assets, game.win, game.dt);
        break;
    case 4:
        new_enemy = std::make_unique<UFOEnemy>(game.assets, game.win, game.dt);
        break;
    default:
        break;
    }

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
    enemy_spawn_delay = DEFAULT_ENEMY_SPAWN_DELAY - (score / 25.f);
    gameOverEvent();
    enemies_batch.clear();
    for (auto& i : enemies)
        if (!i.get()->going_to_die)
            enemies_batch.append(i.get()->sprite);
    addBulletsToBatch();
}

void GameState::render()
{
    game.win.draw(background);
    game.win.draw(bullets_batch, bullets_render_states);
    game.win.draw(enemies_batch, enemies_render_states);
    game.win.draw(mother_ship);
    for (auto& i : enemies)
        game.win.draw(i.get()->explosion);
    game.win.draw(health_bar);
    game.win.draw(equations);
    game.win.draw(score_text);
}
