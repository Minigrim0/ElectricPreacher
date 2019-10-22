/**
    name : map_manager.cpp
    purpose : Contains the source code for the MapManager class

    @author : minigrim0
    @version : 1.0
*/

#include <iostream>
#include <SDL2/SDL.h>

#include "../includes/map_manager.h"
#include "../includes/ground_element.h"

//Constructors
MapManager::MapManager(): m_position(nullptr){}

MapManager::MapManager(const MapManager& mm){
    m_position = mm.get_position();
}

MapManager::MapManager(int x, int y): m_position(nullptr){
    set_position(x, y);
}

MapManager::MapManager(SDL_Rect position): m_position(nullptr){
    set_position(position);
}

MapManager::~MapManager(){}

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
