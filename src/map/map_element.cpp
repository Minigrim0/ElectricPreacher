#include "map/map_element.hpp"

#include <SDL.h>
#include <SDL_rect.h>
#include <SDL_ttf.h>

MapElement::MapElement(bool solid, std::string type)
:m_is_solid(solid),
m_tileset(nullptr),
m_texture_id(-1),
m_texture_size({0, 0}),
m_position({0, 0, 0, 0}),
m_type(type)
{}

MapElement::MapElement(bool solid, std::string type, SDL_Point position)
:m_is_solid(solid),
m_tileset(nullptr),
m_texture_id(-1),
m_texture_size({0, 0}),
m_position({position.x, position.y, 0, 0}),
m_type(type)
{}

std::string MapElement::get_type() const{
    return m_type;
}

bool MapElement::is_solid() const{
    return m_is_solid;
}

void MapElement::set_solidity(bool Solid){
    m_is_solid = Solid;
}

/**
 * @brief Sets the texture of an element
 * 
 * @param tileset The tileset containing the texture of the element
 * @param id The id of the texture in the tileset
 * @param tileset_size The size of the texture in the tileset
 */
void MapElement::set_texture(TileSet* tileset, int id, SDL_Point tileset_size){
    m_tileset = tileset;
    m_texture_id = id;
    m_texture_size = tileset_size;
}

/**
 * @brief Draws current element on the given surface
 * 
 * @param dest The surface to draw the element to
 * @return int 0 if success, -1 if error
 */
int MapElement::draw(SDL_Surface* dest){
    if(m_texture_id != -1){
        m_position.w = m_texture_size.x;
        m_position.h = m_texture_size.y;

        return SDL_BlitSurface(
            m_tileset->get_texture(),
            (*m_tileset)[m_texture_id],
            dest,
            &m_position
        );
    }
    return -1;
}


GroundElement::GroundElement(SDL_Point position)
:MapElement(false, "ground", position)
{}

void GroundElement::interact(Player* player){
    std::cout << "interacting with player" << std::endl;
}
