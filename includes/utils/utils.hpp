#pragma once

#include <SDL.h>
#include "screen/screen.hpp"

void save_texture(Screen *screen, SDL_Texture *texture, const char *filename);
SDL_Point index_to_coord(int index, int width);
int coord_to_index(int x, int y, int width);
