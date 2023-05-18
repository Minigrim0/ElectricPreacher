#include <vector>
#include <SDL.h>

#include "event/layer.hpp"

namespace MiniEngine {
    namespace Event {
        class LayerManager {
            public:
                LayerManager() = default;
                virtual ~LayerManager() = default;

                void attach(Layer* layer);
                bool OnEvent(SDL_Event* event);

            private:
                std::vector<Layer*> m_layers;
        };
    }
}
