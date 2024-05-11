#include "application.hpp"

#include "core/log.hpp"

namespace MiniEngine {
Application *Application::s_instance = nullptr;

Application::Application() : Application("MiniEngine") {}

Application::Application(std::string project_name) : Application(project_name, 0, 0, 0) {}

Application::Application(std::string project_name, int major_version, int minor_version,
                         int patch_version)
    : m_project_name(project_name), m_major_version(major_version), m_minor_version(minor_version),
      m_patch_version(patch_version), m_screen(nullptr), m_notification_center(nullptr),
      m_running(false), console_enabled(false), m_error(false), m_active_scene(nullptr),
      m_console(nullptr) {
    ME_CORE_INFO("Initializing {0} ({1}.{2}.{3})", project_name, major_version, minor_version,
                 patch_version);
    this->init();
    if (m_error) {
        ME_CORE_ERROR("Application failed to initialize, exiting");
        exit(-1);
    }
}

/**
 * @brief Destroy the Application:: Application object
 */
Application::~Application() {
    for (auto scene : m_scenes) {
        free(scene);
    }
}

/**
 * @brief Returns the instance of the application. If the instance is null, a
 * new instance is created.
 *
 * \remark this class implements the singleton pattern, ensure the constructor is
 * private/protected.
 *
 * @return Application* The instance of the application
 */
Application *Application::GetInstance() {
    if (s_instance == nullptr) {
        ME_CORE_INFO("Application instance is null, creating new default instance");
        s_instance = new Application();
    }
    return s_instance;
}

/**
 * @brief Returns the instance of the application. If the instance is null, a
 * new instance is created with the given parameters.
 *
 * \remark this class implements the singleton pattern, ensure the constructor is
 * private/protected.
 *
 * @param project_name The name of the project
 * @param major_version The major version of the project
 * @param minor_version The minor version of the project
 * @param patch_version The patch version of the project
 *
 * @return The instance of the application
 */
Application *Application::GetInstance(std::string project_name, int major_version,
                                      int minor_version, int patch_version) {
    if (s_instance == nullptr) {
        ME_CORE_INFO("Application instance is null, creating new instance with "
                     "parameters '{0}' '{1}.{2}.{3}'",
                     project_name, major_version, minor_version, patch_version);
        s_instance = new Application(project_name, major_version, minor_version, patch_version);
    }
    return s_instance;
}

/**
 * @brief Initializes the application. Starts the screen, notification center,
 * and layer manager.
 *
 * This private function is called by the Application constructor, which will
 * then check for errors and stop execution if any is found
 */
void Application::init() {
    m_screen = std::unique_ptr<Screen>(Screen::create());
    m_notification_center =
        std::unique_ptr<UI::NotificationCenter>(UI::NotificationCenter::create(m_screen.get()));

    m_screen->setWidth(1920);
    m_screen->setHeight(1080);
    m_screen->setCaption(m_project_name + " - " + std::to_string(m_major_version) + "." +
                         std::to_string(m_minor_version) + "." + std::to_string(m_patch_version));
    m_screen->init();
    m_screen->addFont("assets/fonts/Roboto-Regular.ttf", 16, "Roboto_16");
    m_screen->setDefaultFont("Roboto_16");

    if (m_screen->buildWindow() != 0) {
        ME_CORE_ERROR("Failed to build window");
        m_error = true;
    }
}

/**
 * @brief Starts the application
 * If an error occured during the initialization, the function will
 * Log an error message and then return.
 *
 */
void Application::run() {
    ME_CORE_INFO("Starting the application");
    if (m_error) {
        ME_CORE_ERROR("Application failed to initialize, check logs");
        return;
    }

    m_running = true;
    SDL_Event event;

    while (m_running) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_running = false;
            }
            // Handle events on the screen first, then the console, then the
            // active scene
            if (!m_screen->OnEvent(&event)) {
                if (console_enabled) {
                    if (!m_console->OnEvent(&event))
                        m_active_scene->OnEvent(&event);
                } else {
                    m_active_scene->OnEvent(&event);
                }
            }
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

/**
 * @brief Stops the application execution gracefully.
 */
void Application::stop() { m_running = false; }

/**
 * @brief Returns the SDL_Renderer of the application
 *
 * @return SDL_Renderer*
 */
SDL_Renderer *Application::get_renderer() { return m_screen->get_renderer(); }

/**
 * @brief Returns the Screen object of the application
 *
 * @return Screen*
 */
Screen *Application::get_screen() { return m_screen.get(); }

/**
 * @brief Returns a pointer to the notification center
 *
 * @return UI::NotificationCenter*
 */
UI::NotificationCenter *Application::get_notification_center() {
    return m_notification_center.get();
}

/**
 * @brief Adds the given scene to the application's list of scenes.
 * \remark The calling function looses ownership of the scene, the application
 * will handle the freeing of this memory
 *
 * @param scene The pointer to the scene to add
 */
void Application::add_scene(Scene *scene) { m_scenes.push_back(scene); }

/**
 * @brief Sets the scene with the given name as the current active scene.
 *
 * @param scene_name The name of the scene to set as current
 * @return true The scene was found and set as the current one.
 * @return false The scene was not found in the list of scenes.
 */
bool Application::set_active_scene(std::string scene_name) {
    for (auto scene : m_scenes) {
        if (scene->get_name() == scene_name) {
            scene->set_running(true);
            m_active_scene = scene;
            return true;
        }
    }
    return false;
}

/**
 * @brief Enables or disables the console
 * \todo Make to console useful
 *
 * @param enabled True to enable the console, false to disable it
*/
void Application::enable_console(bool enabled) {
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
