#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

#include "../includes/map_element.hpp"

MapElement::MapElement(bool Solid, std::string type)
:m_is_solid(Solid),
m_texture(nullptr),
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

void MapElement::set_texture(SDL_Texture *tex, int w, int h){
    m_texture_size = {0, 0, w, h};
    m_texture = tex;
}

int MapElement::draw(Screen* screen, int x, int y){
    SDL_Rect position = {x, y, m_texture_size.w, m_texture_size.h};
    return SDL_RenderCopy(screen->get_renderer(), m_texture, nullptr, &position);
}

int MapElement::draw(Screen* screen, SDL_Rect position){
    position.w = m_texture_size.w;
    position.h = m_texture_size.h;
    return SDL_RenderCopy(screen->get_renderer(), m_texture, nullptr, &position);
}

GroundElement::GroundElement()
:MapElement(false, "ground")
{}

void GroundElement::interact(Player* player){
    std::cout << "interacting with player" << std::endl;
}
