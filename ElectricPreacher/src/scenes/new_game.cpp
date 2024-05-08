#include "scenes/new_game.hpp"

#include "game/game.hpp"

#include <core/log.hpp>
#include <UI/widgets/button.hpp>

NewGame::NewGame(MiniEngine::Application* a) : AbstractScene(a, "NewGame") {}

NewGame::~NewGame() {}

void NewGame::return_to_main_menu() {
    ME_INFO("returning to main menu");

    auto app = MiniEngine::Application::GetInstance();
    app->set_active_scene("MainMenu");
}

void NewGame::start_game() {
    ME_INFO("starting game");
    auto app = MiniEngine::Application::GetInstance();

    Game *game = new Game(app);
    game->init(app);
    game->start(app);
}

void NewGame::init(MiniEngine::Application* a) {
    ME_INFO("Initializing new game");

    MiniEngine::UI::Widgets::Button* title_button = new MiniEngine::UI::Widgets::Button();
    MiniEngine::UI::Widgets::Button* start_button = new MiniEngine::UI::Widgets::Button();
    MiniEngine::UI::Widgets::Button* back_button = new MiniEngine::UI::Widgets::Button();

    title_button->set_size(200, 50);
    title_button->set_text("New Game");
    title_button->set_position(860, 100);
    title_button->set_text_color(150, 75, 75);
    title_button->update_layout();

    start_button->set_size(200, 25);
    start_button->set_text("Start");
    start_button->set_position(860, 530);
    start_button->set_background_color(20, 20, 50);
    start_button->set_contour_color(50, 50, 150);
    start_button->set_text_color(150, 150, 150);
    start_button->set_callback(std::bind(&NewGame::start_game, this));
    start_button->update_layout();

    back_button->set_size(200, 25);
    back_button->set_text("<- Back");
    back_button->set_position(20, 20);
    back_button->set_background_color(20, 50, 20);
    back_button->set_contour_color(50, 150, 50);
    back_button->set_text_color(150, 150, 150);
    back_button->set_callback(std::bind(&NewGame::return_to_main_menu, this));
    back_button->update_layout();

    m_scene->add_interactible(0, title_button);
    m_scene->add_interactible(1, start_button);
    m_scene->add_interactible(2, back_button);
}
