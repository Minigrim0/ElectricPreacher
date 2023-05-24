#include "scenes/main_menu.hpp"

MainMenu::MainMenu(MiniEngine::Application* app) : Scene(app, "MainMenu") {
    // ME_INFO("Creating main menu");
}

void callback(){
    // ME_INFO("Button pressed");
}

void add_button(MiniEngine::Scene* scene, int posx){
    MiniEngine::UI::Widgets::Button* button = new MiniEngine::UI::Widgets::Button();
    button->set_text("Hello World");
    button->set_position(100 + posx * 5, 100 + posx * 5);
    button->set_size(200, 50);
    button->set_background_color(255, 0, 0);
    button->set_text_color(0, 0, 0); 
    button->update_layout();

    button->set_callback(callback);
    scene->add_interactible(posx, button);
}

MainMenu::~MainMenu(){
    // ME_INFO("Destroying main menu");
}

void MainMenu::init(MiniEngine::Application* app){
    // ME_INFO("Initializing main menu");
    for(auto x = 0; x < 10; x++)
        add_button(m_scene, x);
}
