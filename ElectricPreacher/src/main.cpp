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
