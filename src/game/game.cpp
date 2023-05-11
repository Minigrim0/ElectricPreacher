#include "game/game.hpp"
#include <SDL_keycode.h>

Game::Game(NotificationCenter* notif_center, SDL_Event* event_handler)
:m_player(new Player),
m_map_manager(new MapManager),
m_notification_center(notif_center),
m_event_handler(event_handler)
{}

Game::~Game(){}

void Game::init(){
    Screen* screen = Screen::GetInstance("Electric Preacher");

    // Load the map
    m_map_manager->load(screen, "assets/maps/start.json");
    m_map_manager->set_position(0, 0);
    m_map_manager->init(screen);

    // Load the player
    m_player->init(screen);
    m_player->set_position(96, 96);
}

void Game::run(){
    m_in_game = true;
    // Avoid querying for the singleton at each loop, ask once in the begining
    Screen* screen = Screen::GetInstance("Electric Preacher");

    while(m_in_game){
        draw(screen);
        handle_events(screen);
        update(screen);
    }
}

void Game::draw(Screen* screen){
    m_map_manager->render(screen); // m_player->get_position());
    m_player->draw(screen);
    m_notification_center->draw(screen);
}

void Game::handle_events(Screen* screen){
    while(SDL_PollEvent(m_event_handler) != 0){
        screen->handle_events(m_event_handler);
        m_player->update(m_event_handler);
        // Do updates
        switch(m_event_handler->type){
            case SDL_KEYDOWN:
                if(m_event_handler->key.keysym.sym == SDLK_ESCAPE) m_in_game = false;
                break;
            default:
                break;
        }

        m_notification_center->update(m_event_handler, screen);
    }
}

void Game::update(Screen* screen){
    m_notification_center->update(nullptr, screen);
    screen->update_screen();
}
