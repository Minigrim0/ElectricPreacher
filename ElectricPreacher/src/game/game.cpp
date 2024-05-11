#include "game/game.hpp"

#include <SDL_keycode.h>

Game::Game(MiniEngine::Application *app)
    : AbstractScene(app, "Game"), m_in_game(false), m_player(new Player),
      _map(nullptr), m_event_handler(new SDL_Event) {}

Game::~Game() {}

void Game::init(MiniEngine::Application *app) {
    MiniEngine::Screen *screen = MiniEngine::Application::GetInstance()->get_screen();

    // Load the map
    MiniEngine::Graphics::Tiling::Map *map = new MiniEngine::Graphics::Tiling::Map;
    map->jload(screen, "assets/maps/start.json");
    map->set_position(0, 0);
    map->init(screen);
    m_scene->add_interactible(2, map);
    _map = map;  // Only used to interact with it

    // Load the player
    m_player->init(screen);
    m_player->set_position(2, 2);
    m_scene->add_interactible(1, m_player);
}

// void Game::handle_events(MiniEngine::Screen* sc){
//     while(SDL_PollEvent(m_event_handler) != 0){
//         sc->handle_events(m_event_handler);
//         m_player->handle_event(m_event_handler);
//         // Do updates
//         switch(m_event_handler->type){
//             case SDL_KEYDOWN:
//                 if(m_event_handler->key.keysym.sym == SDLK_ESCAPE) m_in_game
//                 = false; break;
//             default:
//                 break;
//         }
//     }
// }

// void Game::update(MiniEngine::Screen* sc){
//     m_player->update(sc);
//     sc->update_screen();
// }
