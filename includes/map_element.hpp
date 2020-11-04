#ifndef map_element_h
    #define map_element_h

/**
    name : map_element.h
    purpose : An abstract class, defining the base for each
    element of the map (Ground, wall, ...)
*/

#include <SDL2/SDL_render.h>
#include <iostream>
#include <SDL2/SDL.h>

#include "screen.hpp"

class MapElement{
    public:
        //Constructors
        MapElement(bool Solid, std::string type);
        virtual ~MapElement() = default;

        //Getters
        std::string get_type() const;
        bool is_solid() const;

        //Setters
        void set_solidity(bool);
        void set_texture(SDL_Texture *tex);

        //Others
        int draw(Screen*, int, int);
        int draw(Screen*, SDL_Rect);

        virtual void interact() = 0;

    private:
        bool m_is_solid;
        SDL_Texture* m_texture;
        std::string m_type;
};

class GroundElement: public MapElement{
    public:
        GroundElement();
        ~GroundElement() = default;

    private:

};

#endif
