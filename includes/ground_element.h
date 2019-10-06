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

        //Setters
        void set_type(std::string);

    private:
        SDL_Surface* m_image;
        std::string m_type;
};

#endif
