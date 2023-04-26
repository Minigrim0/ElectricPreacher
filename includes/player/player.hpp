#pragma once

#include "SDL.h"

#include "screen/screen.hpp"


class Player{
    public:
        Player();
        ~Player();

        // Getters
        inline SDL_Rect get_position() const{return m_position;}

        // Setters
        void set_position(SDL_Rect position);
        void set_position(int x, int y);

        // Others
        void init(Screen* sc);

        void update(SDL_Event* event);
        int draw(Screen* sc) const;

        void move(SDL_Event* event);

    private:
        SDL_Rect m_position;
        SDL_Texture* m_texture;
};
