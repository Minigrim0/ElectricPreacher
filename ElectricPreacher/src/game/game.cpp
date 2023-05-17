#include "game/game.hpp"

#include <SDL_keycode.h>

Game* Game::game_ = nullptr;

Game::Game()
:m_in_game(false),
m_player(new Player),
m_map_manager(new MapManager),
m_event_handler(new SDL_Event)
{}

Game::~Game(){}

Game *Game::GetInstance(){
    if(game_ == nullptr){
        game_ = new Game();
    }
    return game_;
}

void Game::init(){
    CORE::Screen* screen = CORE::Screen::GetInstance(PROJECT_NAME);

    // Load the map
    m_map_manager->load(screen, "assets/maps/start.json");
    m_map_manager->set_position(0, 0);
    m_map_manager->init(screen);

    // Load the player
    m_player->init(screen);
    m_player->set_position(2, 2);
}

void Game::run(){
    m_in_game = true;
    // Avoid querying for the singleton at each loop, ask once in the begining
    CORE::Screen* screen = CORE::Screen::GetInstance(PROJECT_NAME);
    UI::NotificationCenter* notification_center = UI::NotificationCenter::GetInstance();

    while(m_in_game){
        handle_events(screen, notification_center);
        draw(screen, notification_center);
        update(screen, notification_center);
    }
}

void Game::draw(CORE::Screen* sc, UI::NotificationCenter* nc){
    m_map_manager->render(sc); // m_player->get_position());
    m_player->draw(sc);

    nc->draw(sc);
}

void Game::handle_events(CORE::Screen* sc, UI::NotificationCenter* nc){
    while(SDL_PollEvent(m_event_handler) != 0){
        sc->handle_events(m_event_handler);
        m_player->handle_event(m_event_handler);
        // Do updates
        switch(m_event_handler->type){
            case SDL_KEYDOWN:
                if(m_event_handler->key.keysym.sym == SDLK_ESCAPE) m_in_game = false;
                break;
            default:
                break;
        }

        nc->update(m_event_handler, sc);
    }
}

void Game::update(CORE::Screen* sc, UI::NotificationCenter* nc){
    nc->update(nullptr, sc);

    m_player->update(sc);
    sc->update_screen();
}
