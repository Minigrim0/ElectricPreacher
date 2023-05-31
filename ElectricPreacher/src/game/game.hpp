#pragma once

#include <filesystem>

#include "player/player.hpp"
#include "map/map_manager.hpp"

#include "constants.hpp"
#include "scenes/scene.hpp"

namespace fs = std::filesystem;

/**
 * @brief The Game class is the main class of the game
 * It handles the game loop and the main events during a game
 */
class Game : public Scene {
public:
    Game(MiniEngine::Application* a);
    ~Game();

    // Override
    Game(Game &other) = delete;
    void operator=(const Game &) = delete;

    void init(MiniEngine::Application *app) override;

    void load(fs::path savefile_path);
    void save();

private:
    void draw(MiniEngine::Screen *sc);
    // void handle_events(MiniEngine::Screen *sc);
    // void update(MiniEngine::Screen *sc);

    bool m_in_game;

    Player *m_player;
    MapManager *m_map_manager;
    SDL_Event *m_event_handler;
};
