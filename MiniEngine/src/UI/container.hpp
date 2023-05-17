#pragma once

#include <SDL_rect.h>

#include "UI/widgets/widgets.hpp"

namespace MiniEngine {
    namespace UI {
class Container : public Widgets::Widget
{
public:
    Container();
    virtual ~Container();

    Container &operator=(const Container &);

    // Others
    int draw(Core::Screen *screen) override;
    int update(SDL_Event *event, Core::Screen *screen) override;

private:
    int type;
    SDL_Rect m_rect;
    std::vector<Widgets::Widget *> m_widgets;
};
    }
}