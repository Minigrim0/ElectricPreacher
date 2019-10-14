/**

*/

#include "../includes/map_element.h"

//Constructors
MapElement::MapElement(){}

MapElement::~MapElement(){}

//Getters
std::string MapElement::get_type() const{return m_type;}
bool MapElement::get_accessibility(int dir) const{return m_accessibility[dir];}

//Setters
void MapElement::set_type(std::string type){
    m_type = type;
}

void MapElement::set_rect(SDL_Rect rect){
    m_image_rect = rect;
}

void MapElement::set_rect(int x, int y, int w, int h){
    m_image_rect.x = x;
    m_image_rect.y = y;
    m_image_rect.w = w;
    m_image_rect.h = h;
}
