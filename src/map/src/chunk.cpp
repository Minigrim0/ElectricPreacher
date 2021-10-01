#include "../includes/chunk.hpp"

#include <SDL2/SDL.h>
#include <initializer_list>

#include "../includes/map_element.hpp"

#include "../../screen/includes/tileset.hpp"

//Constructors
Chunk::Chunk()
:m_absolute_coordinates({0, 0}),
m_position({0, 0}),
m_chunk_size({16, 16}),
m_default_missing(nullptr),
m_layer1(nullptr),
m_layer2(nullptr),
m_layer3(nullptr)
{}

Chunk::~Chunk(){
    delete m_layer1;
    delete m_layer2;
    delete m_layer3;
}

//Overrides
Chunk& Chunk::operator=(const Chunk& chunk){
    m_absolute_coordinates = chunk.get_position();

    return *this;
}

//Getters
SDL_Point Chunk::get_position() const{
    return m_absolute_coordinates;
}

//Setters
void Chunk::set_position(int x, int y){
    m_absolute_coordinates = {x, y};
}

void Chunk::set_position(SDL_Point position){
    m_absolute_coordinates = position;
}

void Chunk::init(nlohmann::json chunk, std::map<std::string, TileSet*>* tilesets){
    TileSet* tileset = (*tilesets)["Outside"];

    m_chunk_size = {chunk["width"], chunk["height"]};
    m_position = {chunk["x"], chunk["y"]};

    m_layer1 = static_cast<MapElement***>(malloc(CHUNK_SIZE * sizeof(MapElement)));

    for(int x=0;x<m_chunk_size.x;x++){
        m_layer1[x] = static_cast<MapElement**>(malloc(m_chunk_size.y * sizeof(MapElement)));

        for(int y=0;y<m_chunk_size.y;y++){
            m_layer1[x][y] = new GroundElement();

            m_layer1[x][y]->set_texture(
                tileset, chunk["data"][x * m_chunk_size.y + y]
            );
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
