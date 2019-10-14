#ifndef chunk_h
    #define chunk_h

/**
    name : chunk.h
    purpose : Contains the prototypes of the chunk Class

    @author : mingirim0
    @version : 1.0
*/

#include <iostream>
#include "image_set.h"
#include "ground_element.h"
#include "wall_element.h"
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
        SDL_Rect m_position;

        GroundElement m_layer1[CHUNK_SIZE][CHUNK_SIZE];
        WallElement m_layer2[CHUNK_SIZE][CHUNK_SIZE];
};

#endif
