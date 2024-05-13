#pragma once

#include <SDL.h>

#include "core/core.hpp"
#include "core/screen.hpp"

namespace MiniEngine::Event {
/**
 * @brief Any interactible must implement the `OnEvent` method,
 * Reacting to event in the game loop
 */
class ME_API Interactible {
  public:
    Interactible() = default;
    virtual ~Interactible() = default;

    /**
     * @brief Called upon event arrival in the game.
     *
     * @param event The event that occured
     * @return true The event has been handled and should stop its propagation
     * @return false The event may or may not have been handled but is allowed to continue its
     * propagation
     */
    virtual bool OnEvent(SDL_Event *event) = 0;
};
} // namespace MiniEngine::Event
