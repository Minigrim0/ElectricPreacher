/**
    name : ground_element.cpp
    purpose : Contains the source code for the class GroundElement

    @author : minigrim0
    @version : 1.0
*/

#include <iostream>

#include "../includes/ground_element.h"

//Constructors
GroundElement::GroundElement(){}

GroundElement::~GroundElement(){}

//Getters
std::string GroundElement::get_type() const{return m_type;}
bool GroundElement::get_accessibility(int dir) const{return m_accessibility[dir];}

//Setters
void GroundElement::set_type(std::string type){
    m_type = type;
}

void GroundElement::set_rect(SDL_Rect rect){
    m_image_rect = rect;
}

void GroundElement::set_rect(int x, int y, int w, int h){
    m_image_rect.x = x;
    m_image_rect.y = y;
    m_image_rect.w = w;
    m_image_rect.h = h;
}

//Others
int GroundElement::draw(Screen* screen, int x, int y){
    return screen->blit_surface(&m_image_rect, x, y);
}

int GroundElement::draw(Screen* screen, SDL_Rect rect){
    return screen->blit_surface(&m_image_rect, rect);
}
