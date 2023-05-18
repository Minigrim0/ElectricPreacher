#pragma once

#include <SDL.h>

namespace MiniEngine{
    namespace Event {
        class Interactible {
            public:
                Interactible() = default;
                virtual ~Interactible() = default;

                virtual bool OnEvent(SDL_Event* event) = 0;
        };
    }
}
