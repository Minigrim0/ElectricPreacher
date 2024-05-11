#pragma once

#include <SDL_rect.h>
#include <vector>

#include "event/interactible.hpp"

namespace MiniEngine {
namespace UI {
class Container : public Event::Interactible {
  public:
    Container();
    virtual ~Container();

    Container &operator=(const Container &);

    // Others
    void OnRender(Screen *screen) override;
    void OnUpdate(int time_elapsed) override;
    bool OnEvent(SDL_Event *event) override;

  private:
    int type;
    SDL_Rect m_rect;
    std::vector<Event::Interactible *> m_widgets;
};
} // namespace UI
} // namespace MiniEngine
