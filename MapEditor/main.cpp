#include <iostream>
#include <SDL2/SDL.h>

#include "../includes/screen.h"
#include "includes/constants.h"

int main(){
    Screen screen;
    screen.set_width(SCREEN_WIDTH);
    screen.set_height(SCREEN_HEIGHT);
    screen.set_font("../assets/fonts/courrier_new.ttf");

	if(screen.build_window() != 0) return EXIT_FAILURE;
    screen.update_screen();

    SDL_Delay(2000);

    return EXIT_SUCCESS;
}
