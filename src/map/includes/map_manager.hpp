#ifndef map_manager_h
    #define map_manager_h

/**
    name : map_manager.h
    purpose : Contains the prototypes for the MapManager class

    @author : mingirim0
    @version : 1.0
*/

#include <iostream>
#include <vector>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL.h>
#include "../../includes/nlohmann/json.hpp"

#include "../constants.hpp"
#include "chunk.hpp"

/**
    class : MapManager
    purpose : Manages a "chunk" of the total map, which size is defined by CHUNK_SIZE
    A chunk is composed of three layers of "items/images", the ground, the scenery, and the "objects"
*/
class MapManager{
    public:
        //Constructors
        MapManager();
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

        //Others
        void init(Screen* screen);
        int load_map(std::string path);
        int render(Screen *screen, SDL_Rect position);

    private:
        int add_layers(nlohmann::json layers);
        int add_chunks(nlohmann::json chunks);

        SDL_Texture* m_default_missing;
        SDL_Rect* m_position;
        std::vector<Chunk*> m_chunk;
};

#endif
