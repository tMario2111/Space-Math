#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include <map>

namespace mke
{
class Input
{
public:
    Input();
    char last_pressed_key;
    void update();
    void addPressedKey(sf::Keyboard::Key key);
    void addReleasedKey(sf::Keyboard::Key key);
    void addPressedButton(sf::Mouse::Button button);
    void addReleasedButton(sf::Mouse::Button button);
    bool isKeyPressed(sf::Keyboard::Key key);
    bool isKeyReleased(sf::Keyboard::Key key);
    bool isButtonPressed(sf::Mouse::Button button);
    bool isButtonReleased(sf::Mouse::Button button);
private:
    enum KeyState
    {
        None,
        Pressed,
        Released
    };
    std::map<sf::Keyboard::Key, KeyState> keyboard_input;
    std::map<sf::Mouse::Button, KeyState> mouse_input;
};
}

#endif
