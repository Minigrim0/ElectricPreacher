#pragma once

#include "core.hpp"

namespace MiniEngine {
    class ME_API Application{
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}