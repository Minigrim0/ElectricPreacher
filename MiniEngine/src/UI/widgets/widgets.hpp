#pragma once

#include <iostream>
#include <vector>

#include "core/screen.hpp"

/**
 * @brief A widget is a part of the UI that can be drawn and updated
 * This is an abstract class that must be inherited by all widgets
 */
namespace MiniEngine
{
    namespace UI
    {
        namespace Widgets
        {
            class Widget
            {
            public:
                // Constructors
                virtual ~Widget() = default;

                // Others
                virtual int draw(Core::Screen* sc) = 0;
                virtual int update(SDL_Event* e, Core::Screen* sc) = 0;
            };
        }
    }
}