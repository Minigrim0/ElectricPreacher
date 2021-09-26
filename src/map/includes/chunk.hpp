#ifndef chunk_h
    #define chunk_h

#include <iostream>

#include "../../screen/includes/tileset.hpp"
#include "constants.hpp"

#include "map_element.hpp"

class Chunk{
    public:
        //Constructors
        Chunk();
        ~Chunk();

        //Overrides
        Chunk& operator=(const Chunk&);

        //Getters
        SDL_Rect get_position() const;

        //Setters
        void set_position(int, int);
        void set_position(SDL_Rect);

        //Others
        void init(Screen* screen);
        void render(Screen* screen, SDL_Rect position);

    private:
        SDL_Rect* m_absolute_coordinates;

        SDL_Texture* m_default_missing;

        MapElement*** m_layer1;
        MapElement*** m_layer2;
        MapElement*** m_layer3;
};

#endif
