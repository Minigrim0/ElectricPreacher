#pragma once

#include <vector>

#include <SDL_events.h>
#include "event/interactible.hpp"


namespace MiniEngine {
    namespace Event {
        /**
         * @brief A layer is a collection of interactibles that can be attached to a layer manager.
         * The layer will propagate events to all of its interactibles.
         * 
         * It handles the deletion of its interactibles.
         */
        class Layer{
            public:
                Layer(uint8_t id);
                virtual ~Layer();

                void attach(Interactible* interactible);
                bool OnEvent(SDL_Event* event);
                void OnRender(Screen* screen);
                void OnUpdate(int time_elapsed);

            private:
                std::vector<Interactible*> m_interactibles;
                uint8_t m_id;
        };
    }
}
