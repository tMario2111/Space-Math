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
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update();
private:
    mke::AssetManager& assets;
    sf::RenderWindow& win;
    mke::Random& random;
    mke::Input& input;
    mke::DeltaTime& dt;
    unsigned int level;
    sf::RectangleShape frame;
    sf::Text equation;
    sf::Text result;
    std::string result_string;
    std::string result_value;
    sf::Time skip_clock = sf::seconds(0.f);
    sf::Time skip_delay = sf::seconds(5.f);
    sf::Text skip_text;
    sf::Text skipped_question_result;
    const int skipped_question_result_decrement = 45;
    enum OperationType
    {
        Sum,
        Subtraction,
        Multiply,
        Power,
        SquareRoot
    };
    void setupFrame();
    void setupTexts();
    std::string generateBasicMath();
    std::string generateEquation();
    std::string generateTrigonometry();
    std::string generateEverything();
    void generateQuestion();
    void updateSkippedQuestionResultAlpha();
};

#endif
