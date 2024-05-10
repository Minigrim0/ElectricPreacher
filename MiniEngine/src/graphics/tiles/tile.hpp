#pragma once

#include <SDL.h>

#include "core/screen.hpp"
#include "event/interactible.hpp"
#include "graphics/tiles/tileset.hpp"

/**
 * @author Minigrim0
 * @brief A map element is an element of the map, which can be interacted with
 * This class is abstract, and should be inherited by other classes
 */
namespace MiniEngine {
namespace Graphics {
namespace Tiling {

class Tile {
  public:
    // Constructors
    Tile(bool solid, const std::string *type);
    Tile(bool solid, const std::string *type, SDL_Point position);
    virtual ~Tile() = default;

    // Getters
    std::string get_type() const;
    bool is_solid() const;

    // Setters
    void set_solidity(bool solid);
    void set_position(SDL_Point position);
    void set_texture(MiniEngine::Graphics::Tiling::TileSet *tileset, int id);

    int draw(SDL_Surface *dest);

  protected:
    bool m_is_solid;
    MiniEngine::Graphics::Tiling::TileSet *m_tileset;
    int m_texture_id;

    SDL_Point m_texture_size;
    SDL_Rect m_position;
    std::string m_type;
};
} // namespace Tiling
} // namespace Graphics
} // namespace MiniEngine
