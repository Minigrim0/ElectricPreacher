#include "../includes/game.hpp"
#include <SDL2/SDL_keycode.h>

Game::Game(Screen* screen, NotificationCenter* notif_center, SDL_Event* event_handler)
:m_player(new Player),
m_map_manager(new MapManager),
m_screen(screen),
m_notification_center(notif_center),
m_event_handler(event_handler)
{}

Game::~Game(){}

void Game::init(Screen* screen){
    m_screen = screen;
    m_map_manager->load_map(screen, "assets/maps/start.json");
    m_map_manager->set_position(0, 0);
    m_map_manager->init(screen);
    m_player->init(screen);
    m_player->set_position(100, 100);
}

void Game::run(){
    m_in_game = true;

    while(m_in_game){
        draw();
        handle_events();
        update();
    }
}

void Game::draw(){
    m_map_manager->render(m_screen, {0, 0, 0, 0}); // m_player->get_position());
    m_player->draw(m_screen);
    m_notification_center->draw(m_screen);
}

void Game::handle_events(){
    while(SDL_PollEvent(m_event_handler) != 0){
        m_screen->handle_events(m_event_handler);
        m_player->update(m_event_handler);
        // Do updates
        switch(m_event_handler->type){
            case SDL_KEYDOWN:
                if(m_event_handler->key.keysym.sym == SDLK_ESCAPE) m_in_game = false;
                break;
            default:
                break;
        }

        m_notification_center->update(m_event_handler, m_screen);
    }
}

void Game::update(){
    m_notification_center->update(nullptr, m_screen);
    m_screen->update_screen();
}
