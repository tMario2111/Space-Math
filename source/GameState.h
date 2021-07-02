#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../MKE/MKE.h"
#include <vector>
#include <memory>
#include "../Collision.h"

#include "Game.h"
#include "Background.h"
#include "MotherShip.h"
#include "Enemy.h"
#include "DoveEnemy.h"
#include "LighterEnemy.h"
#include "ParanoidEnemy.h"
#include "UFOEnemy.h"
#include "ProgressBar.h"
#include "Equations.h"
#include "PauseMenuState.h"
#include "GameOverState.h"
#include "FireBarrierAbility.h"
class Game;
class MotherShip;

class GameState : public mke::State
{
public:
    GameState(Game& game, Background& background, unsigned int level);
    void update();
    void render();
private:
    Game& game;
    Background& background;
    unsigned int level;
    MotherShip mother_ship;
    const float ENEMY_SPAWN_MARGIN = 100.f;
    float enemies_spawn_clock = 0;
    float enemy_spawn_delay = 7.5f;
    const float DEFAULT_ENEMY_SPAWN_DELAY = 7.5f;
    unsigned int score = 0;
    sf::Text score_text;
    ProgressBar health_bar;
    sf::Music music;
    sf::Time music_timestamp;
    std::vector<std::unique_ptr<Enemy>> enemies;
    mke::SpriteBatch enemies_batch;
    sf::RenderStates enemies_render_states;
    sf::RenderStates bullets_render_states;
    mke::SpriteBatch bullets_batch;
    Equations equations;
    sf::RectangleShape damage_effect;
    FireBarrierAbility fire_barrier_ability;
    void setupBackground();
    void setupEnemiesRenderStates();
    void setupBulletsRenderStates();
    void setupMusic();
    void setupHealthBar();
    void setupScore();
    void setupDamageEffect();
    void pauseMenuEvent();
    void gameOverEvent();
    void spawnEnemy();
    void spawnEnemies();
    void deleteEnemies();
    void addBulletsToBatch();
    void collisionBulletsMothership();
    void collisionBulletsFireBarrierAbility();
    void updateDamageEffect();
};

#endif
