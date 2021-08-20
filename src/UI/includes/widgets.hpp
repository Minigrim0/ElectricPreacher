#ifndef widgets_h
    #define widgets_h

#include <iostream>
#include <vector>

#include "../../screen/includes/screen.hpp"

class Widget{
    public:
        //Constructors
        virtual ~Widget() = default;

        //Others
        virtual int draw(Screen*) = 0;
        virtual int update(SDL_Event*, Screen*) = 0;
};

#endif
