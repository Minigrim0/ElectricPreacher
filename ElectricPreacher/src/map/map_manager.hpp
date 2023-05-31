#pragma once

#include <iostream>
#include <vector>

#include <SDL_render.h>
#include <SDL.h>

#include <nlohmann/json.hpp>
#include <event/interactible.hpp>

#include "constants.hpp"

#include "map/chunk.hpp"

#include <filesystem>
namespace fs = std::filesystem;

/**
 * @author Minigrim0
 * @brief Manages a "chunk" of the total map, which size is defined by CHUNK_SIZE
 * A chunk is composed of three layers of "items/images", the ground, the scenery, and the "objects"
 */
class MapManager : public MiniEngine::Event::Interactible
{
public:
    // Constructors
    MapManager();
    MapManager(int, int);
    explicit MapManager(SDL_Rect);
    ~MapManager();

    // Getters
    SDL_Rect get_position() const;

    // Setters
    void set_position(SDL_Rect);
    void set_position(int, int);

    // Others
    void init(MiniEngine::Screen *screen);
    int load(MiniEngine::Screen *screen, fs::path path);

    // Override
    bool OnEvent(SDL_Event* e) override;
    void OnRender(MiniEngine::Screen* screen) override;
    void OnUpdate(int time_elapsed) override;

private:
    int load_tilesets(nlohmann::json tilesets, MiniEngine::Screen *screen, fs::path path);
    int add_layers(nlohmann::json layers, MiniEngine::Screen *screen);
    int add_chunks(nlohmann::json chunks, MiniEngine::Screen *screen);

    SDL_Texture *m_default_missing;
    SDL_Rect m_position;
    SDL_Point m_origin;
    std::vector<Chunk *> m_chunks;
    std::map<std::string, MiniEngine::Graphics::TileSet *> m_tilesets;

    int m_tilewidth, m_tileheight;
    int chunk_width, chunk_height;
};
