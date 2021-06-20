#include "SettingsState.h"

SettingsState::SettingsState(Game& game, Background& background) :
    game(game),
    background(background)
{
    name = "SettingsState";
    setupTexts();
    setupButtons();
}

void SettingsState::setupTexts()

{
    music_volume.setFont(game.assets.getFont("font"));
    music_volume.setCharacterSize(40);
    music_volume.setString(std::to_string(game.game_settings.music_volume));
    music_volume.setOrigin(music_volume.getLocalBounds().width / 2, music_volume.getLocalBounds().height / 2);
    music_volume.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2 - BUTTON_MARGIN);

    music_volume_text.setFont(game.assets.getFont("font"));
    music_volume_text.setCharacterSize(40);
    music_volume_text.setString("MUSIC VOLUME");
    music_volume_text.setOrigin(music_volume_text.getLocalBounds().width / 2, music_volume_text.getLocalBounds().height / 2);
    music_volume_text.setPosition(music_volume.getPosition().x, music_volume.getPosition().y - 2 * music_volume.getGlobalBounds().height);

    game_volume.setFont(game.assets.getFont("font"));
    game_volume.setCharacterSize(40);
    game_volume.setString(std::to_string(game.game_settings.game_volume));
    game_volume.setOrigin(game_volume.getLocalBounds().width / 2, game_volume.getLocalBounds().height / 2);
    game_volume.setPosition(game.win.getSize().x / 2, music_volume.getPosition().y - music_volume.getGlobalBounds().height - music_volume_text.getLocalBounds().height - 2 * BUTTON_MARGIN);

    game_volume_text.setFont(game.assets.getFont("font"));
    game_volume_text.setCharacterSize(40);
    game_volume_text.setString("SOUND FX VOLUME");
    game_volume_text.setOrigin(game_volume_text.getLocalBounds().width / 2, game_volume_text.getLocalBounds().height / 2);
    game_volume_text.setPosition(game_volume.getPosition().x, game_volume.getPosition().y - 2 * game_volume.getGlobalBounds().height);

    sqrt_key.setFont(game.assets.getFont("font"));
    sqrt_key.setCharacterSize(40);
    sqrt_key.setString("PRESS \"S\" TO INSERT \"sqrt\" ");
    sqrt_key.setOrigin(sqrt_key.getLocalBounds().width / 2, sqrt_key.getLocalBounds().height / 2);
    sqrt_key.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2 + 2 * BUTTON_MARGIN);

    clear_key.setFont(game.assets.getFont("font"));
    clear_key.setCharacterSize(40);
    clear_key.setString("PRESS \"C\" TO CLEAR INPUT");
    clear_key.setOrigin(clear_key.getLocalBounds().width / 2, clear_key.getLocalBounds().height / 2);
    clear_key.setPosition(game.win.getSize().x / 2, sqrt_key.getPosition().y + sqrt_key.getGlobalBounds().height / 2 + BUTTON_MARGIN);

    show_fps_key.setFont(game.assets.getFont("font"));
    show_fps_key.setCharacterSize(40);
    show_fps_key.setString("PRESS \"F\" TO SHOW FPS COUNTER");
    show_fps_key.setOrigin(show_fps_key.getLocalBounds().width / 2, show_fps_key.getLocalBounds().height / 2);
    show_fps_key.setPosition(game.win.getSize().x / 2, clear_key.getPosition().y + clear_key.getGlobalBounds().height / 2 + BUTTON_MARGIN);
}

void SettingsState::setupButtons()
{
    game_volume_l.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    game_volume_l.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    game_volume_l.body.setScale(1.5f, 1.5f);
    game_volume_l.setOriginsToCenter();
    game_volume_l.body.setScale(0.5f, 1.f);
    game_volume_l.body.setPosition(game_volume.getPosition().x - game_volume_l.body.getGlobalBounds().width, game_volume.getPosition().y + 10.f);
    game_volume_l.setupText(game_volume_l.text, game.assets.getFont("font"), 40, "<", sf::Color::White);
    game_volume_l.centerTextToBody();

    game_volume_r.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    game_volume_r.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    game_volume_r.body.setScale(1.5f, 1.5f);
    game_volume_r.setOriginsToCenter();
    game_volume_r.body.setScale(0.5f, 1.f);
    game_volume_r.body.setPosition(game_volume.getPosition().x + game_volume_r.body.getGlobalBounds().width, game_volume.getPosition().y + 10.f);
    game_volume_r.setupText(game_volume_r.text, game.assets.getFont("font"), 40, ">", sf::Color::White);
    game_volume_r.centerTextToBody();

    music_volume_l.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    music_volume_l.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    music_volume_l.body.setScale(1.5f, 1.5f);
    music_volume_l.setOriginsToCenter();
    music_volume_l.body.setScale(0.5f, 1.f);
    music_volume_l.body.setPosition(music_volume.getPosition().x - music_volume_l.body.getGlobalBounds().width, music_volume.getPosition().y + 10.f);
    music_volume_l.setupText(music_volume_l.text, game.assets.getFont("font"), 40, "<", sf::Color::White);
    music_volume_l.centerTextToBody();

    music_volume_r.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    music_volume_r.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    music_volume_r.body.setScale(1.5f, 1.5f);
    music_volume_r.setOriginsToCenter();
    music_volume_r.body.setScale(0.5f, 1.f);
    music_volume_r.body.setPosition(music_volume.getPosition().x + music_volume_r.body.getGlobalBounds().width, music_volume.getPosition().y + 10.f);
    music_volume_r.setupText(music_volume_r.text, game.assets.getFont("font"), 40, ">", sf::Color::White);
    music_volume_r.centerTextToBody();

    back_.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    back_.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    back_.body.setScale(0.5f, 1.f);
    back_.setOriginsToCenter();
    back_.body.setPosition(back_.body.getGlobalBounds().width / 2 + 20.f, back_.body.getGlobalBounds().height / 2 + 20.f);
    back_.setupText(back_.text, game.assets.getFont("font"), 20, "BACK", sf::Color::White);
    back_.centerTextToBody();
}

void SettingsState::update()
{
    game_volume.setOrigin(game_volume.getLocalBounds().width / 2, game_volume.getLocalBounds().height / 2);
    music_volume.setOrigin(music_volume.getLocalBounds().width / 2, music_volume.getLocalBounds().height / 2);
    game_volume.setString(std::to_string(game.game_settings.game_volume));
    music_volume.setString(std::to_string(game.game_settings.music_volume));
    background.update(game.dt.get());
    if (game.input.isKeyReleased(sf::Keyboard::Escape))
    {
        game.game_settings.saveDoc("data/data.dat");
        game.states.pop();
    }
    if (game_volume_l.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left) && game.game_settings.game_volume > 0)
        game.game_settings.game_volume -= 5;
    if (game_volume_r.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left) && game.game_settings.game_volume < 100)
        game.game_settings.game_volume += 5;
    if (music_volume_l.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left) && game.game_settings.music_volume > 0)
        game.game_settings.music_volume -= 5;
    if (music_volume_r.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left) && game.game_settings.music_volume < 100)
        game.game_settings.music_volume += 5;
    if (back_.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.pop();
}

void SettingsState::render()
{
    game.win.draw(background);
    game.win.draw(game_volume_text);
    game.win.draw(game_volume);
    game.win.draw(game_volume_l);
    game.win.draw(game_volume_r);
    game.win.draw(music_volume_text);
    game.win.draw(music_volume);
    game.win.draw(music_volume_l);
    game.win.draw(music_volume_r);
    game.win.draw(sqrt_key);
    game.win.draw(clear_key);
    game.win.draw(back_);
    game.win.draw(show_fps_key);
}
