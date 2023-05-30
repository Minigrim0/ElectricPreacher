#include "scenes/new_game.hpp"

#include <core/log.hpp>
#include <UI/widgets/button.hpp>

NewGame::NewGame(MiniEngine::Application* a) : Scene(a, "NewGame") {}

NewGame::~NewGame() {}


void NewGame::init(MiniEngine::Application* a) {
    ME_INFO("Initializing new game");

    MiniEngine::UI::Widgets::Button* title_button = new MiniEngine::UI::Widgets::Button();
    MiniEngine::UI::Widgets::Button* start_button = new MiniEngine::UI::Widgets::Button();
    MiniEngine::UI::Widgets::Button* back_button = new MiniEngine::UI::Widgets::Button();

    title_button->set_size(200, 50);
    title_button->set_text("New Game");
    title_button->set_position(860, 100);
    title_button->set_text_color(150, 75, 75);

    start_button->set_size(200, 25);
    start_button->set_text("Start");
    start_button->set_position(860, 530);
    start_button->set_background_color(20, 20, 50);
    start_button->set_contour_color(50, 50, 150);
    start_button->set_text_color(150, 150, 150);

    back_button->set_size(200, 25);
    back_button->set_text("<- Back");
    back_button->set_position(20, 20);
    back_button->set_background_color(20, 50, 20);
    back_button->set_contour_color(50, 150, 50);
    back_button->set_text_color(150, 150, 150);

    m_scene->add_interactible(0, title_button);
    m_scene->add_interactible(1, start_button);
    m_scene->add_interactible(2, back_button);
}
