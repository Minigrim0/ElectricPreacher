/**
    name : chunk.cpp
    purpose : Contains the source code for the chunk class

    @author : minigrim0
    @version : 1.0
*/

#include <SDL2/SDL.h>
#include "../includes/chunk.hpp"
#include "../includes/image_set.hpp"

//Constructors
Chunk::Chunk()
:m_absolute_coordinates(new SDL_Rect),
m_layer1(nullptr),
m_layer2(nullptr),
m_layer3(nullptr)
{
    m_absolute_coordinates->x = 0;
    m_absolute_coordinates->y = 0;
}

Chunk::~Chunk(){
    delete m_absolute_coordinates;
}

//Overrides
Chunk& Chunk::operator=(const Chunk& chunk){
    *m_absolute_coordinates = chunk.get_position();

    return *this;
}

//Getters
SDL_Rect Chunk::get_position() const{
    return *m_absolute_coordinates;
}

//Setters
void Chunk::set_position(int x, int y){
    m_absolute_coordinates->x = x;
    m_absolute_coordinates->y = y;
}

void Chunk::set_position(SDL_Rect position){
    *m_absolute_coordinates = position;
}
