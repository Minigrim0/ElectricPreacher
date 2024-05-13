#pragma once

#include <string>

#include <SDL.h>

#include "graphics/renderable.hpp"

namespace MiniEngine::Graphics {
/**
 * @brief A Simple sprite loaded from a supported file format
 */
class Sprite : public Renderable {
  public:
    Sprite();
    Sprite(std::string path);
    virtual ~Sprite();

  private:
    SDL_Surface _sprite;
};
} // namespace MiniEngine::Graphics
