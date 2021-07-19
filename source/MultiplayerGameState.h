#ifndef MULTIPLAYERGAMESTATE_H
#define MULTIPLAYERGAMESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "../MKE/MKE.h"
#include <memory>
#include <vector>
#include <thread>

#include "Game.h"
#include "Networking.h"
#include "Background.h"
#include "MotherShip.h"
#include "Enemy.h"
#include "UFOEnemy.h"
#include "Equations.h"

class Game;

class MultiplayerGameState : public mke::State
{
public:
    MultiplayerGameState(Game& game, Background& background, unsigned int level);
    void update();
    void render();
private:
    Game& game;
    Background& background;
    unsigned int level;
    mke::Random host_enemies_random;
    mke::Random client_enemies_random;
    mke::Random questions_random;
    sf::RenderStates enemies_render_states;
    sf::RenderStates bullets_render_states;
    sf::Text host_name_text;
    sf::Text client_name_text;
    mke::SpriteBatch enemies_batch;
    mke::SpriteBatch bullets_batch;
    const float ENEMY_SPAWN_MARGIN = 100.f;
    Equations equations;
    MotherShip host_ship;
    MotherShip client_ship;
    unsigned int host_score = 0;
    unsigned int client_score = 0;
    std::vector<std::unique_ptr<Enemy>> host_enemies;
    std::vector<std::unique_ptr<Enemy>> client_enemies;
    sf::Time host_enemies_spawn_clock = sf::seconds(0.f);
    sf::Time client_enemies_spawn_clock = sf::seconds(0.f);
    sf::Time host_enemies_spawn_delay = sf::seconds(7.5f);
    sf::Time client_enemies_spawn_delay = sf::seconds(7.5f);
    std::thread receive_thread;
    void syncRandomSeed();
    void syncNames();
    void setupShips();
    void setupTexts();
    void spawnHostEnemy();
    void spawnClientEnemy();
    void spawnEnemies();
    void receiveUpdates();
    void sendUpdates();
    void addEnemiesToBatch();
    void addBulletsToBatch();
    void collisionHostBulletsMothership();
    void collisionClientBulletsMothership();
    void deleteEnemies();
};

#endif
