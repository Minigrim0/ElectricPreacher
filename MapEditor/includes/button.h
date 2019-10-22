#ifndef button_h
    #define button_h

/**
    name : button.h
    purpose : contains the prototypes for the methods of the class Button
*/

#include <iostream>
#include <SDL2/SDL.h>
#include "../../includes/screen.h"

/**
    Class : Button
    purpose : Defines a button in the editor (with animations, ...)
*/
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
        std::string get_text() const;

        //Setters
        void set_rect(SDL_Rect);
        void set_rect(int, int, int, int);
        void set_position(SDL_Rect);
        void set_position(int, int);
        void set_size(SDL_Rect);
        void set_size(int, int);
        void set_text(std::string);

        //Others
        short draw(Screen*);

    private:
        SDL_Rect* m_rect;
        SDL_Color m_background_color;
        SDL_Color m_foreground_color;

        std::string m_text;
};

#endif
