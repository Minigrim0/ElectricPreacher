/**
    name : ground_element.cpp
    purpose : Contains the source code for the class GroundElement

    @author : minigrim0
    @version : 1.0
*/

#include <iostream>

#include "../includes/ground_element.h"

//Others
int GroundElement::draw(Screen* screen, int x, int y){
    return screen->blit_surface(m_image_rect, x, y);
}

int GroundElement::draw(Screen* screen, SDL_Rect rect){
    return screen->blit_surface(m_image_rect, rect);
}
