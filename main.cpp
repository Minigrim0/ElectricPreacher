#include <iostream>
#include <thread>
#include <mutex>
#include <SDL2/SDL.h>

#include "includes/constants.h"
#include "includes/notification_center.h"
#include "includes/screen.h"
#include "includes/image_set.h"
#include "includes/map_manager.h"
#include "includes/widgets.h"
#include "includes/console.h"
#include "includes/window.h"

std::mutex screenMutex;

int main(){
	std::cout << "Creating screen object" << std::endl;
	Screen screen;
	std::cout << "Creating window object" << std::endl;
	Window window;

	SDL_Event* event_handler = new SDL_Event;
	SDL_StopTextInput();

	std::cout << "Creating screen" << std::endl;
	screen.set_width(SCREEN_X);
	screen.set_height(SCREEN_Y);
	screen.set_caption(
		"The Electric Preacher (" +
		std::to_string(VERSION) + "." +
		std::to_string(SUBVERSION) + "." +
		std::to_string(SUBSUBVERSION) + ")");

	std::cout << "Initializing screen" << std::endl;
	screen.init();
	if(screen.build_window() != 0) return EXIT_FAILURE;

    // Starting the notification center thread
    NotificationCenter notification_center(&screen);
    notification_center.set_running(true);
    std::thread notification_thread(&NotificationCenter::run, &notification_center, &screen);

	std::cout << "Creating main window" << std::endl;
	window.createfrom(&screen, "assets/UI/MainWindow.json");

	while(screen.is_running()){

		window.draw(&screen);

	    while(SDL_PollEvent(event_handler) != 0){
			screen.handle_events(event_handler);
			window.update(event_handler, &screen);
		}

        screenMutex.lock();
		screen.update_screen();
        screenMutex.unlock();
	}

    notification_center.set_running(false);
    notification_thread.join();

	return EXIT_SUCCESS;
}
