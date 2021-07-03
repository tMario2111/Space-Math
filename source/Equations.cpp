#include "Equations.h"

Equations::Equations(mke::AssetManager& assets, sf::RenderWindow& win, mke::Random& random, mke::Input& input, mke::DeltaTime& dt, unsigned int level) :
    assets(assets),
    win(win),
    random(random),
    input(input),
    dt(dt),
    level(level)
{
    setupPanel();
    setupStar();
    setupStarCounterSprite();
    setupTexts();
    generateQuestion();
}

void Equations::setupPanel()
{
    panel.setTexture(assets.getTexture("panel"));
    panel.setOrigin(panel.getLocalBounds().width / 2, panel.getLocalBounds().height / 2);
    panel.setScale(1.1f,1.f);
    panel.setPosition(win.getSize().x / 2, win.getSize().y / 1.1f);
}

void Equations::setupStar()
{
    star.setTexture(assets.getTexture("star"));
    star.setOrigin(star.getLocalBounds().width / 2, star.getLocalBounds().height / 2);
    star.setScale(0.125f, 0.125f);
    star.setPosition(panel.getGlobalBounds().left + 0.9f * panel.getGlobalBounds().width,
                     panel.getGlobalBounds().top + 0.4f * panel.getGlobalBounds().height );
}

void Equations::setupTexts()
{
    equation.setFont(assets.getFont("font"));
    equation.setCharacterSize(35);
    equation.setPosition(-1000.f, -1000.f);
    result.setFont(assets.getFont("font"));
    result.setCharacterSize(35);
    result.setPosition(-1000.f, -1000.f);
    skip_text.setFont(assets.getFont("font"));
    skip_text.setCharacterSize(20);
    skip_text.setPosition(-1000.f, -1000.f);
    skipped_question_result.setFont(assets.getFont("font"));
    skipped_question_result.setCharacterSize(20);
    skipped_question_result.setPosition(-1000.f, -1000.f);
    skipped_question_result.setFillColor(sf::Color(255, 255, 255, 0));
    stars_counter_text.setFont(assets.getFont("font"));
    stars_counter_text.setCharacterSize(40);
    stars_counter_text.setString("0/3");
    stars_counter_text.setPosition(win.getSize().x - stars_counter_text.getGlobalBounds().width - 15.f - star_counter_sprite.getGlobalBounds().width, 10.f);
}

void Equations::setupStarCounterSprite()
{
    star_counter_sprite.setTexture(assets.getTexture("star"));
    star_counter_sprite.setScale(0.1f, 0.1f);
    star_counter_sprite.setPosition(win.getSize().x - star_counter_sprite.getGlobalBounds().width - 10.f, 17.5f);
}

std::string Equations::generateBasicMath()
{
    std::string equation;
    OperationType type = static_cast<OperationType>(random.getInt(0, 4));
    int num1, num2;
    switch (type)
    {
    case OperationType::Sum:
        num1 = random.getInt(10, 500);
        num2 = random.getInt(10, 500);
        equation += std::to_string(num1) + " + " + std::to_string(num2);
        result_value = std::to_string(num1 + num2);
        break;
    case OperationType::Subtraction:
        num1 = random.getInt(10, 500);
        num2 = random.getInt(10, 500);
        if (num1 > num2)
            equation += std::to_string(num1) + " - " + std::to_string(num2);
        else
            equation += std::to_string(num2) + " - " + std::to_string(num1);
        result_value = std::to_string(abs(num1 - num2));
        break;
    case OperationType::Multiply:
        num1 = random.getInt(2, 20);
        num2 = random.getInt(2, 20);
        equation += std::to_string(num1) + " * " + std::to_string(num2);
        result_value = std::to_string(num1 * num2);
        break;
    case OperationType::Power:
        num1 = random.getInt(2, 15);
        num2 = 2;
        equation += std::to_string(num1) + " ^ " + std::to_string(num2);
        result_value = std::to_string(num1 * num1);
        break;
    case OperationType::SquareRoot:
        num1 = random.getInt(2, 15);
        num2 = 2;
        equation += "sqrt " + std::to_string(num1 * num1);
        result_value = std::to_string(num1);
        break;
    }
    equation += " = ";
    return equation;
}

std::string Equations::generateEquation()
{
    std::string equation;
    /// ax + b = c + dx
    int x, a, b, c, d;
    x = random.getInt(1, 25);
    result_value = std::to_string(x);
    do
        a = random.getInt(-5, 5);
    while (a == 0);
    do
        b = random.getInt(-25, 25);
    while (b == 0);
    do
        c = a * x + b;
    while (c == 0);
    do
        d = random.getInt(-5, 5);
    while (d == 0);
    d *= -1;
    a += d;
    equation = std::to_string(a) + "x" + (b >= 0 ? "+" : "") + std::to_string(b) + "=" + std::to_string(c) + (d >= 0 ? "+" : "") +
               std::to_string(d) + "x";
    return equation;
}

std::string Equations::generateTrigonometry()
{
    std::string equation;
    std::vector<int> angles = {0, 30, 45, 60, 90, 120, 135, 150, 180, 210, 225, 240, 270, 300, 315, 330, 360};

    std::vector<std::string> sin_results = {"0", "1/2", "sqrt2/2", "sqrt3/2", "1", "sqrt3/2", "sqrt2/2", "1/2", "0", "-1/2", "-sqrt2/2", "-sqrt3/2",
                                            "-1",  "-sqrt3/2", "-sqrt2/2", "-1/2", "0"
                                           };
    std::vector<std::string> cos_results = {"1", "sqrt3/2", "sqrt2/2", "1/2", "0", "-1/2", "-sqrt2/2", "-sqrt3/2", "-1", "-sqrt3/2", "-sqrt2/2",
                                            "-1/2","0", "1/2", "sqrt2/2", "sqrt3/2","1"
                                           };
    std::vector<std::string> tg_results = {"0", "sqrt3/3", "1", "sqrt3", "-", "-sqrt3", "-1", "-sqrt3/3", "0", "sqrt3/3", "1", "sqrt3", "-", "-sqrt3",
                                           "-1", "-sqrt3/3", "0"
                                          };
    std::vector<std::string> ctg_results = {"-", "sqrt3", "1", "sqrt3/3", "0", "-sqrt3/3", "-1", "-sqrt3", "-", "sqrt3", "1", "sqrt3/3", "0", "-sqrt3/3",
                                            "-1", "-sqrt3", "-"
                                           };
    enum TrigonometricFunction
    {
        Sin,
        Cos,
        Tg,
        Ctg
    } Function;
    int index = random.getInt(0,angles.size() - 1);
    int angle = angles[index];
    Function = static_cast<TrigonometricFunction>(random.getInt(0,3));
    switch (Function)
    {
    case TrigonometricFunction::Sin:
        equation = "sin" + std::to_string(angle);
        result_value = sin_results[index];
        break;
    case TrigonometricFunction::Cos:
        equation = "cos" + std::to_string(angle);
        result_value = cos_results[index];
        break;
    case TrigonometricFunction::Tg:
        equation = "tg" + std::to_string(angle);
        result_value = tg_results[index];
        break;
    case TrigonometricFunction::Ctg:
        equation = "ctg" + std::to_string(angle);
        result_value = ctg_results[index];
        break;
    default:
        break;
    }
    return equation;
}

std::string Equations::generateEverything()
{
    std::string equation;
    int rand = random.getInt(1,3);
    switch(rand)
    {
    case 1:
        equation = generateBasicMath();
        break;
    case 2:
        equation = generateEquation();
        break;
    case 3:
        equation = generateTrigonometry();
        break;
    default:
        break;
    }

    return equation;
}

void Equations::generateQuestion()
{
    float r = random.getFloat(0.f, 100.f);
    star_question = r <= star_chance ? 1 : 0;
    star.setColor(sf::Color(255, 255, 255, 190));
    std::string str;
    switch (level)
    {
    case 1:
        str = generateBasicMath();
        break;
    case 2:
        str = generateEquation();
        break;
    case 3:
        str = generateTrigonometry();
        break;
    case 4:
        str = generateEverything();
        break;
    default:
        break;
    }
    this->equation.setString(str);
}

void Equations::updateSkippedQuestionResultAlpha()
{
    int alpha = skipped_question_result.getFillColor().a - skipped_question_result_decrement * dt.get().asSeconds();
    alpha = alpha < 0 ? 0 : alpha;
    skipped_question_result.setFillColor(sf::Color(255, 255, 255, alpha));
}

void Equations::updateStarQuestionAlpha()
{
    int alpha = star.getColor().a - star_question_decrement * dt.get().asSeconds();
    alpha = alpha < 0 ? 0 : alpha;
    star.setColor(sf::Color(255, 255, 255, alpha));
}

void Equations::update()
{
    skip_clock += dt.get();

    equation.setOrigin(equation.getLocalBounds().width / 2, equation.getLocalBounds().height / 2);
    mke::utility::centerBothAxes(equation, panel.getPosition().x - panel.getGlobalBounds().width / 2, panel.getPosition().x,
                                 panel.getPosition().y - panel.getGlobalBounds().height + 55.f, panel.getPosition().y + panel.getGlobalBounds().height);
    result.setString(result_string);
    result.setOrigin(result.getLocalBounds().width / 2, result.getLocalBounds().height / 2);
    mke::utility::centerBothAxes(result, panel.getPosition().x, panel.getPosition().x + panel.getGlobalBounds().width / 2,
                                 panel.getPosition().y - panel.getGlobalBounds().height + 55.f, panel.getPosition().y + panel.getGlobalBounds().height);
    stars_counter_text.setString(std::string(std::to_string(star_questions_count) + "/" + std::to_string(star_questions_target)));
    for (int i = sf::Keyboard::Num0; i <= sf::Keyboard::Num9; i++)
        if (input.isKeyReleased(static_cast<sf::Keyboard::Key>(i)))
            result_string += std::to_string(i - sf::Keyboard::Num0);
    for (int i = sf::Keyboard::Numpad0; i <= sf::Keyboard::Numpad9; i++)
        if (input.isKeyReleased(static_cast<sf::Keyboard::Key>(i)))
            result_string += std::to_string(i - sf::Keyboard::Numpad0);
    if (input.isKeyReleased(sf::Keyboard::BackSpace))
        result_string = result_string.substr(0, result_string.size() - 1);
    if (input.isKeyReleased(sf::Keyboard::S))
        result_string += "sqrt";
    if (input.isKeyReleased(sf::Keyboard::Slash) || input.isKeyReleased(sf::Keyboard::Divide))
        result_string += "/";
    if (input.isKeyReleased(sf::Keyboard::Dash) || input.isKeyReleased(sf::Keyboard::Subtract))
        result_string += "-";
    if ((input.isKeyReleased(sf::Keyboard::C)))
        result_string.clear();
    if (result_string.compare(result_value) == 0)
    {
        if(star_question)
            star_questions_count++;
        result_string.clear();
        correct_result = 1;
        skip_clock = sf::seconds(0.f);
        generateQuestion();
    }
    int remaining_time = ceil(skip_delay.asSeconds() - skip_clock.asSeconds());
    if (remaining_time > 0)
        skip_text.setString(std::to_string(remaining_time));
    else
        {
            skip_text.setString("PRESS ENTER TO SKIP");
            star_question = 0;
        }
    mke::utility::centerBothAxes(skip_text, panel.getPosition().x, panel.getPosition().x,
    panel.getPosition().y - panel.getGlobalBounds().height / 2 + 70.f, panel.getPosition().y - 25.f);
    updateSkippedQuestionResultAlpha();
    if( remaining_time <= 1.f && star_question)
        updateStarQuestionAlpha();
    if (remaining_time <= 0 && input.isKeyReleased(sf::Keyboard::Enter))
    {
        result_string.clear();
        skip_clock = sf::seconds(0.f);
        skipped_question_result.setString("RIGHT ANSWER: " + result_value);
        skipped_question_result.setPosition(0.f, panel.getGlobalBounds().top + skipped_question_result.getGlobalBounds().height + 3.f);
        mke::utility::centerXAxis(skipped_question_result, panel.getGlobalBounds().left, panel.getGlobalBounds().left + panel.getGlobalBounds().width);
        skipped_question_result.setFillColor(sf::Color(255, 255, 255, 255));
        generateQuestion();
    }

}

void Equations::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(panel, states);
    if(star_question)
        target.draw(star);
    target.draw(skip_text);
    target.draw(equation);
    target.draw(result);
    target.draw(skipped_question_result);
    target.draw(stars_counter_text);
    target.draw(star_counter_sprite);
}
