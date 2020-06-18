#ifndef map_element_h
    #define map_element_h

/**
    name : map_element.h
    purpose : An abstract class, defining the base for each
    element of the map (Ground, wall, ...)
*/

#include <iostream>
#include <SDL2/SDL.h>

#include "screen.h"

class MapElement{
    public:
        //Constructors
        virtual ~MapElement();

        //Getters
        virtual std::string get_type() const = 0;
        virtual bool get_accessibility(int) const = 0;
        virtual SDL_Rect* get_rect() const = 0;

        //Setters
        virtual void set_accessibility(int, bool) = 0;
        virtual void set_rect(SDL_Rect) = 0;
        virtual void set_rect(int, int, int, int) = 0;

        //Others
        virtual int draw(Screen*, int, int) = 0;
        virtual int draw(Screen*, SDL_Rect) = 0;
};

#endif
