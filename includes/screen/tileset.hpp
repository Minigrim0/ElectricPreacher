#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>

#include "screen/screen.hpp"
#include <filesystem>

namespace fs = std::filesystem;

class TileSet
{
public:
    // Constructors
    TileSet();
    TileSet(SDL_Texture *);
    ~TileSet();

    // Override
    TileSet &operator=(const TileSet &);
    SDL_Rect *operator[](std::size_t idx);

    // Getters
    SDL_Texture *get_texture() const;
    const SDL_Rect *get_sub(int, int) const;
    int blit_sub(Screen *, int, int, int, int) const;

    int get_width() const;
    int get_height() const;
    std::string get_name() const;

    // Setters
    void set_image(Screen *screen, std::string);

    // Others
    int set_array();
    void load(Screen *screen, fs::path filePath);

private:
    SDL_Texture *m_tex;
    int m_width, m_height;
    std::string m_name;

    std::vector<SDL_Rect> m_rects;
};
