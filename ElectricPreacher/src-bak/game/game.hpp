#pragma once

#include <filesystem>

#include <UI/notification_center.hpp>

#include "player/player.hpp"
#include "map/map_manager.hpp"

#include "constants.hpp"

namespace fs = std::filesystem;

/**
 * @brief The Game class is the main class of the game
 * It handles the game loop and the main events during a game
 */
class Game {
protected:
    Game();

public:
    ~Game();

    // Override
    Game(Game &other) = delete;
    void operator=(const Game &) = delete;

    // Singleton pattern
    static Game *GetInstance();

    void init();
    void run();

    void load(fs::path savefile_path);
    void save();

private:
    void draw(CORE::Screen *sc, UI::NotificationCenter *nc);
    void handle_events(CORE::Screen *sc, UI::NotificationCenter *nc);
    void update(CORE::Screen *sc, UI::NotificationCenter *nc);

    bool m_in_game;

    Player *m_player;
    MapManager *m_map_manager;
    SDL_Event *m_event_handler;

    static Game *game_;
};
