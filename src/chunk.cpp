/**
    name : chunk.cpp
    purpose : Contains the source code for the chunk class

    @author : minigrim0
    @version : 1.0
*/

#include <SDL2/SDL.h>
#include "../includes/chunk.h"
#include "../includes/image_set.h"

//Constructors
Chunk::Chunk()
:m_image_set(new ImageSet),
m_position(new SDL_Rect),
m_layer1(nullptr),
m_layer2(nullptr),
m_layer3(nullptr)
{
    m_position->x = 0;
    m_position->y = 0;
}

Chunk::Chunk(Chunk& chunk)
:m_image_set(new ImageSet),
m_position(new SDL_Rect),
m_layer1(nullptr),
m_layer2(nullptr),
m_layer3(nullptr)
{
    *m_position = chunk.get_position();
    m_image_set = chunk.get_image_set();
}

Chunk::~Chunk(){
    delete m_image_set;
    delete m_position;
}

//Overrides
Chunk& Chunk::operator=(const Chunk& chunk){
    *m_position = chunk.get_position();
    m_image_set = chunk.get_image_set();

    return *this;
}

//Getters
SDL_Rect Chunk::get_position() const{
    return *m_position;
}

ImageSet* Chunk::get_image_set() const{
    return m_image_set;
}

//Setters
void Chunk::set_position(int x, int y){
    m_position->x = x;
    m_position->y = y;
}

void Chunk::set_position(SDL_Rect position){
    *m_position = position;
}

void Chunk::set_image_set(ImageSet* img_set){
    m_image_set = img_set;
}

void Chunk::set_image_set(std::string){
    m_image_set = new ImageSet;
}
