#include "AchievementsState.h"

AchievementsState::AchievementsState(Game& game, Background& background) :
    game(game),
    background(background)
{
    name = "Achievements";
    setupAchievements();
}

void AchievementsState::setupAchievements()
{
    const float MARGIN = 50.f;
    tinyxml2::XMLElement* root = game.game_settings.doc.FirstChildElement("achievements");
    for (tinyxml2::XMLElement* i = root->FirstChildElement("achievement"); i != 0; i = i->NextSiblingElement("achievement"))
    {
        bool done;
        i->FirstChildElement("done")->QueryBoolText(&done);
        std::pair<sf::Text, sf::Text> achievement;
        achievement.first.setFont(game.assets.getFont("font"));
        achievement.first.setCharacterSize(40);
        achievement.first.setFillColor(done ? sf::Color(255, 255, 255) : sf::Color(100, 100, 100));
        achievement.first.setString(i->FirstChildElement("title")->GetText());
        achievement.second.setFont(game.assets.getFont("font"));
        achievement.second.setCharacterSize(20);
        achievement.second.setFillColor(done ? sf::Color(255, 255, 255) : sf::Color(100, 100, 100));
        achievement.second.setString(i->FirstChildElement("text")->GetText());
        if (achievements.size() == 0)
            achievement.first.setPosition(game.win.getSize().x / 6, game.win.getSize().y / 6);
        else
        {
            auto& above = achievements[achievements.size() - 1];
            achievement.first.setPosition(above.first.getPosition().x,
                        above.second.getGlobalBounds().top + above.second.getGlobalBounds().height + MARGIN);
        }
        achievement.second.setPosition(achievement.first.getPosition().x,
                        achievement.first.getGlobalBounds().top + achievement.first.getGlobalBounds().height);
        achievements.push_back(achievement);
    }
}

void AchievementsState::update()
{
    background.update(game.dt.get());
    if (game.input.isKeyReleased(sf::Keyboard::Escape))
        game.states.pop();
}

void AchievementsState::render()
{
    game.win.draw(background);
    for (auto& i : achievements)
    {
        game.win.draw(i.first);
        game.win.draw(i.second);
    }
}
