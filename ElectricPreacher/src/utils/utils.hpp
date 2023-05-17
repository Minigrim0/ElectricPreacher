#pragma once

#include <SDL.h>
#include <core/screen.hpp>

#include "constants.hpp"

/**
 * @brief Save a texture to a file
 * 
 * @param screen The screen from which the texture is from
 * @param texture The texture to save
 * @param filename The name of the file to save to
 */
void save_texture(CORE::Screen *screen, SDL_Texture *texture, const char *filename);

/**
 * @brief Convert an index to a coordinate
 * 
 * @param index A tile index
 * @param width the width of the tileset (in tiles, not pixels)
 * @return SDL_Point The coordinate of the tile on the tileset
 */
SDL_Point index_to_coord(int index, int width);

/**
 * @brief Convert a coordinate to an index
 * 
 * @param x The x coordinate of the tile on the tileset
 * @param y The y coordinate of the tile on the tileset
 * @param width The width of the tileset (in tiles, not pixels)
 * @return int The index of the tile
 */
int coord_to_index(int x, int y, int width);
