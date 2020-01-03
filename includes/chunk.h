#ifndef chunk_h
    #define chunk_h

/**
    name : chunk.h
    purpose : Handles a 'chunk' of the map, defined by a global variable as a square of CHUNK_SIZE by CHUNK_SIZE

    @author : mingirim0
    @version : 1.0
*/

#include <iostream>
#include "image_set.h"
#include "map_element.h"
#include "constants.h"

class Chunk{
    public:
        //Constructors
        Chunk();
        Chunk(Chunk&);
        ~Chunk();

        //Overrides
        Chunk& operator=(const Chunk&);

        //Getters
        SDL_Rect get_position() const;
        ImageSet* get_image_set() const;

        //Setters
        void set_position(int, int);
        void set_position(SDL_Rect);
        void set_image_set(ImageSet*);
        void set_image_set(std::string);

        //Others


    private:
        ImageSet* m_image_set;
        SDL_Rect* m_position;

        MapElement*** m_layer1;
        MapElement*** m_layer2;
        MapElement*** m_layer3;
};

#endif
