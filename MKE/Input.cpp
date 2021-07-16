#include "Input.h"

namespace mke
{
Input::Input()
{

}

void Input::update()
{
    last_pressed_key = 0;
    for (auto& i : keyboard_input)
        if (i.second == KeyState::Released)
            i.second = KeyState::None;
    for (auto& i : mouse_input)
        if (i.second == KeyState::Released)
            i.second = KeyState::None;
}

void Input::addPressedKey(sf::Keyboard::Key key)
{
    keyboard_input[key] = KeyState::Pressed;
}

void Input::addReleasedKey(sf::Keyboard::Key key)
{
    keyboard_input[key] = KeyState::Released;
}

void Input::addPressedButton(sf::Mouse::Button button)
{
    mouse_input[button] = KeyState::Pressed;
}

void Input::addReleasedButton(sf::Mouse::Button button)
{
    mouse_input[button] = KeyState::Released;
}

bool Input::isKeyPressed(sf::Keyboard::Key key)
{
    return keyboard_input[key] == KeyState::Pressed;
}

bool Input::isKeyReleased(sf::Keyboard::Key key)
{
    return keyboard_input[key] == KeyState::Released;
}

bool Input::isButtonPressed(sf::Mouse::Button button)
{
    return mouse_input[button] == KeyState::Pressed;
}

bool Input::isButtonReleased(sf::Mouse::Button button)
{
    return mouse_input[button] == KeyState::Released;
}
}
