#ifndef EQUATIONS_H
#define EQUATIONS_H

#include <SFML/Graphics.hpp>
#include "../MKE/MKE.h"
#include <string>
#include <cmath>

class Equations : public sf::Drawable
{
public:
    Equations(mke::AssetManager& assets, sf::RenderWindow& win, mke::Random& random, mke::Input& input, mke::DeltaTime& dt, unsigned int level);
    bool correct_result = 0;
    unsigned int star_questions_count = 0;
    const unsigned int star_questions_target = 3;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update();
private:
    mke::AssetManager& assets;
    sf::RenderWindow& win;
    mke::Random& random;
    mke::Input& input;
    mke::DeltaTime& dt;
    unsigned int level;
    const float star_chance = 25.f;
    bool star_question = 0;
    sf::Sprite panel;
    sf::Sprite star;
    sf::Sprite star_counter_sprite;
    sf::Text equation;
    sf::Text result;
    sf::Text stars_counter_text;
    std::string result_string;
    std::string result_value;
    sf::Time skip_clock = sf::seconds(0.f);
    sf::Time skip_delay = sf::seconds(5.f);
    sf::Text skip_text;
    sf::Text skipped_question_result;
    const int star_question_decrement = 190;
    const int skipped_question_result_decrement = 45;
    enum OperationType
    {
        Sum,
        Subtraction,
        Multiply,
        Power,
        SquareRoot
    };
    void setupPanel();
    void setupStar();
    void setupTexts();
    void setupStarCounterSprite();
    std::string generateBasicMath();
    std::string generateEquation();
    std::string generateTrigonometry();
    std::string generateEverything();
    void generateQuestion();
    void updateSkippedQuestionResultAlpha();
    void updateStarQuestionAlpha();
};

#endif
