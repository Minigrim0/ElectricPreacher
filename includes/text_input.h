#ifndef text_input_h
    #define text_input_h

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "screen.h"

class TextInput{
    public:
        TextInput();
        ~TextInput();

        // Getters
        std::string get_text() const;

        // Setters
        void set_text_size(int, int);


        // Others
        int draw(Screen*);
        int update(SDL_Event);
        void backspace();
        void update_image(Screen*, TTF_Font*);

    private:
        SDL_Texture* m_tex;
        SDL_Rect* m_init_size;
        SDL_Rect* m_screen_pos_size;

        std::string m_current_input;
        bool m_is_active;
};

#endif
