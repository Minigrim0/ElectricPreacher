#include "UI/container.hpp"

namespace MiniEngine {
    namespace UI {
        Container::Container()
        :m_rect({0, 0, 0, 0}),
        m_widgets(std::vector<Widgets::Widget*>())
        {}

        Container::~Container(){}

        // Others
        int Container::draw(Core::Screen* screen){
            return 0;
        }

        int Container::update(SDL_Event* event, Core::Screen* screen){
            return 0;
        }
    }
}