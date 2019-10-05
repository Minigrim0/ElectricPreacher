#include <iostream>
#include "includes/screen.h"

Screen screen;

int main(){
	screen.set_width(800);
	screen.set_height(480);

	if(screen.build_window() != 0) return EXIT_FAILURE;

	while(screen.is_running()){
		screen.handle_events();
		screen.update_screen();
	}

	return EXIT_SUCCESS;
}
