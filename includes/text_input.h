#ifndef text_input_h
    #define text_input_h

/**
    name : text_input.h
    purpose : Handle a complete text input, drawing, handling events (such as copy/paste), and text keeping

    @author : minigrim0
    @version : 1.5
*/

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "screen.h"
#include "widgets.h"

class TextInput: public Widget{
    public:
        TextInput();
        TextInput(const TextInput&);
        ~TextInput();

        TextInput& operator=(const TextInput&);

        // Getters
        std::string get_text() const;
        bool collide(SDL_Event*) const;
        bool collide(int, int) const;
        TTF_Font* get_font() const;
        bool is_empty() const;

        // Setters
        void set_position(int, int);
        void set_text_size(int, int);
        void set_font(std::string, int);
        void set_font(TTF_Font*);

        // Others
        int draw(Screen*) override;
        int update(SDL_Event*, Screen*) override;

        void update_image(Screen*);
        void flush(Screen*);

    private:
        SDL_Texture* m_tex;
        SDL_Texture* m_cursor;
        SDL_Surface* m_background_image;
        SDL_Rect m_rect;
        TTF_Font* m_font;

        std::string m_current_input;
        Sint32 m_cursor_pos;
        Sint32 m_selection_len;

        bool m_is_active;
};

#endif
