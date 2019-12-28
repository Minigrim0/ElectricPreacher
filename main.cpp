#include <iostream>
#include <SDL2/SDL.h>

#include "includes/constants.h"
#include "includes/screen.h"
#include "includes/image_set.h"
#include "includes/map_manager.h"
#include "includes/console.h"

int main(){
	if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Creating screen" << std::endl;
	Screen screen;
	if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Creating Image set" << std::endl;
	ImageSet set;

	SDL_Event* event_handler = new SDL_Event;
	SDL_StopTextInput();

	screen.set_width(SCREEN_X);
	screen.set_height(SCREEN_Y);
	screen.set_caption("Fuzzy waddle");

	screen.init();
	if(screen.build_window() != 0) return EXIT_FAILURE;

	set.set_image(&screen, "assets/images/Doors.png");
	set.set_array();

	if(DEBUG) std::cout << __PRETTY_FUNCTION__ << "> Creating console" << std::endl;
	Console cons(10, 200, 250, 400);
	cons.set_font("assets/fonts/Roboto-Regular.ttf", 70);
	cons.init(&screen);
	cons.update_layout(&screen);

	while(screen.is_running()){

		screen.blit(set.get_texture(), set.get_sub(0, 9),  0, 10);
		screen.blit(set.get_texture(), set.get_sub(0, 10), 0, 42);
		screen.blit(set.get_texture(), set.get_sub(0, 11), 0, 74);

		screen.blit(set.get_texture(), set.get_sub(3, 9),  32, 10);
		screen.blit(set.get_texture(), set.get_sub(3, 10), 32, 42);
		screen.blit(set.get_texture(), set.get_sub(3, 11), 32, 74);

		screen.blit(set.get_texture(), set.get_sub(2, 9),  64, 10);
		screen.blit(set.get_texture(), set.get_sub(2, 10), 64, 42);
		screen.blit(set.get_texture(), set.get_sub(2, 11), 64, 74);

		cons.draw(&screen);


	    while(SDL_PollEvent(event_handler) != 0){
			screen.handle_events(event_handler);
			cons.update(event_handler, &screen);
		}

		screen.update_screen();
	}

	return EXIT_SUCCESS;
}
