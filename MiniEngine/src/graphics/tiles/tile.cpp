#include "graphics/tiles/tile.hpp"
#include "map/elements/elements.hpp"

namespace MiniEngine {
    namespace Graphics {
        namespace Tiling {

Tile::Tile(bool solid, const std::string *type)
    : m_is_solid(solid), m_tileset(nullptr), m_texture_id(-1), m_texture_size({0, 0}),
      m_position({0, 0, 0, 0}), m_type(*type) {}

Tile::Tile(bool solid, const std::string *type, SDL_Point position)
    : m_is_solid(solid), m_tileset(nullptr), m_texture_id(-1), m_texture_size({0, 0}),
      m_position({position.x, position.y, 0, 0}), m_type(*type) {}

std::string Tile::get_type() const { return m_type; }

bool Tile::is_solid() const { return m_is_solid; }

void Tile::set_solidity(bool solid) { m_is_solid = solid; }

/**
 * @brief Sets the texture of an element
 *
 * @param tileset The tileset containing the texture of the element
 * @param id The id of the texture in the tileset
 * @param tileset_size The size of the texture in the tileset
 */
void Tile::set_texture(MiniEngine::Graphics::TileSet *tileset, int id) {
    m_tileset = tileset;
    m_texture_id = id;
    m_position.w = tileset->get_tile_width();
    m_position.h = tileset->get_tile_height();
}

/**
 * @brief Draws current element on the given surface
 *
 * @param dest The surface to draw the element to
 * @return int 0 if success, -1 if error
 */
int Tile::draw(SDL_Surface *dest) {
    if (m_texture_id != -1) {
        return SDL_BlitSurface(m_tileset->get_texture(), (*m_tileset)[m_texture_id], dest,
                               &m_position);
    }
    return -1;
}
        }
    }
}
