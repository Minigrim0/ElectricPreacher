#pragma once

#include <memory>
#include <string>

#include "UI/console.hpp"
#include "UI/notification_center.hpp"
#include "core/core.hpp"
#include "core/scene.hpp"
#include "core/screen.hpp"

namespace MiniEngine {
/**
 * @brief The application represents the 'meta' object that will run the whole game. It is
 * responsible for loading the different parts of the game and dispatching events.
 */
class ME_API Application {
  protected:
    Application();
    Application(std::string project_name);
    Application(std::string project_name, int major_version, int minor_version, int patch_version);

  public:
    virtual ~Application();

    static Application *GetInstance();
    static Application *GetInstance(std::string project_name, int major_version, int minor_version,
                                    int patch_version);

    void run();
    void stop();

    SDL_Renderer *get_renderer();
    Screen *get_screen();
    UI::NotificationCenter *get_notification_center();

    void add_scene(Scene *scene);
    bool set_active_scene(std::string scene_name);

    void enable_console(bool enable = true);

  protected:
    std::string m_project_name;
    int m_major_version;
    int m_minor_version;
    int m_patch_version;

    std::unique_ptr<Screen> m_screen;
    std::unique_ptr<UI::NotificationCenter> m_notification_center;

    std::vector<Scene *> m_scenes;

    bool m_running;
    bool console_enabled;
    bool m_error;

  private:
    void init();
    static Application *s_instance;
    Scene *m_active_scene;
    std::unique_ptr<UI::Console> m_console;
};

/**
 * This function should be implemented by the game itself, it is used as the entrypoint
 * for the engine.
 */
Application *CreateApplication();
} // namespace MiniEngine
