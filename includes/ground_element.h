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

#include "screen.h"

/**
    Class : GroundElement
    purpose : defines an element of the ground (grass, rock,...)
    Can be a trap or a staircase
*/
class GroundElement{
    public:
        //Constructors
        GroundElement();
        ~GroundElement();

        //Getters
        std::string get_type() const;
        bool get_accessibility(int) const;

        //Setters
        void set_type(std::string);
        void set_rect(SDL_Rect);
        void set_rect(int, int, int, int);

        //Others
        int draw(Screen*, int, int);
        int draw(Screen*, SDL_Rect);

    private:
        SDL_Rect m_image_rect;
        std::string m_type;
        bool m_accessibility[4];
};

#endif
