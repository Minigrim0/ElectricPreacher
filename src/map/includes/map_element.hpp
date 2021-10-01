#ifndef map_element_h
    #define map_element_h

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "../../screen/includes/screen.hpp"
#include "../../screen/includes/tileset.hpp"
#include "../../player/includes/player.hpp"


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
        void set_texture(TileSet* tileset, int id);

        //Others
        int draw(Screen*, int, int);
        int draw(Screen*, SDL_Rect);

        virtual void interact(Player* player) = 0;

    private:
        bool m_is_solid;
        TileSet* m_tileset;
        int m_texture_id;

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
