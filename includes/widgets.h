#ifndef widgets_h
    #define widgets_h

#include <iostream>
#include <vector>
#include "screen.h"

/**
    name : widgets.h
    purpose : Defines an abstract class for all the widgets of the game (console, button, text input, ...)

    @author : minigrim0
    @version : 1.0
*/

class Widget{
    public:
        //Constructors
        virtual ~Widget(){}

        //Others
        virtual int draw(Screen*) = 0;
        virtual int update(SDL_Event*, Screen*) = 0;
};

#endif
