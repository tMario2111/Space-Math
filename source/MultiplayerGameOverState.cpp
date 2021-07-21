#include "MultiplayerGameOverState.h"

MultiplayerGameOverState::MultiplayerGameOverState(Game& game, Background& background, Networking::UserType winner, sf::Image background_texture) :
    game(game),
    background(background),
    winner(winner)
{
    name = "MultiplayerGameOver";
    this->background_texture.loadFromImage(background_texture);
    background_sprite.setTexture(this->background_texture);
    background_sprite.setColor(sf::Color(100, 100, 100));
    setupText();
    setupButtons();
}

void MultiplayerGameOverState::setupText()
{
    game_over_text.setFont(game.assets.getFont("font"));
    game_over_text.setCharacterSize(50);
    if(game.networking.user_type == Networking::UserType::Host)
    {
        if(winner == Networking::UserType::Host)
            game_over_text.setString(game.networking.local_name + " WON!");
        else
            game_over_text.setString(game.networking.remote_name + " WON!");
    }
    else
    {
        if(winner == Networking::UserType::Client)
            game_over_text.setString(game.networking.local_name + " WON!");
        else
            game_over_text.setString(game.networking.remote_name + " WON!");
    }
    game_over_text.setOrigin(game_over_text.getLocalBounds().width / 2, game_over_text.getLocalBounds().height / 2);
    game_over_text.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 4);
}

void MultiplayerGameOverState::setupButtons()
{
    reset.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    reset.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    reset.body.setScale(1.5f, 1.5f);
    reset.setOriginsToCenter();
    reset.body.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2 - reset.body.getGlobalBounds().height / 2 - BUTTON_MARGIN / 2);
    reset.setupText(reset.text, game.assets.getFont("font"), 40, "TRY AGAIN", sf::Color::White);
    reset.centerTextToBody();

    main_menu.setTextures(game.assets.getTexture("button_pressed"), game.assets.getTexture("button_released"));
    main_menu.setFonts(game.assets.getFont("font"), game.assets.getFont("font"));
    main_menu.body.setScale(1.5f, 1.5f);
    main_menu.setOriginsToCenter();
    main_menu.body.setPosition(game.win.getSize().x / 2, game.win.getSize().y / 2 + main_menu.body.getGlobalBounds().height / 2 + BUTTON_MARGIN / 2);
    main_menu.setupText(main_menu.text, game.assets.getFont("font"), 40, "MAIN MENU", sf::Color::White);
    main_menu.centerTextToBody();
}

void MultiplayerGameOverState::update()
{
    if (main_menu.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left))
        game.states.popStatesUntil("MainMenu");
    else if (reset.selected(game.win) && game.input.isButtonReleased(sf::Mouse::Left));
}

void MultiplayerGameOverState::render()
{
    game.win.draw(background_sprite);
    game.win.draw(game_over_text);
    game.win.draw(reset);
    game.win.draw(main_menu);
}
