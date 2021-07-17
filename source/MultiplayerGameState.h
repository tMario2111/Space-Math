#ifndef MULTIPLAYERGAMESTATE_H
#define MULTIPLAYERGAMESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "../MKE/MKE.h"
#include <memory>
#include <vector>

#include "Game.h"
#include "Networking.h"
#include "Background.h"
#include "MotherShip.h"
#include "Enemy.h"
#include "UFOEnemy.h"

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
    sf::RenderStates enemies_render_states;
    sf::RenderStates bullets_render_states;
    mke::SpriteBatch enemies_batch;
    const float ENEMY_SPAWN_MARGIN = 100.f;
    MotherShip host_ship;
    MotherShip client_ship;
    std::vector<std::unique_ptr<Enemy>> host_enemies;
    std::vector<std::unique_ptr<Enemy>> client_enemies;
    unsigned int host_score;
    unsigned int client_score;
    sf::Time host_enemies_spawn_clock = sf::seconds(0.f);
    sf::Time client_enemies_spawn_clock = sf::seconds(0.f);
    sf::Time host_enemies_spawn_delay = sf::seconds(7.5f);
    sf::Time client_enemies_spawn_delay = sf::seconds(7.5f);
    void syncRandomSeed();
    void setupShips();
    void spawnHostEnemy();
    void spawnClientEnemy();
    void spawnEnemies();
    void addEnemiesToBatch();
};

#endif
