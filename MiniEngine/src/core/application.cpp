#include "application.hpp"

#include "core/log.hpp"


namespace MiniEngine {
    Application* Application::s_instance = nullptr;

    Application::Application() : Application("MiniEngine") {}

    Application::Application(std::string project_name) : Application(project_name, 0, 1, 0) {}

    Application::Application(std::string project_name, int major_version, int minor_version, int patch_version)
    :m_project_name(project_name),
    m_major_version(major_version),
    m_minor_version(minor_version),
    m_patch_version(patch_version),
    m_screen(nullptr),
    m_notification_center(nullptr),
    m_running(false),
    console_enabled(false),
    error(false),
    m_active_scene(nullptr),
    m_console(nullptr)
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

    Application* Application::GetInstance(){
        if (s_instance == nullptr) {
            ME_CORE_WARN("Application instance is null, creating new default instance");
            s_instance = new Application();
        }
        return s_instance;
    }

    Application* Application::GetInstance(std::string project_name, int major_version, int minor_version, int patch_version){
        if (s_instance == nullptr) {
            s_instance = new Application(project_name, major_version, minor_version, patch_version);
        }
        return s_instance;
    }

    /**
     * @brief Initializes the application. Starts the screen, notification center, and layer manager.
     */
    void Application::init(){
        m_screen = std::unique_ptr<Screen>(Screen::Create());
        m_notification_center = std::unique_ptr<UI::NotificationCenter>(UI::NotificationCenter::Create(m_screen.get()));

        m_screen->SetWidth(1920);
        m_screen->SetHeight(1080);
        m_screen->SetCaption(m_project_name + " - " + std::to_string(m_major_version) + "." + std::to_string(m_minor_version) + "." + std::to_string(m_patch_version));
        m_screen->Init();
        m_screen->AddFont("assets/fonts/Roboto-Regular.ttf", 16, "Roboto_16");
        m_screen->SetDefaultFont("Roboto_16");

        if (m_screen->BuildWindow() != 0) {
            ME_CORE_ERROR("Failed to build window");
            error = true;
        }
    }

    void Application::run(){
        ME_CORE_INFO("Starting the application");
        if (error) {
            ME_CORE_ERROR("Application failed to initialize, check logs");
            return;
        }

        m_running = true;
        SDL_Event event;

        while (m_running) {
            // Handle events
            while(SDL_PollEvent(&event)){
                if (event.type == SDL_QUIT) {
                    m_running = false;
                }
                // Handle events on the screen first, then the console, then the active scene
                if(!m_screen->OnEvent(&event))
                    if(console_enabled)
                        if(!m_console->OnEvent(&event))
                            m_active_scene->OnEvent(&event);
                    else
                        m_active_scene->OnEvent(&event);
            }

            // Render
            m_active_scene->OnUpdate(m_screen->get_time_elapsed());
            m_active_scene->OnRender(m_screen.get());
            if (console_enabled) {
                m_console->OnUpdate(m_screen->get_time_elapsed());
                m_console->OnRender(m_screen.get());
            }
            m_screen->Update();
        }
    }

    void Application::stop(){
        m_running = false;
    }

    SDL_Renderer* Application::get_renderer(){
        return m_screen->get_renderer();
    }

    Screen* Application::get_screen(){
        return m_screen.get();
    }

    UI::NotificationCenter* Application::get_notification_center(){
        return m_notification_center.get();
    }

    bool Application::add_scene(Scene* scene){
        m_scenes.push_back(scene);
        return true;
    }

    bool Application::set_active_scene(std::string scene_name){
        for(auto scene : m_scenes) {
            if (scene->get_name() == scene_name) {
                scene->set_running(true);
                m_active_scene = scene;
                return true;
            }
        }
        return false;
    }

    void Application::set_active_scene(Scene* scene){
        scene->set_running(true);
        m_active_scene = scene;
    }

    void Application::enable_console(bool enabled){
        console_enabled = enabled;
        if (console_enabled) {
            m_console = std::unique_ptr<UI::Console>(new UI::Console(15, 100, 250, 650));
            m_console->set_font(m_screen->get_font("Roboto_16"));
            m_console->init(m_screen.get());
        } else {
            m_console.reset();
        }
    }
}
