#pragma once

#include <filesystem>
#include <vector>

#include <SDL.h>

#include "core/core.hpp"
#include "core/screen.hpp"

namespace fs = std::filesystem;

namespace MiniEngine::Graphics::Tiling {
/**
 * @author Minigrim0
 * @brief A tileset is a set of tiles, which can be used to draw a map
 * It is loaded from a .tsx file, which is an XML file.
 * It contains the path to the texture, the size of the tiles, and the size of the texture
 */
class ME_API TileSet {
  public:
    // Constructors
    TileSet();
    explicit TileSet(SDL_Surface *img);
    virtual ~TileSet();

    // Override
    inline SDL_Rect *operator[](std::size_t idx) { return &(_rects[idx]); }

    // Getters
    inline SDL_Surface *get_texture() const { return _texture; }

    const SDL_Rect *get_sub(int, int) const;

    inline int get_width() const { return _width; }
    inline int get_height() const { return _height; }
    inline int get_tile_width() const { return _tile_width; }
    inline int get_tile_height() const { return _tile_height; }
    inline std::string get_name() const { return _name; }

    void load(Screen *screen, fs::path filePath);

  private:
    int set_array();

    SDL_Surface *_texture;
    int _width, _height;
    int _tile_width, _tile_height;
    std::string _name;

    std::vector<SDL_Rect> _rects;
};
} // namespace MiniEngine::Graphics::Tiling
