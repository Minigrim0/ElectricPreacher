#ifndef wall_element_h
    #define wall_element_h

/**
    name : wall_element.h
    purpose : Constains the prototypes for the WallElement class

    @author : minigrim0
    @version : 1.0
*/

#include <iostream>
#include <SDL2/SDL.h>
#include "map_element.h"

/**
    Class : WallElement
    Purpose : defines a wall, can be breaked, can be a secret way,
    a trap, ...
*/
class WallElement: public MapElement{
    public:
        WallElement();
        ~WallElement();

    private:
        bool m_is_trap;
        bool m_breakable;
        bool m_transparent;
};

#endif
