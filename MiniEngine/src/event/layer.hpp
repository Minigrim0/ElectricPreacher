#include <vector>

#include "event/interactible.hpp"


namespace MiniEngine {
    namespace Event {
        class Layer{
            public:
                Layer() = default;
                virtual ~Layer() = default;

                void attach(Interactible* interactible);

                bool OnEvent(SDL_Event* event);
            private:
                std::vector<Interactible*> m_interactibles;
        };
    }
}
