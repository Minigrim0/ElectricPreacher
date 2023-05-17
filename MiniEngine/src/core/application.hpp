#pragma once

#include <memory>
#include <string>

#include "core/screen.hpp"
#include "core/core.hpp"

#include "UI/notification_center.hpp"

namespace MiniEngine {
    class ME_API Application{
    public:
        Application();
        Application(std::string project_name);
        virtual ~Application();

        void Run();
    protected:
        std::string m_project_name;
        std::unique_ptr<Screen> m_screen;
        std::unique_ptr<UI::NotificationCenter> m_notification_center;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}