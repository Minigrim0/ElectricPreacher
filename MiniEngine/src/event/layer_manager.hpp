#pragma once

#include <SDL.h>
#include <vector>

#include "event/layer.hpp"

namespace MiniEngine {
namespace Event {
#define GAME_LAYER 0
#define UI_LAYER 1

class LayerManager {
  public:
    LayerManager();
    virtual ~LayerManager();

    static LayerManager *create();

    void attach(uint8_t layer_index, Layer *layer);
    void attach(uint8_t layer_index, Interactible *interactible);

    bool OnEvent(SDL_Event *event);
    void OnRender(Screen *screen) const;
    void OnUpdate(int time_elapsed);

  private:
    std::vector<Layer *> m_layers;
};
} // namespace Event
} // namespace MiniEngine
