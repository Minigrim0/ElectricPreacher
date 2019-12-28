#ifndef ground_element_h
    #define ground_element_h

/**
    name : ground_element.h
    purpose : defines an element of the ground (grass, rock,...)
    Can be a trap or a staircase

    @author : minigrim0
    @version : 1.0
*/

#include <iostream>
#include <SDL2/SDL.h>

#include "map_element.h"

class GroundElement: public MapElement{
    public:
        //Constructors
        GroundElement();
        ~GroundElement();

        //Others
        int draw(Screen*, int, int);
        int draw(Screen*, SDL_Rect);
};

#endif
