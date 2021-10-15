#include "../includes/map_manager.hpp"

#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "../../nlohmann/json.hpp"

#include "../includes/map_element.hpp"


//Constructors
MapManager::MapManager()
:m_position({0, 0}),
m_chunks()
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

//Override
MapManager& MapManager::operator=(const MapManager& mm){
    m_position = mm.get_position();

    return *this;
}

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

void MapManager::init(Screen* screen){
    m_default_missing = screen->load_texture("assets/images/MISSING.png");

    SDL_QueryTexture(m_default_missing, NULL, NULL, &(m_position.w), &(m_position.h));
}

int MapManager::load_map(Screen* screen, fs::path path){
    std::ifstream json_in(path.c_str());
    nlohmann::json root;
    json_in >> root;
    json_in.close();

    for(int tileset_id=0;tileset_id<root["tilesets"].size();tileset_id++){
        TileSet* tileset = new TileSet();
        tileset->load(screen, path.remove_filename() / root["tilesets"][tileset_id]["source"]);
        m_tilesets[tileset->get_name()] = tileset;
    }

    this->add_layers(root["layers"]);

    return 0;
}

int MapManager::add_layers(nlohmann::json layers){
    for(int layer_id=0;layer_id<layers.size();layer_id++){
        this->add_chunks(layers[layer_id]["chunks"]);
    }
    return 0;
}

int MapManager::add_chunks(nlohmann::json chunks){
    for(int chunk_id=0;chunk_id<chunks.size();chunk_id++){
        nlohmann::json chunk = chunks[chunk_id];

        Chunk* newChunk = new Chunk();
        newChunk->set_position(chunk["x"], chunk["y"]);
        newChunk->init(chunk, &m_tilesets);
        m_chunks.push_back(newChunk);
    }

    return 0;
}

int MapManager::render(Screen *screen, SDL_Rect position){
    // Completely ignore position for now, will be used with the camera

    for(auto y=0;y<1;y++){
        position.y = y * 32 * CHUNK_SIZE;
        for(auto x=0;x<m_chunks.size();x++){
            position.x = x * 32 * CHUNK_SIZE;
            m_chunks[x]->render(screen, position);
        }
    }

    return 0;
}
