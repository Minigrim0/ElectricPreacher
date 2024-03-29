#include "map/map_element.hpp"
#include "map/elements/elements.hpp"

MapElement::MapElement(bool solid, const std::string *type)
:m_is_solid(solid),
m_tileset(nullptr),
m_texture_id(-1),
m_texture_size({0, 0}),
m_position({0, 0, 0, 0}),
m_type(*type)
{}

MapElement::MapElement(bool solid, const std::string *type, SDL_Point position)
:m_is_solid(solid),
m_tileset(nullptr),
m_texture_id(-1),
m_texture_size({0, 0}),
m_position({position.x, position.y, 0, 0}),
m_type(*type)
{}

std::string MapElement::get_type() const{
    return m_type;
}

bool MapElement::is_solid() const{
    return m_is_solid;
}

void MapElement::set_solidity(bool solid){
    m_is_solid = solid;
}

/**
 * @brief Sets the texture of an element
 * 
 * @param tileset The tileset containing the texture of the element
 * @param id The id of the texture in the tileset
 * @param tileset_size The size of the texture in the tileset
 */
void MapElement::set_texture(MiniEngine::Graphics::TileSet* tileset, int id){
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
int MapElement::draw(SDL_Surface* dest){
    if(m_texture_id != -1){
        return SDL_BlitSurface(
            m_tileset->get_texture(),
            (*m_tileset)[m_texture_id],
            dest,
            &m_position
        );
    }
    return -1;
}
