#include <iostream>
#include <SDL2/SDL.h>

#include "includes/screen.h"

int main(){
	Screen screen;

	screen.set_width(1440);
	screen.set_height(900);

	if(screen.build_window() != 0) return EXIT_FAILURE;

	std::cout << "1" << std::endl;
	SDL_Surface* image = NULL;
	std::cout << "2" << std::endl;
	image = screen.load_image("assets/images/Doors.png");
	std::cout << "3" << std::endl;
	if(image == NULL) return EXIT_FAILURE;
	std::cout << "4" << std::endl;

	screen.set_current_surface(image);

	while(screen.is_running()){
		screen.handle_events();
		screen.blit_surface(NULL, 10, 10);
		screen.update_screen();
	}

	return EXIT_SUCCESS;
}
