#include "application.hpp"

#include "core/log.hpp"

namespace MiniEngine {
    Application::Application():m_project_name("MiniEngine Application") {}

    Application::Application(std::string project_name)
    :m_project_name(project_name),
    m_major_version(0),
    m_minor_version(1),
    m_patch_version(0),
    m_screen(nullptr),
    m_notification_center(nullptr),
    m_layer_manager(nullptr),
    m_running(false)
    {
        ME_CORE_INFO("Initializing {0}", project_name);
        this->init();
    }

    Application::Application(std::string project_name, int major_version, int minor_version, int patch_version)
    :m_project_name(project_name),
    m_major_version(major_version),
    m_minor_version(minor_version),
    m_patch_version(patch_version),
    m_screen(nullptr),
    m_notification_center(nullptr),
    m_layer_manager(nullptr),
    m_running(false)
    {
        ME_CORE_INFO(
            "Initializing {0} ({1}.{2}.{3})",
            project_name,
            major_version,
            minor_version,
            patch_version
        );
        this->init();
    }

    Application::~Application(){}

    void Application::init(){
        ME_CORE_INFO("Initializing application");
        m_screen = std::unique_ptr<Screen>(Screen::Create());
        m_notification_center = std::unique_ptr<UI::NotificationCenter>(UI::NotificationCenter::Create(m_screen.get()));
        m_layer_manager = std::unique_ptr<Event::LayerManager>(Event::LayerManager::Create());
    }

    void Application::run(){
        ME_CORE_INFO("Starting the application");
        m_running = true;

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
                m_layer_manager->OnEvent(&event);
            }
            m_screen->update_screen();
        }

        //! No need to delete the screen, it is a unique_ptr
    }
}
