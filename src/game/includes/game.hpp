#ifndef game_hpp
#define game_hpp

#include "../src/player/includes/player.hpp"
#include "../src/map/includes/map_manager.hpp"
#include "../src/screen/includes/notification_center.hpp"

class Game{
    public:
        Game(Screen *screen, NotificationCenter *notif_center, SDL_Event *event_handler);
        ~Game();

        void init(Screen *screen);
        void run();

        void render();
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
