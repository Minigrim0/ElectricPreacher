#pragma once

#include <memory>
#include <string>

#include "core/core.hpp"
#include "core/screen.hpp"
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

        void run();

        SDL_Renderer* get_renderer();
        Screen* get_screen();
        UI::NotificationCenter* get_notification_center();
        Event::LayerManager* get_layer_manager();

    protected:
        std::string m_project_name;
        int m_major_version;
        int m_minor_version;
        int m_patch_version;

        std::unique_ptr<Screen> m_screen;
        std::unique_ptr<UI::NotificationCenter> m_notification_center;
        std::unique_ptr<Event::LayerManager> m_layer_manager;

        bool m_running = false;

    private:
        void init();
        static Application* s_instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}
