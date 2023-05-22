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
 
        /**
         * @brief Sets the layer `layer_index` the given layer.
         * 
         * @param layer_index 
         * @param layer 
         */
        void LayerManager::attach(uint8_t layer_index, Layer* layer) {
            m_layers[layer_index] = layer;
        }

        void LayerManager::attach(uint8_t layer_index, Interactible* interactible) {
            m_layers[layer_index]->attach(interactible);
        }

        bool LayerManager::OnEvent(SDL_Event* event) {
            for (auto layer : m_layers) {
                if (layer->OnEvent(event))
                    return true;
            }
            return false;
        }

        void LayerManager::OnRender(Screen* screen) const {
            // Render layers in inverse order
            for (auto layer = m_layers.rbegin(); layer != m_layers.rend(); layer++) {
                (*layer)->OnRender(screen);
            }
        }

        void LayerManager::OnUpdate(int time_elapsed) {
            for (auto layer : m_layers) {
                layer->OnUpdate(time_elapsed);
            }
        }
    }
}
