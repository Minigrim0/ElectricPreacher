#include "application.hpp"

#include "core/log.hpp"

namespace MiniEngine {
    Application::Application():m_project_name("MiniEngine Application") {}

    Application::Application(std::string project_name)
    :m_project_name(project_name),
    m_major_version(0),
    m_minor_version(1),
    m_patch_version(0)
    {
        ME_CORE_INFO("Application {0} created!", project_name);
    }

    Application::Application(std::string project_name, int major_version, int minor_version, int patch_version)
    :m_project_name(project_name),
    m_major_version(major_version),
    m_minor_version(minor_version),
    m_patch_version(patch_version)
    {
        ME_CORE_INFO(
            "Application {0} ({1}.{2}.{3}) created!",
            project_name,
            major_version,
            minor_version,
            patch_version
            );
    }

    Application::~Application(){}

    void Application::run(){
        ME_CORE_INFO("Starting the application");
        m_running = true;

        m_screen = std::unique_ptr<Screen>(Screen::Create());
        m_screen->set_width(1920);
        m_screen->set_height(1080);
        m_screen->set_caption(
            m_project_name +
            std::to_string(0) + "." +
            std::to_string(1) + "." +
            std::to_string(2));
        m_screen->init();
        m_screen->add_font("assets/fonts/Roboto-Regular.ttf", 16, "Roboto_16");
        m_screen->set_default_font("Roboto_16");

        if (m_screen->build_window() != 0) {
            ME_CORE_ERROR("Failed to build window");
            return;
        }
        ME_CORE_INFO("Started application");

        SDL_Event event;

        while (m_running) {
            // Handle events
            while(SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT) {
                    m_running = false;
                }
            }
            m_screen->update_screen();
        }
    }
}
