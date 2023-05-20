#include "event/layer_manager.hpp"

#include "core/log.hpp"

namespace MiniEngine {
    namespace Event {
        LayerManager::LayerManager()
        :m_layers(std::vector<Layer*>()) {
            ME_CORE_INFO("Creating layer manager");
            for (uint8_t index = 0; index < 10; index++) {
                m_layers.push_back(new Layer(index));
            }
        }

        LayerManager::~LayerManager() {
            ME_CORE_INFO("Destroying layer manager");
            for (auto layer : m_layers) {
                delete layer;
            }
        }

        LayerManager* LayerManager::Create() {
            return new LayerManager();
        }
 
        void LayerManager::attach(Layer* layer) {
            ME_CORE_INFO("Attaching layer to layer manager");
            m_layers.push_back(layer);
        }

        bool LayerManager::OnEvent(SDL_Event* event) {
            ME_CORE_TRACE("Layer manager handling event {0}", event->type);
            for (auto layer : m_layers) {
                if (layer->OnEvent(event))
                    return true;
            }
            return false;
        }

        void LayerManager::render() {
            ME_CORE_TRACE("Layer manager rendering");
            // Render layers in inverse order
            for (auto layer = m_layers.rbegin(); layer != m_layers.rend(); layer++) {
                (*layer)->render();
            }
        }
    }
}
