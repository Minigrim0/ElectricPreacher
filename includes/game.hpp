#ifndef game_hpp
    #define game_hpp

#include "player.hpp"
#include "map_manager.hpp"
#include "notification_center.hpp"

/**
    class : Game
    purpose : Manages everything game related, the player, the different actors, the environment, ...
*/

class Game{
    public:
        Game(Screen* screen, NotificationCenter* notif_center, SDL_Event* event_handler);
        ~Game();

        void init(Screen* screen);
        void run();

        void render();
        void save();

    private:
        bool m_in_game;

        Player *m_player;
        MapManager *m_map_manager;
        Screen* m_screen;
        NotificationCenter* m_notification_center;
	    SDL_Event* m_event_handler;
};

#endif
