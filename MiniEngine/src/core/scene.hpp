#pragma once

#include <SDL.h>
#include <string>

#include "core/core.hpp"
#include "core/screen.hpp"

#include "event/interactible.hpp"
#include "event/layer_manager.hpp"

namespace MiniEngine {
/**
 * @brief A scene represents a scene in the game. It contains multiple layers, each with their list
 * of interactibles.
 */
class ME_API Scene : public Event::Interactible {
  public:
    Scene();
    Scene(std::string name);
    virtual ~Scene();

    // Getters
    bool is_current() const;
    std::string get_name() const;

    // Setters
    void set_running(bool);

    // Others
    void add_layer(uint8_t index, Event::Layer *layer);
    void add_interactible(uint8_t layer_index, Event::Interactible *interactible);

    void OnUpdate(int time_elapsed);
    bool OnEvent(SDL_Event *event);
    void OnRender(Screen *sc);

  private:
    //! Should be shown and updated ?
    bool m_current;
    //! Name to identify the scene
    std::string m_name;

    //! Layers of the scene
    Event::LayerManager *m_layer_manager;
};
} // namespace MiniEngine
