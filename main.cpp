#include <iostream>
#include <SDL2/SDL.h>

#include "includes/constants.h"
#include "includes/screen.h"
#include "includes/image_set.h"
#include "includes/map_manager.h"
#include "includes/widgets.h"
#include "includes/console.h"
#include "includes/window.h"

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

	std::cout << "Loading window's fonts" << std::endl;
	window.set_font("assets/fonts/Roboto-Regular.ttf");

	std::cout << "Creating main window" << std::endl;
	window.createfrom(&screen, "assets/UI/setup.json");

	while(screen.is_running()){

		window.draw(&screen);

	    while(SDL_PollEvent(event_handler) != 0){
			screen.handle_events(event_handler);
			window.update(event_handler, &screen);
		}

		screen.update_screen();
	}

	return EXIT_SUCCESS;
}
