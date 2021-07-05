#include "AchievementsState.h"

AchievementsState::AchievementsState(Game& game, Background& background) :
    game(game),
    background(background)
{
    name = "Achievements";
    setupButtons();
    setupAchievements();
}

void AchievementsState::setupButtons()
{
    back_.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    back_.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    back_.body.setScale(0.5f, 1.f);
    back_.setOriginsToCenter();
    back_.body.setPosition(back_.body.getGlobalBounds().width / 2 + 20.f, back_.body.getGlobalBounds().height / 2 + 20.f);
    back_.setupText(back_.text, game.assets.getFont("font"), 20, "BACK", sf::Color::White);
    back_.centerTextToBody();
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
    if (back_.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.pop();
}

void AchievementsState::render()
{
    game.win.draw(background);
    game.win.draw(back_);
    for (auto& i : achievements)
    {
        game.win.draw(i.first);
        game.win.draw(i.second);
    }
}
