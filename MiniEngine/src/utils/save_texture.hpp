#pragma once

#include <SDL.h>

#include "core/screen.hpp"

namespace MiniEngine {
    namespace Utils {
        /**
         * @brief Save a texture to a file
         * 
         * @param screen The screen from which the texture is from
         * @param texture The texture to save
         * @param filename The name of the file to save to
         */
        void save_texture(Screen *screen, SDL_Texture *texture, const char *filename);
    }
}
