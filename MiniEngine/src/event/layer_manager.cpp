#include "event/layer_manager.hpp"

#include "core/log.hpp"

namespace MiniEngine::Event {
LayerManager::LayerManager() : _layers(std::vector<Layer>()) {
    ME_CORE_INFO("Creating layer manager");
    for (uint8_t index = 0; index < 10; index++) {
        _layers.push_back(Layer(index));
    }
}

LayerManager::~LayerManager() {
    ME_CORE_INFO("Destroying layer manager");
}

LayerManager *LayerManager::create() { return new LayerManager(); }

/**
 * @brief Sets the layer `layer_index` the given layer.
 *
 * @param layer_index
 * @param layer
 */
void LayerManager::attach(uint8_t layer_index, Layer layer) { _layers[layer_index] = layer; }

void LayerManager::attach(uint8_t layer_index, Interactible* interactible) {
    _layers[layer_index].attach(interactible);
}

bool LayerManager::OnEvent(SDL_Event *event) {
    for (auto layer : _layers) {
        if (layer.OnEvent(event)) {
            ME_CORE_TRACE("Event handled by layer {0}", layer.getId());
            return true;
        }
    }
    return false;
}

void LayerManager::OnRender(Screen *screen) const {
    // Render layers in inverse order
    for (auto layer : _layers) {
        layer.OnRender(screen);
    }
}

void LayerManager::OnUpdate(int time_elapsed) {
    for (auto layer : _layers) {
        layer.OnUpdate(time_elapsed);
    }
}
} // namespace Event
