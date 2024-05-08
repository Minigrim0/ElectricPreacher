#include "scenes/main_menu.hpp"
#include "scenes/new_game.hpp"

#include <core/log.hpp>
#include <UI/widgets/button.hpp>


MainMenu::MainMenu(MiniEngine::Application* app) : AbstractScene(app, "MainMenu") {}

MainMenu::~MainMenu(){}

void MainMenu::start_new_game(){
    ME_INFO("starting new game");

    auto app = MiniEngine::Application::GetInstance();
    NewGame* new_game = new NewGame(app);
    new_game->init(app);
    new_game->start(app);
}

void MainMenu::load_game(){
    ME_INFO("loading game");
}

void MainMenu::quit_game(){
    ME_INFO("quitting game");
    auto app = MiniEngine::Application::GetInstance();
    app->stop();
}

void MainMenu::init(MiniEngine::Application* app) {
    ME_INFO("Initializing main menu");

    MiniEngine::UI::Widgets::Button* title_button = new MiniEngine::UI::Widgets::Button();
    MiniEngine::UI::Widgets::Button* new_button = new MiniEngine::UI::Widgets::Button();
    MiniEngine::UI::Widgets::Button* load_button = new MiniEngine::UI::Widgets::Button();
    MiniEngine::UI::Widgets::Button* quit_button = new MiniEngine::UI::Widgets::Button();

    title_button->set_size(200, 50);
    title_button->set_text("The Electric Preacher");
    title_button->set_position(860, 100);
    title_button->set_background_color(0, 0, 0, 0);
    title_button->set_text_color(200, 200, 200); 
    title_button->update_layout();

    new_button->set_size(200, 25);
    new_button->set_text("New Game");
    new_button->set_position(860, 485);
    new_button->set_background_color(20, 50, 20);
    new_button->set_text_color(150, 150, 150);
    new_button->set_contour_color(50, 150, 50);
    new_button->set_callback(std::bind(&MainMenu::start_new_game, this));
    new_button->update_layout();

    load_button->set_size(200, 25);
    load_button->set_text("Load Game");
    load_button->set_position(860, 530);
    load_button->set_text_color(150, 150, 150);
    load_button->set_background_color(20, 20, 50);
    load_button->set_contour_color(50, 50, 150);
    load_button->set_callback(std::bind(&MainMenu::load_game, this));
    load_button->update_layout();

    quit_button->set_size(200, 25);
    quit_button->set_text("Quit");
    quit_button->set_position(860, 575);
    quit_button->set_text_color(150, 150, 150);
    quit_button->set_background_color(50, 20, 20);
    quit_button->set_contour_color(150, 50, 50);
    quit_button->set_callback(std::bind(&MainMenu::quit_game, this));
    quit_button->update_layout();

    m_scene->add_interactible(0, title_button);
    m_scene->add_interactible(1, new_button);
    m_scene->add_interactible(1, load_button);
    m_scene->add_interactible(1, quit_button);
}
