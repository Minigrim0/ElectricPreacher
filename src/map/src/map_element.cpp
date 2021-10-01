#include "../includes/map_element.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

MapElement::MapElement(bool Solid, std::string type)
:m_is_solid(Solid),
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

void MapElement::set_texture(TileSet* tileset, int id){
    m_tileset = tileset;
    m_texture_id = id;
}

int MapElement::draw(Screen* screen, int x, int y){
    SDL_Rect position = {x, y, m_texture_size.w, m_texture_size.h};
    return SDL_RenderCopy(
        screen->get_renderer(),
        m_tileset->get_texture(),
        (*m_tileset)[m_texture_id],
        &position
    );
}

int MapElement::draw(Screen* screen, SDL_Rect position){
    position.w = m_texture_size.w;
    position.h = m_texture_size.h;
    return SDL_RenderCopy(
        screen->get_renderer(),
        m_tileset->get_texture(),
        (*m_tileset)[m_texture_id],
        &position
    );
}


GroundElement::GroundElement()
:MapElement(false, "ground")
{}

void GroundElement::interact(Player* player){
    std::cout << "interacting with player" << std::endl;
}
