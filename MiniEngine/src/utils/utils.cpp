#include "utils/utils.hpp"

SDL_Point index_to_coord(int index, int width) { return {index % width, index / width}; }

int coord_to_index(int x, int y, int width) { return y * width + x; }
