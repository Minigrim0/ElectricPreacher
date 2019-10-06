/**
    name : map_manager.cpp
    purpose : Contains the source code for the MapManager class

    @author : minigrim0
    @version : 1.0
*/

#include <iostream>
#include <SDL2/SDL.h>

#include "../includes/map_manager.h"

//Cosntructors
MapManager::MapManager(): m_position(NULL){}

MapManager::MapManager(int x, int y): m_position(NULL){
    set_position(x, y);
}

MapManager::MapManager(SDL_Rect position): m_position(NULL){
    set_position(position);
}

MapManager::~MapManager(){}

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
