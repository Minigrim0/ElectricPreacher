#ifndef player_hpp
    #define player_hpp

#include "SDL2/SDL.h"


class Player{
    public:
        Player();
        ~Player();

        inline SDL_Rect get_position() const{return m_position;}

        void set_position(SDL_Rect position);
        void set_position(int x, int y);

    private:
        SDL_Rect m_position;
};

#endif
