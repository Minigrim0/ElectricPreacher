#include <iostream>
#include <vector>
#include "screen.h"

class Widget{
    public:
        //Constructors
        virtual ~Widget(){}

        //Others
        virtual int draw(Screen*) = 0;
        virtual int update(SDL_Event) = 0;
};
