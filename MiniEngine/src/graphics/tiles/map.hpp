#pragma once

#include <filesystem>
#include <iostream>
#include <vector>

#include <SDL.h>
#include <SDL_render.h>
#include <nlohmann/json.hpp>

#include "event/interactible.hpp"
#include "graphics/tiles/chunk.hpp"

namespace fs = std::filesystem;

namespace MiniEngine::Graphics::Tiling {

/**
 * @brief Represents a 2D tiled map. The map is composed of tilesets, chunks and layers.
 * It can be loaded from a json export of a tiled map.
 */
class Map : public MiniEngine::Event::Interactible {
  public:
    // Constructors
    Map();
    Map(int, int);
    explicit Map(SDL_Rect);
    ~Map();

    // Getters
    SDL_Rect get_position() const;

    // Setters
    void set_position(SDL_Rect);
    void set_position(int, int);

    // Others
    void init(MiniEngine::Screen *screen);
    int jload(MiniEngine::Screen *screen, fs::path path);

    // Override
    bool OnEvent(SDL_Event *e) override;
    void OnRender(MiniEngine::Screen *screen) override;
    void OnUpdate(int time_elapsed) override;

  private:
    int load_tilesets(nlohmann::json tilesets, MiniEngine::Screen *screen, fs::path path);
    int add_layers(nlohmann::json layers, MiniEngine::Screen *screen);
    int add_chunks(nlohmann::json chunks, MiniEngine::Screen *screen);

    SDL_Texture *m_default_missing;
    SDL_Rect m_position;
    SDL_Point m_origin;
    std::vector<Chunk *> m_chunks;
    std::map<std::string, TileSet *> m_tilesets;

    int m_tilewidth, m_tileheight;
    int chunk_width, chunk_height;
};
} // namespace MiniEngine::Graphics::Tiling