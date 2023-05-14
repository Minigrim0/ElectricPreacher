#include <iostream>
#include <mutex>
#include <map>

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_render.h>

#include "constants.hpp"

#include "screen/notification_center.hpp"
#include "screen/screen.hpp"

#include "map/map_manager.hpp"

#include "UI/widgets.hpp"
#include "UI/console.hpp"
#include "UI/window.hpp"

#include "utils/build_windows.hpp"
#include "game/game.hpp"

/**
 * @brief The main function
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[]){
    Screen* screen = Screen::GetInstance(PROJECT_NAME);
    std::string current_window = "Main";

    std::map<std::string, Window> windows;

    SDL_Event* event_handler = new SDL_Event;
    SDL_StopTextInput();

    screen->set_width(SCREEN_X);
    screen->set_height(SCREEN_Y);
    screen->set_caption(
        "The Electric Preacher (" +
        std::to_string(VERSION_MAJOR) + "." +
        std::to_string(VERSION_MINOR) + "." +
        std::to_string(VERSION_PATCH) + ")");
    screen->init();

    screen->add_font("assets/fonts/Roboto-Regular.ttf", 16, "Roboto_16");
    screen->set_default_font("Roboto_16");

    if(screen->build_window() != 0) return EXIT_FAILURE;

    NotificationCenter* notification_center = NotificationCenter::GetInstance();
    notification_center->set_default_font("Roboto_16");
    build_windows(screen, &windows);
    std::string action;

    while(screen->is_running()){
        action = "";
        windows[current_window].draw(screen);
        notification_center->draw(screen);

        while(SDL_PollEvent(event_handler) != 0){
            screen->handle_events(event_handler);
            windows[current_window].update(event_handler, screen, &current_window, &action);
            if(action == "start_new_game"){
                Game::GetInstance()->init();
                Game::GetInstance()->run();
            }

            notification_center->update(event_handler, screen);
            /* Example code to create a notification */
            if(event_handler->type == SDL_KEYUP){
                notification_center->create_notification("Keyup !", screen, "Roboto_16", 2500);
            }
        }
        notification_center->update(nullptr, screen);

        screen->update_screen();
    }

    return EXIT_SUCCESS;
}
