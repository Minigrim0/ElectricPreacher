#include "map/map_manager.hpp"

#include <iostream>
#include <fstream>

#include <SDL.h>
#include <SDL_rect.h>
#include <SDL_render.h>

#include "nlohmann/json.hpp"

#include "map/map_element.hpp"


//Constructors
MapManager::MapManager()
:m_default_missing(nullptr),
m_position({0, 0}),
m_origin({0, 0}),
m_chunks(std::vector<Chunk*>()),
m_tilesets(std::map<std::string, MiniEngine::Graphics::TileSet*>()),
m_tilewidth(32),
m_tileheight(32),
chunk_width(16),
chunk_height(16)
{}

MapManager::MapManager(int x, int y)
:MapManager()
{
    set_position(x, y);
}

MapManager::MapManager(SDL_Rect position)
:MapManager()
{
    set_position(position);
}

MapManager::~MapManager(){}

//Getters
SDL_Rect MapManager::get_position() const{
    return m_position;
}

//Setters
void MapManager::set_position(SDL_Rect pos){
    m_position = pos;
}

void MapManager::set_position(int x, int y){
    m_position = {x, y};
}

void MapManager::init(MiniEngine::Screen* screen){
    m_default_missing = screen->load_texture("assets/images/MISSING.png");

    SDL_QueryTexture(m_default_missing, NULL, NULL, &(m_position.w), &(m_position.h));
}

int MapManager::load(MiniEngine::Screen* screen, fs::path path){
    std::ifstream json_in(path.c_str());
    nlohmann::json root;
    json_in >> root;
    json_in.close();

    bool result = 0;

    result |= this->load_tilesets(root["tilesets"], screen, path);
    result |= this->add_layers(root["layers"], screen);

    return result;
}

int MapManager::load_tilesets(nlohmann::json tilesets, MiniEngine::Screen* screen, fs::path path){
    for(int tileset_id=0;tileset_id<tilesets.size();tileset_id++){
        MiniEngine::Graphics::TileSet* tileset = new MiniEngine::Graphics::TileSet();
        tileset->load(screen, path.remove_filename() / tilesets[tileset_id]["source"]);
        m_tilesets[tileset->get_name()] = tileset;
    }
    return 0;
}

int MapManager::add_layers(nlohmann::json layers, MiniEngine::Screen* screen){
    for(int layer_id=0;layer_id<layers.size();layer_id++){
        this->add_chunks(layers[layer_id]["chunks"], screen);
    }
    return 0;
}

/**
 * @brief Adds some chunks to the map
 * 
 * @param chunks The list of chunks
 * @param screen The screen to render the chunks on
 * @return int 0 if success, -1 if error
 */
int MapManager::add_chunks(nlohmann::json chunks, MiniEngine::Screen* screen){
    for(int chunk_id=0;chunk_id<chunks.size();chunk_id++){
        nlohmann::json chunk = chunks[chunk_id];

        Chunk* newChunk = new Chunk();
        newChunk->load(chunk, &m_tilesets, screen);
        m_chunks.push_back(newChunk);
    }

    return 0;
}

void MapManager::OnRender(MiniEngine::Screen* screen){
    // Completely ignore position for now, will be used with the camera
    for(auto x=0;x<m_chunks.size();x++){
        m_chunks[x]->OnRender(screen);
    }
}

bool MapManager::OnEvent(SDL_Event* event){
    return false;
}

void MapManager::OnUpdate(int time_elapsed){
    for(auto x=0;x<m_chunks.size();x++){
        m_chunks[x]->OnUpdate(time_elapsed);
    }
}
