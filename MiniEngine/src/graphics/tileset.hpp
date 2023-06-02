#pragma once

#include <filesystem>
#include <vector>
#include <SDL.h>

#include "core/screen.hpp"

namespace fs = std::filesystem;

/**
 * @author Minigrim0
 * @brief A tileset is a set of tiles, which can be used to draw a map
 * It is loaded from a .tsx file, which is an XML file.
 * It contains the path to the texture, the size of the tiles, and the size of the texture
 */
namespace MiniEngine {
    namespace Graphics {
        class TileSet {
        public:
            // Constructors
            TileSet();
            explicit TileSet(SDL_Surface *);
            ~TileSet();

            // Override
            SDL_Rect *operator[](std::size_t idx);

            // Getters
            inline SDL_Surface *get_texture() const { return m_tex; }

            const SDL_Rect *get_sub(int, int) const;

            inline int get_width() const { return m_width; }
            inline int get_height() const { return m_height; }
            inline int get_tile_width() const { return m_tile_width; }
            inline int get_tile_height() const { return m_tile_height; }
            inline std::string get_name() const { return m_name; }

            void load(Screen *screen, fs::path filePath);

        private:
            int set_array();

            SDL_Surface* m_tex;
            int m_width, m_height;
            int m_tile_width, m_tile_height;
            std::string m_name;

            std::vector<SDL_Rect> m_rects;
        };
    }
}
