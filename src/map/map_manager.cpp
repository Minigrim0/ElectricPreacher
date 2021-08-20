/**
    name : map_manager.cpp
    purpose : Contains the source code for the MapManager class

    @author : minigrim0
    @version : 1.0
*/

#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "../../includes/nlohmann/json.hpp"

#include "../../includes/map/map_manager.hpp"
#include "../../includes/map/map_element.hpp"

//Constructors
MapManager::MapManager()
:m_position(new SDL_Rect),
m_chunk()
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

MapManager::~MapManager(){
    delete m_position;
}

//Override
MapManager& MapManager::operator=(const MapManager& mm){
    m_position = mm.get_position();

    return *this;
}

//Getters
SDL_Rect* MapManager::get_position() const{
    return m_position;
}

//Setters
void MapManager::set_position(SDL_Rect pos){
    m_position = &pos;
}

void MapManager::set_position(int x, int y){
    m_position->x = x;
    m_position->y = y;
}

void MapManager::init(Screen* screen){
    m_default_missing = screen->load_texture("assets/images/MISSING.png");

    SDL_QueryTexture(m_default_missing, NULL, NULL, &(m_position->w), &(m_position->h));

    for(auto &elem: m_chunk){
        elem->init(screen);
    }
}

int MapManager::load_map(std::string path){
    std::ifstream json_in(path.c_str());
    nlohmann::json root;
    json_in >> root;
    json_in.close();

    this->add_layers(root["layers"]);

    for(int x=0;x<9;x++){
        Chunk* newChunk = new Chunk();
        newChunk->set_position(x % 3 * CHUNK_SIZE, x / 3 * CHUNK_SIZE);
        m_chunk.push_back(newChunk);
    }

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
        std::cout << chunks[chunk_id]["x"] << chunks[chunk_id]["y"] << std::endl;
    }
    return 0;
}

int MapManager::render(Screen *screen, SDL_Rect position){
    SDL_Rect initial_position = {position.x - SCREEN_X/2, position.y - SCREEN_Y/2, 0, 0};
    for(long long unsigned int x=0;x<3;x++){
        position.x = initial_position.x + x*32*CHUNK_SIZE;
        for(int y=0;y<3;y++){
            position.y = initial_position.y + y*32*CHUNK_SIZE;
            m_chunk[x]->render(screen, position);
        }
    }

    return 0;
}
