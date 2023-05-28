#pragma once

#include <SDL.h>

#include "core/core.hpp"
#include "core/screen.hpp"

namespace MiniEngine{
    namespace Event {
        class ME_API Interactible {
            public:
                Interactible() = default;
                virtual ~Interactible() = default;

                virtual bool OnEvent(SDL_Event* event) = 0;
                virtual void OnRender(Screen* sc) = 0;
                virtual void OnUpdate(int time_elapsed) = 0;
        };
    }
}
