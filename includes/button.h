#ifndef button_h
    #define button_h

/**
    name : button.h
    purpose : Defines a button and its methods (with animations, ...)
*/

#include <iostream>
#include <SDL2/SDL.h>
#include "screen.h"

class Button{
    public:
        //Constructors
        Button();
        Button(const Button&);
        ~Button();

        //Operators
        Button& operator=(const Button&);

        //Getters
        SDL_Rect get_rect() const;
        SDL_Color get_background_color() const;
        SDL_Color get_foreground_color() const;
        SDL_Color get_contour_color() const;
        SDL_Rect get_text_position(SDL_Surface*) const;
        std::string get_text() const;

        //Setters
        void set_rect(SDL_Rect);
        void set_rect(int, int, int, int);
        void set_position(SDL_Rect);
        void set_position(int, int);
        void set_text_pos(std::string);
        void set_text_pos(int, int);
        void set_text_color(int, int, int);
        void set_background_color(int, int, int);
        void set_contour_color(int, int, int);
        void set_size(SDL_Rect);
        void set_size(int, int);
        void set_text(std::string);

        void move(int, int);
        void resize(int, int);

        //Others
        int update_layout(Screen*, TTF_Font*);
        int draw_contour(SDL_Surface*, SDL_Color);
        int draw(Screen*);
        void update(Screen*);
        bool collide(SDL_Rect) const;

    private:
        SDL_Rect* m_rect;
        SDL_Rect* m_absolute_text_position;
        int m_text_position;
        bool m_hover;

        SDL_Color m_background_color;
        SDL_Color m_foreground_color;
        SDL_Color m_contour_color;

        SDL_Texture* m_image;

        std::string m_text;
        bool m_pos_as_text;
        TTF_Font* m_font;
};

#endif
