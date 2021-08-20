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

#include "../screen.hpp"
#include "../player.hpp"

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
        void set_texture(SDL_Texture *tex, int w=32, int h=32);

        //Others
        int draw(Screen*, int, int);
        int draw(Screen*, SDL_Rect);

        virtual void interact(Player* player) = 0;

    private:
        bool m_is_solid;
        SDL_Texture* m_texture;
        SDL_Rect m_texture_size;
        std::string m_type;
};

class GroundElement: public MapElement{
    public:
        GroundElement();
        ~GroundElement() = default;

        void interact(Player* player) override;
    private:

};

#endif
