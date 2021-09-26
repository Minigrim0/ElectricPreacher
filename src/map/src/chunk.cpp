#include "../includes/chunk.hpp"

#include <SDL2/SDL.h>
#include <initializer_list>

#include "../includes/map_element.hpp"

#include "../../screen/includes/tileset.hpp"

//Constructors
Chunk::Chunk()
:m_absolute_coordinates(new SDL_Rect),
m_default_missing(nullptr),
m_layer1(nullptr),
m_layer2(nullptr),
m_layer3(nullptr)
{
    m_absolute_coordinates->x = 0;
    m_absolute_coordinates->y = 0;
}

Chunk::~Chunk(){
    delete m_absolute_coordinates;
}

//Overrides
Chunk& Chunk::operator=(const Chunk& chunk){
    *m_absolute_coordinates = chunk.get_position();

    return *this;
}

//Getters
SDL_Rect Chunk::get_position() const{
    return *m_absolute_coordinates;
}

//Setters
void Chunk::set_position(int x, int y){
    m_absolute_coordinates->x = x;
    m_absolute_coordinates->y = y;
}

void Chunk::set_position(SDL_Rect position){
    *m_absolute_coordinates = position;
}

void Chunk::init(Screen* screen){
    m_default_missing = screen->load_texture("assets/images/MISSING.png");

    m_layer1 = static_cast<MapElement***>(malloc(CHUNK_SIZE * sizeof(MapElement)));

    for(int x=0;x<CHUNK_SIZE;x++){
        m_layer1[x] = static_cast<MapElement**>(malloc(CHUNK_SIZE * sizeof(MapElement)));
        for(int y=0;y<CHUNK_SIZE;y++){
            m_layer1[x][y] = new GroundElement();
            m_layer1[x][y]->set_texture(m_default_missing);
        }
    }
}

void Chunk::render(Screen* screen, SDL_Rect position){
    SDL_Rect initial_position = position;
    for(int x=0;x<CHUNK_SIZE;x++){
        position.x = initial_position.x + x*32;
        for(int y=0;y<CHUNK_SIZE;y++){
            position.y = initial_position.y + y*32;
            m_layer1[x][y]->draw(screen, position);
        }
    }
}
