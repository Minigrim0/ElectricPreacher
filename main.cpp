#include <iostream>
#include <mutex>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

#include "includes/build_windows.hpp"
#include "includes/constants.hpp"
#include "includes/notification_center.hpp"
#include "includes/screen.hpp"
#include "includes/image_set.hpp"
#include "includes/map/map_manager.hpp"
#include "includes/widgets.hpp"
#include "includes/console.hpp"
#include "includes/window.hpp"
#include "includes/game.hpp"

int main(int argc, char *argv[]){
	Screen screen;
    std::string current_window = "Main";

	std::map<std::string, Window> windows;

	SDL_Event* event_handler = new SDL_Event;
	SDL_StopTextInput();

	screen.set_width(SCREEN_X);
	screen.set_height(SCREEN_Y);
	screen.set_caption(
		"The Electric Preacher (" +
		std::to_string(VERSION_MAJOR) + "." +
		std::to_string(VERSION_MINOR) + ")");
	screen.init();

    screen.add_font("assets/fonts/Roboto-Regular.ttf", 16, "Roboto_16");
    screen.set_default_font("Roboto_16");

	if(screen.build_window() != 0) return EXIT_FAILURE;

    NotificationCenter notification_center(&screen, "Roboto_16");
    build_windows(&screen, &windows);

    while(screen.is_running()){

        windows[current_window].draw(&screen);
        notification_center.draw(&screen);

        while(SDL_PollEvent(event_handler) != 0){
            screen.handle_events(event_handler);
            
            std::string action = "";
            windows[current_window].update(event_handler, &screen, &current_window, &action);
            if(action == "start_new_game"){
                Game* game = new Game(&screen, &notification_center, event_handler);
                game->init(&screen);
                game->run();
            }

            notification_center.update(event_handler, &screen);
            if(event_handler->type == SDL_KEYUP){
                notification_center.create_notification("Keyup !", &screen, "Roboto_16", 2500);
            }
        }
        notification_center.update(nullptr, &screen);

        screen.update_screen();
    }

    return EXIT_SUCCESS;
}
