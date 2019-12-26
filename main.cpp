#include <iostream>
#include <SDL2/SDL.h>

#include "includes/constants.h"
#include "includes/screen.h"
#include "includes/image_set.h"
#include "includes/map_manager.h"

int main(){
	Screen screen;
	ImageSet set;

	screen.set_width(SCREEN_X);
	screen.set_height(SCREEN_Y);
	screen.set_caption("Fuzzy waddle");

	screen.init();
	if(screen.build_window() != 0) return EXIT_FAILURE;

	set.set_image(&screen, "assets/images/Doors.png");
	set.set_array();

	while(screen.is_running()){
		screen.handle_events();
		screen.blit(set.get_texture(), set.get_sub(0, 9),  0, 10);
		screen.blit(set.get_texture(), set.get_sub(0, 10), 0, 42);
		screen.blit(set.get_texture(), set.get_sub(0, 11), 0, 74);

		screen.blit(set.get_texture(), set.get_sub(3, 9),  32, 10);
		screen.blit(set.get_texture(), set.get_sub(3, 10), 32, 42);
		screen.blit(set.get_texture(), set.get_sub(3, 11), 32, 74);

		screen.blit(set.get_texture(), set.get_sub(2, 9),  64, 10);
		screen.blit(set.get_texture(), set.get_sub(2, 10), 64, 42);
		screen.blit(set.get_texture(), set.get_sub(2, 11), 64, 74);
		screen.update_screen();
	}

	return EXIT_SUCCESS;
}
