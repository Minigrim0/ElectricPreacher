#ifndef ground_element_h
    #define ground_element_h

/**
    name : ground_element.h
    purpose : Contains the prototypes of the GroundElement class

    @author : minigrim0
    @version : 1.0
*/

#include <iostream>
#include <SDL2/SDL.h>

#include "map_element.h"

/**
    Class : GroundElement
    purpose : defines an element of the ground (grass, rock,...)
    Can be a trap or a staircase
*/
class GroundElement: public MapElement{
    public:
        int draw(Screen*, int, int);
        int draw(Screen*, SDL_Rect);
};

#endif
