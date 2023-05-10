#pragma once

#include <iostream>
#include <vector>

#include "screen/screen.hpp"

class Widget
{
public:
    // Constructors
    virtual ~Widget() = default;

    // Others
    virtual int draw(Screen *) = 0;
    virtual int update(SDL_Event *, Screen *) = 0;
};
