#pragma once

#include <iostream>

#include "screen/tileset.hpp"
#include "nlohmann/json.hpp"
#include "constants.hpp"

#include "map/map_element.hpp"

class Chunk
{
public:
    // Constructors
    Chunk();
    ~Chunk();

    // Overrides
    Chunk &operator=(const Chunk &);

    // Getters
    SDL_Point get_position() const;

    // Setters
    void set_position(int, int);
    void set_position(SDL_Point);

    // Others
    void init(nlohmann::json chunk, std::map<std::string, TileSet *> *tilesets, Screen *screen);
    void render(Screen *screen, SDL_Rect position);

private:
    SDL_Point m_absolute_coordinates;
    SDL_Point m_position;
    SDL_Point m_chunk_size;

    SDL_Texture *m_default_missing;

    MapElement ***m_layer1;
    MapElement ***m_layer2;
    MapElement ***m_layer3;
};
