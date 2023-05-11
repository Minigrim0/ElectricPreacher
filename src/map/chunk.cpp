#include "map/chunk.hpp"

#include <SDL.h>
#include <initializer_list>

#include "map/map_element.hpp"

#include "screen/tileset.hpp"
#include "utils/utils.hpp"


//Constructors
Chunk::Chunk()
:m_absolute_coordinates({0, 0}),
m_position({0, 0}),
m_chunk_size({0, 0}),
m_texture(nullptr),
m_elements(nullptr)
{}


Chunk::Chunk(int chunk_size, SDL_Point position)
:m_absolute_coordinates({0, 0}),
m_position({position.x, position.y, 0, 0}),
m_chunk_size({chunk_size, chunk_size}),
m_texture(nullptr),
m_elements(nullptr)
{}

Chunk::~Chunk(){}

//Getters
SDL_Point Chunk::get_position() const{
    return m_absolute_coordinates;
}

//Setters
void Chunk::set_position(int x, int y){
    m_absolute_coordinates = {x, y};
    m_position.x = x;
    m_position.y = y;
}

void Chunk::set_position(SDL_Point position){
    m_absolute_coordinates = position;
    m_position = {position.x, position.y, 0, 0};
}

/**
 * @brief Loads the chunk from the json file
 * 
 * @param chunk The json description of the chunk
 * @param tilesets The available tilesets
 * @param screen The screen to render the chunk on
 */
void Chunk::load(nlohmann::json chunk, std::map<std::string, TileSet*>* tilesets, Screen* screen){
    // TODO: Change this hardcoded tileset name
    TileSet* tileset = (*tilesets)["Outside"];

    m_chunk_size = {chunk["width"], chunk["height"]};
    m_position = {chunk["x"], chunk["y"]};

    m_elements = static_cast<MapElement**>(malloc(m_chunk_size.x * m_chunk_size.y * sizeof(MapElement)));

    // Create a Surface for chunk pre-rendering
    SDL_Surface* surface = SDL_CreateRGBSurface(0, m_chunk_size.x * 32, m_chunk_size.y * 32, 32, 0, 0, 0, 0);

    for(int y=0;y<m_chunk_size.y;y++){
        for(int x=0;x<m_chunk_size.x;x++){
            GroundElement* newElem = new GroundElement({x * m_chunk_size.x, y * m_chunk_size.y});
            newElem->set_texture(
                tileset, chunk["data"][coord_to_index(x, y, m_chunk_size.x)].get<int>() - 1, {32, 32}
            );
            // Draw the element on the surface
            newElem->draw(surface);
            m_elements[coord_to_index(x, y, m_chunk_size.x)] = newElem;
        }
    }

    // Convert the surface to a texture
    m_texture = SDL_CreateTextureFromSurface(screen->get_renderer(), surface);
}

/**
 * @brief Renders the chunk on the screen
 * 
 * @param screen The screen object to render the chunk to
 * @param position The position on the screen
 */
void Chunk::render(Screen* screen){
    SDL_RenderCopy(
        screen->get_renderer(),
        m_texture,
        NULL,
        &m_position
    );
}
