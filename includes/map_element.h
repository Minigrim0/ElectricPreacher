#ifndef map_element_h
    #define map_element_h

/**
    name : map_element.h
    purpose : Contains the base prototypes for each class
    defining an element of the map
*/

#include <iostream>
#include <SDL2/SDL.h>

#include "screen.h"

/**
    Class : MapElement
    purpose : A 'Super' class, defining the base for each element
    of the map
*/
class MapElement{
    public:
        MapElement();
        ~MapElement();

        //Getters
        std::string get_type() const;
        bool get_accessibility(int) const;

        //Setters
        void set_accessibility(int, bool) const;
        void set_type(std::string);
        void set_rect(SDL_Rect);
        void set_rect(int, int, int, int);

        //Others
        int draw(Screen*, int, int);
        int draw(Screen*, SDL_Rect);

    protected:
        SDL_Rect m_image_rect;
        std::string m_type;
        bool m_accessibility[4];
};

#endif
