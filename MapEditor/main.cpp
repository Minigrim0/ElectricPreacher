#include <iostream>
#include <SDL2/SDL.h>

#include "../includes/screen.h"
#include "includes/constants.h"
#include "includes/editor_ui.h"

int main(){
    Screen screen;
    screen.set_width(SCREEN_WIDTH);
    screen.set_height(SCREEN_HEIGHT);
    screen.set_font("../assets/fonts/courrier_new.ttf");

    EditorUI ui;

	if(screen.build_window() != 0) return EXIT_FAILURE;
    while(screen.is_running()){
        ui.draw(&screen);
        screen.handle_events();
        screen.update_screen();
    }

    SDL_Delay(2000);

    return EXIT_SUCCESS;
}
