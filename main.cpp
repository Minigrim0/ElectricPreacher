#include <iostream>
#include <SDL2/SDL.h>

#include "includes/constants.h"
#include "includes/screen.h"
#include "includes/image_set.h"
#include "includes/map_manager.h"

int main(){
	Screen screen;
	std::cout << "Screen address : " << &screen << std::endl;
	ImageSet set;

	screen.set_width(SCREEN_X);
	screen.set_height(SCREEN_Y);
	screen.set_caption("Fuzzy waddle");

	if(screen.build_window() != 0) return EXIT_FAILURE;

	SDL_Surface* image = NULL;
	image = screen.load_image("assets/images/Doors.png");
	if(image == NULL) return EXIT_FAILURE;

	set.set_image(image);
	set.set_array();

	while(screen.is_running()){
		screen.handle_events();
		screen.set_current_surface(image);
		screen.blit_surface(set.get_sub(0, 9),  0, 10);
		screen.blit_surface(set.get_sub(0, 10), 0, 42);
		screen.blit_surface(set.get_sub(0, 11), 0, 74);

		screen.blit_surface(set.get_sub(3, 9),  32, 10);
		screen.blit_surface(set.get_sub(3, 10), 32, 42);
		screen.blit_surface(set.get_sub(3, 11), 32, 74);

		screen.blit_surface(set.get_sub(2, 9),  64, 10);
		screen.blit_surface(set.get_sub(2, 10), 64, 42);
		screen.blit_surface(set.get_sub(2, 11), 64, 74);
		screen.update_screen();
	}

	SDL_FreeSurface(image);

	return EXIT_SUCCESS;
}
