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

int MapManager::load(Screen* screen, fs::path path){
    std::ifstream json_in(path.c_str());
    nlohmann::json root;
    json_in >> root;
    json_in.close();

    bool result = 0;

    result |= this->load_tilesets(root["tilesets"], screen, path);
    result |= this->add_layers(root["layers"], screen);

    return result;
}

int MapManager::load_tilesets(nlohmann::json tilesets, Screen* screen, fs::path path){
    for(int tileset_id=0;tileset_id<tilesets.size();tileset_id++){
        TileSet* tileset = new TileSet();
        tileset->load(screen, path.remove_filename() / tilesets[tileset_id]["source"]);
        m_tilesets[tileset->get_name()] = tileset;
    }
}

int MapManager::add_layers(nlohmann::json layers, Screen* screen){
    for(int layer_id=0;layer_id<layers.size();layer_id++){
        this->add_chunks(layers[layer_id]["chunks"], screen);
    }
    return 0;
}

int MapManager::add_chunks(nlohmann::json chunks, Screen* screen){
    for(int chunk_id=0;chunk_id<chunks.size();chunk_id++){
        nlohmann::json chunk = chunks[chunk_id];

        Chunk* newChunk = new Chunk();
        newChunk->set_position(chunk["x"], chunk["y"]);
        newChunk->load(chunk, &m_tilesets, screen);
        m_chunks.push_back(newChunk);
    }

    return 0;
}

int MapManager::render(Screen *screen){
    // Completely ignore position for now, will be used with the camera
    for(auto y=0;y<1;y++){
        for(auto x=0;x<m_chunks.size();x++){
            m_chunks[x]->render(screen);
        }
    }

    return 0;
}
