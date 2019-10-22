#include <iostream>
#include <SDL2/SDL.h>

#include "../includes/screen.h"
#include "../includes/constants.h"
#include "includes/editor_ui.h"

int main(){
    Screen screen;
    EditorUI ui;

    screen.set_width(EDITOR_SCREEN_X);
    screen.set_height(EDITOR_SCREEN_Y);
    screen.set_font("../assets/fonts/courrier_new.ttf");
    screen.set_caption("Fuzzy-Waddle Editor");
    screen.set_background_color(215, 215, 215);

    if(screen.build_window() != 0) return EXIT_FAILURE;

    //ui.set_grid_pos(20, 20);
    if(ui.set_font("../assets/fonts/Roboto-Regular.ttf") != 0) return EXIT_FAILURE;
    ui.init_ui_elements(&screen);

    while(screen.is_running()){
        ui.draw(&screen);
        screen.handle_events();
        screen.update_screen();
    }

    return EXIT_SUCCESS;
}
