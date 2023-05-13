#pragma once

#include <iostream>
#include <vector>

#include "screen/screen.hpp"

/**
 * @brief A widget is a part of the UI that can be drawn and updated
 * This is an abstract class that must be inherited by all widgets
 */
class Widget
{
public:
    // Constructors
    virtual ~Widget() = default;

    // Others
    virtual int draw(Screen *) = 0;
    virtual int update(SDL_Event *, Screen *) = 0;
};
