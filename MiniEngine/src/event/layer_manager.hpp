#include <vector>
#include <SDL.h>

#include "event/layer.hpp"

namespace MiniEngine {
    namespace Event {
        #define GAME_LAYER 0
        #define UI_LAYER 1

        class LayerManager {
            public:
                LayerManager();
                virtual ~LayerManager();

                static LayerManager* Create();

                void attach(Layer* layer);
                bool OnEvent(SDL_Event* event);
                void render();

            private:
                std::vector<Layer*> m_layers;
        };
    }
}
