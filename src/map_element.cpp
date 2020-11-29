#include "../includes/map_element.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

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

void MapElement::set_texture(SDL_Texture *tex){
    m_texture = tex;
}

int MapElement::draw(Screen* screen, int x, int y){
    SDL_Rect position = {x, y, 0, 0};
    SDL_RenderCopy(screen->get_renderer(), m_texture, nullptr, &position);
    //SDL_RenderCopy(screen->get_renderer(), m_texture, NULL, &position);

    return 0;
}

int MapElement::draw(Screen* screen, SDL_Rect position){
    SDL_RenderCopy(screen->get_renderer(), m_texture, nullptr, &position);
    //SDL_RenderCopy(screen->get_renderer(), m_texture, NULL, &position);

    return 0;
}

GroundElement::GroundElement()
:MapElement(false, "ground")
{}

void GroundElement::interact(Player* player){
    std::cout << "interacting with player" << std::endl;
}