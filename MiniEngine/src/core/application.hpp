#pragma once

#include <memory>
#include <string>

#include "core/core.hpp"
#include "core/screen.hpp"
#include "core/scene.hpp"
#include "event/layer_manager.hpp"
#include "UI/notification_center.hpp"

namespace MiniEngine {
    class ME_API Application{
    protected:
        Application();
        Application(std::string project_name);
        Application(std::string project_name, int major_version, int minor_version, int patch_version);

    public:
        virtual ~Application();

        static Application* GetInstance();
        static Application* GetInstance(std::string project_name, int major_version, int minor_version, int patch_version);

        void run();

        SDL_Renderer* get_renderer();
        Screen* get_screen();
        UI::NotificationCenter* get_notification_center();

        bool add_scene(Scene* scene);
        bool set_active_scene(std::string scene_name);
        void set_active_scene(Scene* scene);

    protected:
        std::string m_project_name;
        int m_major_version;
        int m_minor_version;
        int m_patch_version;

        std::unique_ptr<Screen> m_screen;
        std::unique_ptr<UI::NotificationCenter> m_notification_center;

        std::vector<Scene*> m_scenes;

        bool m_running;
        bool console_enabled;
        bool error;

    private:
        void init();
        static Application* s_instance;
        Scene* m_active_scene;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}
