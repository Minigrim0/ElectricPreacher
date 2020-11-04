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
    m_map_manager->load_map("non");
    m_map_manager->set_position(200, 200);
    m_map_manager->init(screen);
}

void Game::run(){
    m_in_game = true;

    while(m_in_game){
        m_map_manager->render(m_screen, m_player->get_position());
        m_notification_center->draw(m_screen);

        while(SDL_PollEvent(m_event_handler) != 0){
            m_screen->handle_events(m_event_handler);
            // Do updates

            m_notification_center->update(m_event_handler, m_screen);
            if(m_event_handler->type == SDL_KEYUP){
                m_notification_center->create_notification("Keyup !", m_screen, "Roboto_16", 2500);
                if(m_event_handler->key.keysym.sym == SDLK_ESCAPE){
                    m_in_game = false;
                }
            }
        }
        m_notification_center->update(nullptr, m_screen);

        m_screen->update_screen();
    }
}
