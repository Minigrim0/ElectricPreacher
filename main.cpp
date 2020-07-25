#include <iostream>
#include <thread>
#include <mutex>
#include <map>
#include <SDL2/SDL.h>
#include <filesystem>

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
	Screen screen;
    std::string current_window = "Main";

	std::map<std::string, Window> windows;

	SDL_Event* event_handler = new SDL_Event;
	SDL_StopTextInput();

	screen.set_width(SCREEN_X);
	screen.set_height(SCREEN_Y);
	screen.set_caption(
		"The Electric Preacher (" +
		std::to_string(VERSION) + "." +
		std::to_string(SUBVERSION) + "." +
		std::to_string(SUBSUBVERSION) + ")");
	screen.init();

    screen.add_font("assets/fonts/Roboto-Regular.ttf", 16, "Roboto_16");
    screen.set_default_font("Roboto_16");

	if(screen.build_window() != 0) return EXIT_FAILURE;

    // Starting the notification center thread
    NotificationCenter notification_center(&screen);
    notification_center.set_running(true);
    std::thread notification_thread(&NotificationCenter::run, &notification_center, &screen);

    std::string UI_path = static_cast<std::string>(std::filesystem::current_path()) + "/assets/UI/";
    const std::filesystem::path pathToShow{ UI_path };

    for (const auto& entry : std::filesystem::directory_iterator(pathToShow)) {
        const auto filenameStr = entry.path().filename().string();
        if(entry.is_regular_file()){
            std::cout << "Found window " << filenameStr << std::endl;
            Window tmp_window;
            tmp_window.createfrom(&screen, static_cast<std::string>(pathToShow) + static_cast<std::string>(filenameStr));

            std::cout << "Saving window as " << tmp_window.get_title() << std::endl;
            windows[tmp_window.get_title()] = tmp_window;
        }
    }

	while(screen.is_running()){

		windows[current_window].draw(&screen);

	    while(SDL_PollEvent(event_handler) != 0){
			screen.handle_events(event_handler);
			windows[current_window].update(event_handler, &screen, &current_window);
		}

        screenMutex.lock();
		screen.update_screen();
        screenMutex.unlock();
    }

    notification_center.set_running(false);
    notification_thread.join();

	return EXIT_SUCCESS;
}
