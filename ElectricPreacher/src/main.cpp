// #include <iostream>
// #include <mutex>
// #include <map>

// #include <SDL.h>
// #include <SDL_events.h>
// #include <SDL_render.h>

// #include <core/screen.hpp>

// #include <UI/notification_center.hpp>
// #include <UI/console.hpp>
// #include <UI/window.hpp>
// #include <UI/widgets/widgets.hpp>

// #include "constants.hpp"
// #include "game/game.hpp"
// #include "map/map_manager.hpp"
// #include "utils/build_windows.hpp"

// /**
//  * @brief The main function
//  * 
//  * @param argc 
//  * @param argv 
//  * @return int 
//  */
// int main2(int argc, char* argv[]) {
//     CORE::Screen* screen = CORE::Screen::GetInstance(PROJECT_NAME);
//     std::string current_window = "Main";

//     std::map<std::string, UI::Window> windows;

//     SDL_Event* event_handler = new SDL_Event;
//     SDL_StopTextInput();

//     if(screen->build_window() != 0) return EXIT_FAILURE;

//     // build_windows(&windows);
//     std::string action;

//     while(screen->is_running()){
//         action = "";
//         windows[current_window].draw(screen);
//         notification_center->draw(screen);

//         while(SDL_PollEvent(event_handler) != 0){
//             screen->handle_events(event_handler);
//             windows[current_window].update(event_handler, screen, &current_window, &action);
//             if(action == "start_new_game"){
//                 Game::GetInstance()->init();
//                 Game::GetInstance()->run();
//             }

//             notification_center->update(event_handler, screen);
//             /* Example code to create a notification */
//             if(event_handler->type == SDL_KEYUP){
//                 notification_center->create_notification("Keyup !", screen, "Roboto_16", 2500);
//             }
//         }
//         notification_center->update(nullptr, screen);

//         screen->update_screen();
//     }

//     return EXIT_SUCCESS;
// }

#include <MiniEngine.hpp>

#include "constants.hpp"
#include "scenes/main_menu.hpp"


MiniEngine::Application* MiniEngine::CreateApplication() {
    Application* app = MiniEngine::Application::GetInstance(
        PROJECT_NAME,
        VERSION_MAJOR,
        VERSION_MINOR,
        VERSION_PATCH
    );
    app->enable_console();

    MainMenu* main_menu = new MainMenu(app);
    main_menu->init(app);
    main_menu->start(app);

    return app;
}
