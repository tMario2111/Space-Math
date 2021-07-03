#include "AchievementsState.h"

AchievementsState::AchievementsState(Game& game, Background& background) :
    game(game),
    background(background)
{
    name = "Achievements";
}

void AchievementsState::update()
{
    background.update(game.dt.get());
    if(game.input.isKeyReleased(sf::Keyboard::Escape))
        game.states.pop();
}

void AchievementsState::render()
{
    game.win.draw(background);
}
