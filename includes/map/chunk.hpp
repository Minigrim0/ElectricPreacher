#pragma once

#include <iostream>

#include "screen/tileset.hpp"
#include "nlohmann/json.hpp"
#include "constants.hpp"

#include "map/map_element.hpp"

/**
 * @brief A chunk is a part of the map, which size is defined by the map manager
 * It is pre-loaded and rendered, and can be unloaded when the player is too far away
 */
class Chunk
{
public:
    // Constructors
    Chunk();
    Chunk(int chunk_size, SDL_Point position);
    ~Chunk();

    // Getters
    SDL_Point get_position() const;

    // Setters
    void set_position(int, int);
    void set_position(SDL_Point);

    // Others
    void load(nlohmann::json chunk, std::map<std::string, TileSet *> *tilesets, Screen *screen);
    void render(Screen *screen);

private:
    SDL_Point m_absolute_coordinates;
    SDL_Point m_chunk_size;
    SDL_Rect m_position;

    SDL_Texture *m_texture;
    MapElement **m_elements;
};
