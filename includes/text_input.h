#ifndef text_input_h
    #define text_input_h

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "screen.h"
#include "ltexture.h"

class TextInput{
    public:
        TextInput();
        TextInput(const TextInput&);
        ~TextInput();

        TextInput& operator=(const TextInput&);

        // Getters
        std::string get_text() const;
        bool collide(SDL_Event*) const;
        bool collide(int, int) const;

        // Setters
        void set_text_size(int, int);


        // Others
        int draw(Screen*);
        int update(SDL_Event*, Screen*, TTF_Font*);
        void update_image(Screen*, TTF_Font*);

    private:
        SDL_Texture* m_tex;
        SDL_Surface* m_background_image;
        SDL_Rect* m_init_size;
        SDL_Rect* m_screen_pos_size;

        std::string m_current_input;
        Sint32 m_cursor_pos;
        Sint32 m_selection_len;

        bool m_is_active;
};

#endif
