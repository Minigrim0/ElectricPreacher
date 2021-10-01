#ifndef game_hpp
#define game_hpp

#include <filesystem>

#include "../../player/includes/player.hpp"
#include "../../map/includes/map_manager.hpp"
#include "../../screen/includes/notification_center.hpp"

namespace fs = std::filesystem;


class Game{
    public:
        Game(Screen *screen, NotificationCenter *notif_center, SDL_Event *event_handler);
        ~Game();

        void init(Screen *screen);
        void run();

        void draw();
        void handle_events();
        void update();

        void load(fs::path savefile_path);
        void save();

    private:
        bool m_in_game;

        Player *m_player;
        MapManager *m_map_manager;
        Screen *m_screen;
        NotificationCenter *m_notification_center;
        SDL_Event *m_event_handler;
};

#endif
