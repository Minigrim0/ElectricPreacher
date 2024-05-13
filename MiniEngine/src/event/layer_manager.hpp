#pragma once

#include <SDL.h>
#include <vector>

#include "event/layer.hpp"

namespace MiniEngine::Event {
#define GAME_LAYER 0
#define UI_LAYER 1

/**
 * @brief Implement a number of layer that can hold interactible elements.
 * If an event occurs, the first layer will be notified, all elements equally,
 * and the event will continue through the next layers only if no element on the current
 * layer stops the propagation of the event.
 */
class LayerManager {
  public:
    LayerManager();
    virtual ~LayerManager();

    static LayerManager *create();

    void attach(uint8_t layer_index, Layer layer);
    void attach(uint8_t layer_index, Interactible *interactible);

    bool OnEvent(SDL_Event *event);
    void OnRender(Screen *screen) const;
    void OnUpdate(int time_elapsed);

  private:
    std::vector<Layer> _layers;
};
} // namespace Event
