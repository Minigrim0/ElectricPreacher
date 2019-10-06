#ifndef map_manager_h
    #define map_manager_h

/**
    name : map_manager.h
    purpose : Contains the prototypes for the MapManager class

    @author : mingirim0
    @version : 1.0
*/

#include <iostream>
#include <SDL2/SDL.h>

#include "../includes/constants.h"

/**
    class : MapManager
    purpose : Manages a "chunk" of the total map, which size is defined by CHUNK_SIZE
    A chunk is composed of three layers of "items/images", the ground, the scenery, and the "objects"
*/
class MapManager{
    public:
        //Constructors
        MapManager();
        MapManager(const MapManager&);
        MapManager(int, int);
        MapManager(SDL_Rect);
        ~MapManager();

        //Override
        MapManager& operator=(const MapManager&);

        //Getters
        SDL_Rect* get_position() const;

        //Setters
        void set_position(SDL_Rect);
        void set_position(int, int);

    private:
        int level_1[CHUNK_SIZE][CHUNK_SIZE];
        int level_2[CHUNK_SIZE][CHUNK_SIZE];
        int level_3[CHUNK_SIZE][CHUNK_SIZE];

        SDL_Rect* m_position;
};

#endif
